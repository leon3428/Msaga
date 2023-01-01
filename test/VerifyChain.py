import os
import subprocess

EXAMPLES_DIR = 'test/examples3'

def main():
    for dir in os.listdir(EXAMPLES_DIR):
        with open(os.path.join(EXAMPLES_DIR, dir, 'test.c'), 'r') as source_file, \
             open(os.path.join(EXAMPLES_DIR, dir, 'test.in'), 'r') as out_file:

            source_file_content = source_file.read()
            out_file_content = out_file.read()

            p1 = subprocess.run(['test/Lexer'], input=source_file_content, capture_output=True, text=True)
            p2 = subprocess.run(['test/yay/Syntax'], input=p1.stdout, capture_output=True, text=True)
            

            if p2.stdout == out_file_content:
                print('Test', dir, 'passed')
            else:
                print('Test', dir, 'failed')
                print(p2.stdout)
                print(out_file_content)

if __name__ == '__main__':
    main()