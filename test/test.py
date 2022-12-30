import os
import time
import subprocess

EXAMPLES_DIR = 'test/examples'

def main():
    for dir in os.listdir(EXAMPLES_DIR):
        with open(os.path.join(EXAMPLES_DIR, dir, 'test.in'), 'r') as in_file, \
             open(os.path.join(EXAMPLES_DIR, dir, 'test.out'), 'r') as out_file:

            in_file_content = in_file.read()
            out_file_content = out_file.read()

            begin_t = time.time()

            p = subprocess.run(['build/src/Msaga'], input=in_file_content, capture_output=True, text=True)

            end_t = time.time()

            if p.stdout == out_file_content:
                print('Test', dir, 'passed')
            else:
                print('Test', dir, 'failed')
                print(p.stderr)
                print(p.stdout)
                print(out_file_content)
                

            #print('Table generation took: ', end_t-begin_t)

if __name__ == '__main__':
    main()