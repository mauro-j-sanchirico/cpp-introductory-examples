/**
 * Out of Memory
 *
 * In this example, trying to allocate a large array on the stack causes
 * undefined behavior, leading to a segmentation fault.
 *
 * A segmentation fault is an error raised by hardware with memory protection,
 * notifying an operating system that the running program has attempted to
 * access memory that is not available or that it does not have permission to
 * access.
 *
 * A segmentation fault is thrown by the hardware itself to protect the OS
 * from a malicious or defective program from using all its memory, overwriting
 * important files, or accessing memory that is protected, leading to security
 * vulnerabilities.
 */

#include <iostream>

auto main() -> int
{
    int stack[100000000] = {};
    std::cout << "Test..." << stack[0] << std::endl;
}