from transformers import GPT2Tokenizer
import sys

def count_tokens_in_file(filename):
    tokenizer = GPT2Tokenizer.from_pretrained("gpt2")

    with open(filename, 'r', encoding='utf-8') as file:
        content = file.read()  # Read the whole file at once
        tokens = tokenizer.tokenize(content)
        token_count = len(tokens)
        print(f'Total number of tokens in file: {token_count}')

if len(sys.argv) < 2:
    print('specify a text file to be counted')
    exit()
count_tokens_in_file(sys.argv[1])
