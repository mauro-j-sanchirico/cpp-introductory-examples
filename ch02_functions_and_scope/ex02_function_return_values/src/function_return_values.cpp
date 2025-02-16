/**
 * The definition of a function sets its *return type*. This is the type of the
 * value that will be returned by the function. A return type of void means the
 * function does not return any value.
 *
 * The *return statement* (the statement that begins with *return*) indicates
 * the value to be returned to the caller. The expression that follows the
 * return statement and computes this value is called the *return expression*.
 *
 * The value produced by the return expression is copied back to the caller.
 * The copy is called the return value.
 */

#include <iostream>

int getValueFromUser() // This tells the compiler the function will return int
{
    std::cout << "Enter an integer: ";
    int input{};
    std::cin >> input;
    return input; // return the value the user entered back to the caller
}

int main()
{
    // Use function calls to avoid writing the same code twice
    // As a best practice, remember to write "DRY" ("Don't Repeat Yourself")
    // code instead of "WET" code ("Write Everything Twice"). Writing DRY code
    // saves you time and makes your code easier to maintain since the code
    // only needs to be changed in one place to update the functionality
    // everywhere it is used.
    int x{getValueFromUser()};
    int y{getValueFromUser()};

    std::cout << x << " + " << y << " = " << x + y << '\n';

    return 0;
}

/**
 * In C++, main must return an integer. This integer should be zero if the
 * program executed normally. Non-zero exit codes are usually used to indicate
 * failure. This works on most operating systems but is not guaranteed to be
 * portable.
 *
 * The C++ standard only defines the meaning of 3 status codes:
 *  0 - indicate success
 *  EXIT_SUCCESS - indicate success, comes from cstdlib
 *  EXIT_FAILURE - indicate failure, comes from cstdlib
 *
 * To maximize portability, only use 0 or EXIT_SUCCESS to indicate successful
 * program termination, or EXIT_FAILURE to indicate an unsuccessful
 * termination. The status code is provided back to the operating system. This
 * provides a basic way for any program launching another program to check if
 * it terminated successfully.
 *
 * Note that in C++, explicit function calls to main() are not allowed. The
 * following code will not compile in most cases. Some compilers will allow it
 * for backwards compatibility with C which does allow explicit calls to
 * main().
 *
 * The following is illegal in C++:
 *
 * void foo()
 * {
 *      main(); // Compile error: explicit calls to main() not allowed!
 * }
 *
 * void main() // Main not allowed
 * {
 *      foo(); // Compile error: main not allowed to have non-int return type
 * }
 *
 * Additional notes:
 *  - Function main will implicitly return 0 if no return statement is provided
 *  - Unlike some other languages, functions can only return a single value in
 *      C++. There are many ways to work around the limitation of functions
 *      returning a single value that will be covered in later examples.
 *  - The meaning of a function return value is determined by the author. Some
 *      functions return status codes while others return computed values. Be
 *      sure to clarify the meaning of your return values in comments and
 *      documentation.
 */