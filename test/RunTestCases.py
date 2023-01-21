import os
import subprocess
import time

EXAMPLES_DIR = 'test/examples7'

def main():
    cnt = 0
    maxCnt = 0
    for dir in os.listdir(EXAMPLES_DIR):
        if dir == "eval.cfg" or dir=="integration":
            continue
        with open(os.path.join(EXAMPLES_DIR, dir, 'test.c'), 'r') as source_file:
            source_file_content = source_file.read()
            if os.path.join(EXAMPLES_DIR, dir, 'test.out') in ["test/examples9/26_niz4/test.out"]:#, "test/examples5/32_gcd/test.out"]:
                continue
            #p1 = subprocess.run(['test/Test2'], input=source_file_content, capture_output=True, text=True)
            #p2 = subprocess.run(['test/analizator/Main'], input=p1.stdout, capture_output=True, text=True)
            #if len(p1.stderr) != 0 or len(p2.stderr) != 0:
            #    print(p1.stderr, p2.stderr)
            with open(os.path.join(EXAMPLES_DIR, dir, 'test.in'), 'r') as input_file:
                inp = input_file.read()  
                subprocess.run(['build/src/Msaga'], input=inp, capture_output=True, text=True)
                
                p4 = subprocess.run(['node', 'test/frisc/main.js', 'out.asm'], capture_output=True, text=True)
                with open(os.path.join(EXAMPLES_DIR, dir, 'test.out'), 'r') as output_file:
                    output = output_file.read()
                    if p4.stdout.strip() == output.strip():
                        print("SUCCESS", os.path.join(EXAMPLES_DIR, dir, 'test.out'))
                        cnt += 1
                    else:
                        print(f"NOT YAY {os.path.join(EXAMPLES_DIR, dir)}")
                        print("GOT THIS:", p4.stdout)
                        print("BUT WANTED THIS", output)
                    maxCnt += 1
    print(f"Passed {cnt}/{maxCnt}")

if __name__ == '__main__':
    main()