import subprocess

EXE_PATH = r"..\ConsoleApplication1\x64\Debug\Interpreter.exe"

def run_interpreter(input_lines):
    input_data = "\n".join(input_lines) + "\n"
    process = subprocess.Popen(
        [EXE_PATH],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )
    stdout, stderr = process.communicate(input_data)
    return stdout.strip().split("\n"), stderr.strip()


def run_tests():
    tests = [
        {
            "input": ["5 + 3 * 2"],
            "expected": ["11"]
        },
        {
            "input": ["max(5, 2)"],
            "expected": ["5"]
        },
        {
            "input": ["min(3, 4)"],
            "expected": ["3"]
        },
        {
            "input": ["max(min(3 * 2, 2), 2)"],
            "expected": ["2"]
        },
        {
            "input": ["var a = max(min(3 * 2, 2), 2)", "a + 3"],
            "expected": ["5"]
        },
        {
            "input": ["var b = 10", "var b = 20"],
            "expected": ["Error: Variable 'b' is already defined"]
        },
        {
            "input": ["pow(2, 4)"],
            "expected": ["16"]
        },
        {
            "input": ["abs(0 - 7)"],
            "expected": ["7"]
        },
        {
            "input": ["10 / 0"],
            "expected": ["inf"]
        },
        {
            "input": ["unknownVar + 1"],
            "expected": ["Error: Unknown variable: unknownVar"]
        },
        {
            "input": ["nosuchfunc(1, 2)"],
            "expected": ["Error: Unknown function: nosuchfunc"]
        },
        {
            "input": ["pow(2, 3, 4)"],
            "expected": ["Error: pow needs 2 arguments"]
        },
        {
            "input": ["2.5 + 1.5"],
            "expected": ["4"]
        },
        {
            "input": ["((2 + 3) * (4 - 1))"],
            "expected": ["15"]
        },
    ]

    passed = 0
    failed = 0

    for test in tests:
        output, error = run_interpreter(test["input"])

        if error:
            print(f"FAILED (stderr): input={test['input']}")
            print(f"  stderr: {error}")
            failed += 1
            continue

        if output == test["expected"]:
            print(f"PASSED: input={test['input']}")
            passed += 1
        else:
            print(f"FAILED: input={test['input']}")
            print(f"  expected: {test['expected']}")
            print(f"  got:      {output}")
            failed += 1

    print(f"\n{passed} passed, {failed} failed")


if __name__ == "__main__":
    run_tests()