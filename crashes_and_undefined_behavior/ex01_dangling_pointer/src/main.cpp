/**
 * Dangling Pointer example
 *
 * Dangling pointers are one of the most common causes of unsafe behavior in
 * C++. A *dangling pointer* is one that is pointing to deallocated memory.
 * Dereferencing or deleting a dangling pointer will lead to undefined
 * behavior. C++ does not guarantee what will happen to the contents of
 * deallocated memory. If delete is called on a pointer, its memory is returned
 * to the operating system. The operating system may not allow the program to
 * access that memory afterward, leading to a program crash.
 */

#include <iostream>

auto main() -> int
{
    int *ptr{new int};
    *ptr = 7;

    delete ptr;

    // Dereferencing a dangling pointer causes UB
    std::cout << *ptr << std::endl; // prints a garbage value

    // Deallocating memory after it has already been deallocated leads to UB
    delete ptr; // crashes program!
}