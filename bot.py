#!/usr/bin/env python3

from anthropic import AsyncAnthropic
from openai import OpenAI

import argparse
import asyncio
import os
from dotenv import load_dotenv


default_max_tokens = 2048
default_temperature = 0.6
models = {
    'haiku3':     ('anthropic', 'claude-3-haiku-20240307'),
    'sonnet3.5':  ('anthropic', 'claude-3-5-sonnet-20240620'),
    'gpt4o-mini': ('openai',    'gpt-4o-mini-2024-07-18'),
    'gpt4o':      ('openai',    'gpt-4o-2024-08-06'),
    'deepseek':   ('deepseek',  'deepseek-coder'),
}


def parse_args():
    model_names = models.keys()
    parser = argparse.ArgumentParser(description='NEON chatbot')
    parser.add_argument('prompt_file', help='path to the prompt file')
    parser.add_argument('model', help=f'{", ".join(model_names)}')
    parser.add_argument('question', help='ask the chatbot')
    args = parser.parse_args()
    if args.model not in model_names:
        print(f'select model from {", ".join(model_names)}')
        exit(1)
    args.model = models[args.model]
    return args


def create_client(args):
    with open(args.prompt_file, 'r') as f:
        prompt = f.read()
    messages = [
        {
            'role': 'user',
            'content': prompt,
        }, {
            'role': 'assistant',
            'content': 'Understood, I\'m ready to answer questions',
        }, {
            'role': 'user',
            'content': args.question,
        },
    ]
    api, model = args.model
    # deepseek uses openai api, override the api key and endpoint
    if api == 'anthropic':
        return AnthropicClient(model, messages)
    elif api == 'openai':
        return OpenaiClient(model, messages)
    elif api == 'deepseek':
        api_key = os.getenv('DEEPSEEK_API_KEY')
        api_base = 'https://api.deepseek.com'
        return OpenaiClient(model, messages, api_key, api_base)
    raise NotImplementedError(f'unsupported api: {api}')


class AnthropicClient:
    def __init__(self, model, messages):
        self.model = model
        self.messages = messages
        self.client = AsyncAnthropic()

    # use async mode
    async def streaming(self):
        async with self.client.messages.stream(
            model=self.model,
            messages=self.messages,
            max_tokens=default_max_tokens,
            temperature=default_temperature,
        ) as stream:
            async for text in stream.text_stream:
                print(text, end='', flush=True)
        final_message = await stream.get_final_message()
        return final_message.usage

    def __call__(self):
        usage = asyncio.run(self.streaming())
        return usage


class OpenaiClient:
    def __init__(self, model, messages, api_key=None, api_base=None):
        self.model = model
        self.messages = messages
        self.client = OpenAI(api_key=api_key, base_url=api_base)

    # use stream mode (openai also supports AsyncOpenAI)
    def __call__(self):
        stream = self.client.chat.completions.create(
            model=self.model,
            messages=self.messages,
            max_tokens=default_max_tokens,
            temperature=default_temperature,
            stream=True,
            stream_options={'include_usage': True},
        )
        for chunk in stream:
            content = chunk.choices[0].delta.content
            if content is None:
                break
            print(content, end='', flush=True)
        try:
            final_message = next(stream)
            return final_message.usage
        except:
            # deepseek doesn't support token usage counting
            return None


if __name__ == '__main__':
    args = parse_args()
    load_dotenv()
    print(f'model: {args.model}')
    print(f'prompt file: {args.prompt_file}')
    print(f'question: {args.question}')
    r = input('ready to go (y/n): ')
    if r != 'y' and r != 'Y':
        exit(0)
    client = create_client(args)
    print('--------------------------------------------------------------')
    usage = client()
    print('\n')
    print('--------------------------------------------------------------')
    if usage:
        print(usage)
