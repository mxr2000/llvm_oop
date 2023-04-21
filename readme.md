# LLOP: An implementation of Objective Oriented Language Constructs to LLVM IR

## About

Document can be found at:
https://mxr2000.github.io/llop_doc

Grammar of the language: https://github.com/mxr2000/llvm_oop/blob/master/lib/Parser/LLOP.g4

## Build

Prerequisite:

1. LLVM 16
2. Antlr4 Runtime
3. Cmake

Build:

```shell
mkdir build
cd build
cmake --build .
```


## Example

Example of a program: https://github.com/mxr2000/llvm_oop/blob/master/examples/demo.llop

```
CLASS Person (Object) []
BEGIN
    VAR age: Int
    VAR salary: Int

    FUNC init(age: Int, salary: Int) -> Void
    BEGIN
        SELF.age = age
        SELF.salary = salary
    END

    FUNC getAge() -> Int
    BEGIN
        RETURN SELF.age
    END

    FUNC getSalary() -> Int
    BEGIN
        RETURN SELF.age
    END
END

STATIC Person
BEGIN
    FUNC compare(p1: Person, p2: Person) -> Int
    BEGIN
        RETURN p1.getAge() - p2.getAge()
    END
END

INTERFACE Consumer
BEGIN
    FUNC consume() -> Void
    FUNC earn() -> Void
END

CLASS Employee (Person) [Consumer]
BEGIN
    VAR id: Int

    FUNC init(age: Int, salary: Int, id: Int) -> Void
    BEGIN
        SUPER.init(age, salary)
        SELF.id = id
    END

    FUNC getSalary() -> Int
    BEGIN
        RETURN 0
    END

    FUNC consume() -> Void
    BEGIN
        IF (SELF.salary > 1000) THEN
            SELF.salary = 1000
        WHILE (SELF.salary > 0)
            SELF.salary = SELF.salary - 1
        IF (SELF.salary < 0) THEN
        BEGIN
            SELF.salary = SELF.salary + 10
        END
    END

    FUNC earn() -> Void
    BEGIN

    END

    FUNC eat() -> Void
    BEGIN
        VAR num1: Int
        VAR num2: Int
        num1 = 30
        num2 = 45
        OUTPUT (num1 + num2) * 2
    END
END

STATIC Program
BEGIN
    FUNC main() -> Int
    BEGIN
        VAR person: Person
        VAR employee: Employee
        VAR e: Employee
        person = NEW Person(10, 100)
        employee = NEW Employee(20, 1000, 20)
        employee.eat()
        e = person.[Employee]
        RETURN 0
    END
END

```