#include <iostream>

/**
 * A *function parameter* is a variable used in the header of a function.
 * Function parameters work almost identically to variables defined inside a
 * function, but they are initialized with values provided by the caller.
 * Function parameters provide a way for the caller to pass data to the callee.
 *
 * An *argument* is a value that is passed from the caller to the function
 * when a function call is made.
 *
 * When a function is called, all of the parameters of the function are created
 * as variables, and the value of each argument is copied into the matching
 * parameter via copy-assignment. This process is called *pass by value*.
 * Function parameters that utilize pass by value are called value parameters.
 *
 * Note: parameters are the variables the function creates to hold data from
 * the caller. Arguments are the values the caller passes to the callee.
 */

// Get a value from the user and return it
int getValueFromUser()
{
    std::cout << "Enter an integer: ";
    int input{};
    std::cin >> input;

    return input;
}

// Accept a value as input and print it
void printDouble(int value)
{
    std::cout << value << " doubled is: " << value * 2 << '\n';
}

// Takes two values as parameters and returns their sum
// The values are determined by the caller
int add(int x, int y)
{
    return x + y;
}

// Takes two values as parameters and returns their product
// The values are determined by the caller
int multiply(int x, int y)
{
    return x * y;
}

/**
 * Function parameters that are not used inside the function are called
 * *unreferenced parameters*.
 *
 * Unreferenced parameters will generate a compiler warning, and will not
 * compile if the compiler is set to treat warnings as errors.
 *
 * Sometimes unreferenced parameters are used to ensure backwards compatibility
 * of a function call. In this case, they can be left unnamed to avoid a
 * compiler warning.
 */

// This function can accept a single int parameter and will not use it.
void doSomething(int)
{
    std::cout << "Called doSomething()...\n";
}

int main()
{
    // Pass the return value of getValueFromUser() to printDouble()
    std::cout << "printDouble() example...\n";
    printDouble(getValueFromUser());

    // Use parameters and return values to perform basic math operations
    std::cout << "Math examples...\n";
    auto x = int{2};
    auto y = int{3};
    std::cout << x << " + " << y << " = " << add(x, y) << '\n';
    std::cout << x << " * " << y << " = " << multiply(x, y) << '\n';

    // Call a function with an unreferenced parameter
    doSomething(2);

    return 0;
}