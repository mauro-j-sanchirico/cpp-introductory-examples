/**
 * Functions do not need to return a value to the caller. To tell the compiler
 * that a function does not return a value, a return type of void is used. A
 * function that does not return a value is called a *non-value returning
 * function* or a *void function*.
 */

#include <iostream>

// Function that does not return a value
void returnNothing()
{
    std::cout << "This is a void function. Is does not return anything.\n";
}

// Function that returns a value
int returnFive()
{
    return 5;
}

int main()
{
    // When calling a function by itself, no value is returned
    returnNothing();
    returnFive();

    // When calling a function in a context that requires a value (like std::cout)
    std::cout << returnFive(); // ok: we can call a function that returns a value, and the value will be used
    // std::cout << returnNothing(); // Compile error: there is no value returned to be printed!
}