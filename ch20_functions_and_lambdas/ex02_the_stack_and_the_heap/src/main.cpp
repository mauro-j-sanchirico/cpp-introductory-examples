/**
 * The Stack and the Heap
 *
 * The memory a program uses is divided into:
 *
 *     1. The code segment (also called text segment) where the compiled
 *        program actually lives in memory. This is typically read only.
 *     2. The bss segment (also called the uninitialized data segment). The
 *        abbreviation bss stands for block starting symbol. This is the
 *        section of the compiled object file where zero-initialized statically
 *        allocated variables are stored.
 *     3. The data segment (also called the initialized data segment) is where
 *        initialized global and static variables are stored.
 *     4. The heap is where dynamically allocated variables get their memory
 *        from.
 *     5. The call stack is where function parameters, local variables, and
 *        other function-related information are stored.
 *
 * The Heap
 *
 * The heep keeps track of memory used for dynamic memory allocation (i.e.,
 * with new). If an int is 32b, then dynamically allocating an int will use
 * 32b = 4B on the heap. When delete is called, the memory is returned to the
 * heap. Deleting the pointer doe not delete the variable, it just returns the
 * memory associated with the address back to the OS.
 *
 * Allocating memory on the heap has advantages and disadvantages. The heap is
 * flexible and allows allocating memory for objects with size unknown at
 * compile time. Since the heap is a large pool of memory, large arrays,
 * structures, and classes can be allocated on it. However, It is slow and must
 * be accessed through a pointer. Accessing through a pointer can also be
 * slower than direct access.
 *
 * Dynamically allocated memory stays allocated until it is deallocated or the
 * application ends and the OS cleans it up. If it is not allocated and the
 * program keeps allocating more memory this is known as a memory leak and can
 * use up all available memory.
 *
 * The Stack
 *
 * The *call stack* tracks all the active functions that have been called
 * but are not yet finished. A stack is a first in last out (FILO) data
 * structure with three operations:
 *     1. Peek / top - look at the top of the stack
 *     2. Push - add to the top of the stack
 *     3. Pop - pop from the top of the stack
 *
 * Each time a function is called, a *stack frame* is pushed to keep track of
 * everything the CPU needs to execute the function and return to the caller
 * function when the current function is finished. When an item is popped off
 * the stack, its memory is not explicitly deleted. The stack pointer just
 * moves down to the next frame so no time is wasted.
 *
 * A stack frame consists of:
 *     * The address of the next instruction after the function call (i.e., the
 *       *return address*)
 *     * All the function arguments
 *     * Memory for any local variables
 *     * Saved copies of any registers modifed by the function that need to be
 *       restored when the function returns.
 *
 * When a function is called:
 *     * A stack frame is pushed
 *     * The CPU jumps to the functions start point
 *     * The instructions in the function begin executing
 *
 * Once the function terminates:
 *     * Registers are restored from the stack
 *     * The stack frame is popped off the stack
 *     * The return value is handled
 *     * The CPU resumes execution at the return address
 *
 * Some computers handle return values as part of the stack, others place them
 * in a CPU register.
 *
 * The stack has advantages and disadvantages. Allocating memory on the stack
 * is fast. Memory on the stack stays in scope until it is popped off the
 * stack. However, all the memory allocated on the stack must be known at
 * compile time. Because the stack is small, it is not good practice to use
 * too much stack space. The stack is not a good place to store large data
 * structures.
 */

#include <iostream>

auto f() -> void;
auto g() -> void;
auto h() -> void;

auto main() -> int
{
    std::cout << "In main()..." << std::endl;
    std::cout << "Calling f()..." << std::endl;
    f();
    std::cout << "Returned to main()." << std::endl;
}

auto f() -> void
{
    std::cout << "--- Pushing f()" << std::endl;
    g();
    std::cout << "--- Popping f()" << std::endl;
}

auto g() -> void
{
    std::cout << "------ Pushing g()" << std::endl;
    h();
    std::cout << "------ Popping g()" << std::endl;
}

auto h() -> void
{
    std::cout << "--------- Pushing h()" << std::endl;
    std::cout << "--------- Popping h()" << std::endl;
}