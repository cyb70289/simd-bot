#!/usr/bin/env python3

from dotenv import load_dotenv
from anthropic import AsyncAnthropic
import argparse
import asyncio
import os


default_max_token = 2048
default_temperature = 0.6
models = {
    'haiku3':     ('anthropic', 'claude-3-haiku-20240307'),
    'sonnet3.5':  ('anthropic', 'claude-3-5-sonnet-20240620'),
    'gpt4o-mini': ('openai',    'gpt-4o-mini'),
    'gpt4o':      ('openai',    'gpt-4o'),
    'gpt4':       ('openai',    'gpt-4o-turbo'),
}


def parse_args():
    model_names = models.keys()
    parser = argparse.ArgumentParser(description='NEON chatbot')
    parser.add_argument('prompt_file', help='path to the prompt file')
    parser.add_argument('model', help=f'{", ".join(model_names)}')
    parser.add_argument('question', help='user questions to the chatbot')
    args = parser.parse_args()
    if args.model not in model_names:
        print(f'select model from {", ".join(model_names)}')
        exit(1)
    args.model = models[args.model]
    return args


def create_client(args):
    with open(args.prompt_file, 'r') as file:
        prompt = file.read()
    messages = [
        {
            "role": "user",
            "content": prompt,
        }, {
            "role": "assistant",
            "content": "Understood, I'm ready to answer questions",
        }, {
            "role": "user",
            "content": args.question,
        },
    ]
    api, model = args.model
    if api == 'anthropic':
        return AsyncAnthropicClient(model, messages)
    raise NotImplementedError('tbd')


class AsyncAnthropicClient:
    def __init__(self, model, messages):
        self.model = model
        self.messages = messages
        self.client = AsyncAnthropic()

    async def streaming(self):
        print('--------------------------------------------------------------')
        async with self.client.messages.stream(
            messages=self.messages,
            model=self.model,
            max_tokens=default_max_token,
            temperature=default_temperature,
        ) as stream:
            async for text in stream.text_stream:
                print(text, end='', flush=True)
        final_message = await stream.get_final_message()
        print('\n')
        print('--------------------------------------------------------------')
        print(final_message.usage)

    def __call__(self):
        asyncio.run(self.streaming())


if __name__ == "__main__":
    args = parse_args()
    load_dotenv()
    print(f'model: {args.model}')
    print(f'prompt file: {args.prompt_file}')
    print(f'question: {args.question}')
    r = input("ready to go (y/n): ")
    if r != 'y' and r != 'Y':
        exit(0)
    client = create_client(args)
    client()
