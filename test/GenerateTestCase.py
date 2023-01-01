import os
import subprocess

EXAMPLES_DIR = 'test/examples3'

def main():
    for dir in os.listdir(EXAMPLES_DIR):
        with open(os.path.join(EXAMPLES_DIR, dir, 'test.c'), 'r') as source_file:

            source_file_content = source_file.read()

            p1 = subprocess.run(['test/Lexer'], input=source_file_content, capture_output=True, text=True)
            p2 = subprocess.run(['test/yay/Syntax'], input=p1.stdout, capture_output=True, text=True)

            if len(p1.stderr) != 0 or len(p2.stderr) != 0:
                print(p1.stderr, p2.stderr)

            with open(os.path.join(EXAMPLES_DIR, dir, 'test.in'), 'w') as test_in:
                test_in.write(p2.stdout)

            p3 = subprocess.run(['build/src/Msaga'], input=p2.stdout, capture_output=True, text=True)

            with open(os.path.join(EXAMPLES_DIR, dir, 'test.out'), 'w') as test_out:
                test_out.write(p3.stdout)
            


if __name__ == '__main__':
    main()