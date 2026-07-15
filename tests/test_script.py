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
            "name": "Basic addition",
            "input": ["5 + 3 * 2"],
            "expected": ["11"]
        },
        {
            "name": "Parentheses override precedence",
            "input": ["(5 + 3) * 2"],
            "expected": ["16"]
        },
        {
            "name": "Division and subtraction",
            "input": ["10 / 2 - 3"],
            "expected": ["2"]
        },
        {
            "name": "Nested parentheses",
            "input": ["((2 + 3) * (4 - 1))"],
            "expected": ["15"]
        },
        {
            "name": "Float numbers",
            "input": ["2.5 + 1.5"],
            "expected": ["4"]
        },
        {
            "name": "pow",
            "input": ["pow(2, 4)"],
            "expected": ["16"]
        },
        {
            "name": "abs",
            "input": ["abs(0 - 7)"],
            "expected": ["7"]
        },
        {
            "name": "max",
            "input": ["max(5, 2)"],
            "expected": ["5"]
        },
        {
            "name": "min",
            "input": ["min(3, 4)"],
            "expected": ["3"]
        },
        {
            "name": "Nested function calls",
            "input": ["max(min(3 * 2, 2), 2)"],
            "expected": ["2"]
        },
        {
            "name": "Function inside arithmetic",
            "input": ["pow(2, 3) + min(10, 5)"],
            "expected": ["13"]
        },
        {
            "name": "Variable binding and reuse",
            "input": ["var a = max(min(3 * 2, 2), 2)", "a + 3"],
            "expected": ["5"]
        },
        {
            "name": "Variable in nested expression",
            "input": ["var x = pow(2, 3)", "max(x, 5)"],
            "expected": ["8"]
        },
        {
            "name": "Immutability violation",
            "input": ["var b = 10", "var b = 20"],
            "expected": ["Error: Variable 'b' is already defined"]
        },
        {
            "name": "User function: min + max",
            "input": ["def myfunc(a, b) { min(a, b) + max(a, b) }", "myfunc(3, 4)"],
            "expected": ["7"]
        },
        {
            "name": "User function: arithmetic in body",
            "input": ["def double(x) { x * 2 }", "double(5)"],
            "expected": ["10"]
        },
        {
            "name": "User function: called multiple times",
            "input": ["def square(x) { x * x }", "square(3)", "square(4)"],
            "expected": ["9", "16"]
        },
        {
            "name": "User function: nested built-in calls",
            "input": ["def hypo(a, b) { pow(a, 2) + pow(b, 2) }", "hypo(3, 4)"],
            "expected": ["25"]
        },
        {
            "name": "User function redefine error",
            "input": ["def f(x) { x + 1 }", "def f(x) { x + 2 }"],
            "expected": ["Error: Function 'f' is already defined"]
        },
        {
            "name": "Division by zero",
            "input": ["10 / 0"],
            "expected": ["inf"]
        },
        {
            "name": "Unknown variable",
            "input": ["unknownVar + 1"],
            "expected": ["Error: Unknown variable: unknownVar"]
        },
        {
            "name": "Unknown function",
            "input": ["nosuchfunc(1, 2)"],
            "expected": ["Error: Unknown function: nosuchfunc"]
        },
        {
            "name": "Wrong number of arguments",
            "input": ["pow(2, 3, 4)"],
            "expected": ["Error: pow needs 2 arguments"]
        },
    ]

    passed = 0
    failed = 0

    for test in tests:
        output, error = run_interpreter(test["input"])

        if error:
            print(f"FAILED [{test['name']}]: stderr={error}")
            failed += 1
            continue

        if output == test["expected"]:
            print(f"PASSED [{test['name']}]")
            passed += 1
        else:
            print(f"FAILED [{test['name']}]")
            print(f"  input:    {test['input']}")
            print(f"  expected: {test['expected']}")
            print(f"  got:      {output}")
            failed += 1

    print(f"\n{passed} passed, {failed} failed")


if __name__ == "__main__":
    run_tests()