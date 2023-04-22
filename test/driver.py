def print_diff(expected: str, actual: str):
    print("\033[32mExpected:")
    print(expected)
    print("\033[31mActual:")
    print(actual)


if __name__ == "__main__":
    print_diff("aaa", "bbb")
