import subprocess
import argparse
from pathlib import Path

parser = argparse.ArgumentParser()
parser.add_argument("--compile", action="store_true", help="Compile before running tests")
parser.add_argument("--testcases", default="testcases", help="Directory containing test cases")
args = parser.parse_args()

compile = args.compile
testcases_dir = Path(args.testcases)

if compile:
    print("Compiling...")
    subprocess.run(["g++", "-std=c++23", "-lstdc++exp", "-g", "main.cpp"])

for test_file in sorted(testcases_dir.glob("*.txt")):
    print(f"testcases/{test_file.name}:")
    with open(test_file) as f:
        result = subprocess.run(["./a.exe"], stdin=f,
                                capture_output=True, text=True)
        print(result.stdout.strip())
        if result.stderr:
            print(f"Error: {result.stderr.strip()}")
    # print("-" * 40)
    print()
