#include <iostream>

int five()
{
    return 5;
}

int main()
{
    // In C++ operators allow combining two values, and work as expected:
    std::cout << 1 + 2 << std::endl;

    /**
     * Above, the literals (literal values hardcoded into the program) are
     * the operands of the + operator.
     *
     * The number of operands an operator takes is called its "arity". C++
     * operators come in four different arities.
     *     - Unary - Act on a single operand (e.g., sign operator, -)
     *     - Binary - Act on two operands (e.g., +, -, /, *)
     *     - Ternary - Act on three operands (e.g., the conditional operator, ?)
     *      - Nullary - Act on zero operands (e.g., the throw operator)
     *
     * Arithmetic order of operations is obeyed.
     *
     * Most operators simply return a value but some operators have *side
     * effects*. The assignment operator has the side effect of changing the
     * value of one of its operands.
     *
     * Note that operators that we usually use for their side effects may
     * have non-intuitive return values. For example:
     */
    int y{};
    int x = (y = 5);
    std::cout << "y = " << y << std::endl;
    std::cout << "x = " << x << std::endl;
    // In this case, the assigned value (5) is the returned value.

    // We can combine operators with expressions
    int a{2};
    int b{2 + 3};
    int c{(2 * 3) + 4};
    int d{b};
    int e{five()};

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;

    // The result of an expression can be a value, an object, or nothing.

    // Some compilers will produce warnings if they detect a useless expression
    // 2 + 3;

    // A compound expression contains 2 or more operators
    a = 10 * (2 + 3);

    return 0;
}