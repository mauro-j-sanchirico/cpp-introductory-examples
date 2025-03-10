/**
 * Stack Overflow Error!
 *
 * The stack is used to keep track of where each function called is stored in
 * memory and where the CPU needs to return to after each is complete.
 *
 * If we call too many layers of functions down, we get a stack overflow error.
 * In general, it is a best practice to design programs to avoid infinite
 * recursion and some compilers will try to catch this and issue a warning.
 *
 * Source: https://www.learncpp.com/cpp-tutorial/the-stack-and-the-heap/
 */

#include <iostream>

int g_counter{0};

void eat_stack()
{
    std::cout << ++g_counter << std::endl;

    // Trick the compiler into thinking this is not infinite recursion
    if (g_counter > 0)
    {
        eat_stack();
    }

    // Prevent compiler from doing tail-call optimization
    std::cout << "hi" << std::endl;
}

auto main() -> int
{
    eat_stack();
}