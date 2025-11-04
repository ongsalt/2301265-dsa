import subprocess
from pathlib import Path

compile = False
testcases_dir = Path("testcases")

if compile:
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
