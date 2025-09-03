import os
import subprocess

def list_files_in_testcases():
    testcases_dir = 'testcases'
    if not os.path.exists(testcases_dir):
        print(f"Directory {testcases_dir} does not exist")
        return []
    files = []
    for root, dirs, filenames in os.walk(testcases_dir):
        for filename in filenames:
            rel_dir = os.path.relpath(root, testcases_dir)
            rel_file = f"{rel_dir}/{filename}" if rel_dir != '.' else filename
            files.append(rel_file)
    return files

def run_greedy_with_testcases():
    testcases_dir = 'testcases'
    for rel_path in list_files_in_testcases():
        file_path = os.path.join(testcases_dir, rel_path)
        print(f"{rel_path} : ", end='')
        with open(file_path, 'r') as f:
            process = subprocess.run([
                'target/release/greedy.exe'
            ], input=f.read(), text=True, capture_output=True)
        print(f"{process.stdout.strip()}")
        if process.stderr:
            print(f"Error: {process.stderr.strip()}")

if __name__ == "__main__":
    files = list_files_in_testcases()
    # print(files)
    run_greedy_with_testcases()