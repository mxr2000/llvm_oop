import subprocess


def print_diff(expected: str, actual: str):
    print("\033[32mExpected:")
    print(expected)
    print("\033[31mActual:")
    print(actual)


def run_test(test_name: str):
    expected_filename = "outputs/" + test_name + "_result.txt"
    bin_path = "./build.sh"
    args = ["./inputs/" + test_name]
    subprocess.run(["sh", bin_path] + args)
    with open('a.txt', 'r') as output_file, open(expected_filename, 'r') as expected_file:
        output = output_file.read()
        expected = expected_file.read()
        if output == expected:
            print("\033[32mTest {} passed".format(test_name))
        else:
            print_diff(expected, output)


def copy_files():
    subprocess.run(["cp", "../cmake-build-debug/src/build.sh", "."])
    subprocess.run(["cp", "../cmake-build-debug/src/main", "."])
    subprocess.run(["cp", "../cmake-build-debug/src/rt.ll", "."])


if __name__ == "__main__":
    copy_files()
    run_test("relational")
    run_test("access")
    run_test("boolean")
    run_test("override")
