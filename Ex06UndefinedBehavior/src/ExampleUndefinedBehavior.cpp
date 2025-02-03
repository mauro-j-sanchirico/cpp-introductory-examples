#include <iostream>

// Undefined behavior is the result of executing code whose behavior is not
// well defined by the C++ language. Using a variable uninitialized is a
// common example of undefined behavior. Since the compiler will not allow
// this with warnings set to errors, we can use the following code to trick
// the compiler into thinking we are defining the variable for this
// example.
//
// Symptoms of undefined behavior include:
//  - Different results on each run of a program
//  - Same incorrect result produced every time
//  - Sometimes producing correct results and sometimes not
//  - Producing a correct result and then an incorrect result later
//  - Crashing immediately or after running
//  - Program working on some compilers but not on others
//  - Program working until you change seemingly unrelated code

void doNothing(int &)
{
}

int main()
{
    // Undefined Behavior Example

    int x;
    doNothing(x);
    // Notice this value is different on every run of the program!
    std::cout << "The garbage value of x is " << x << std::endl;

    // Implementation Defined Behavior Example

    // Implementation defined behavior is that which is specific to a given
    // compiler. The following code may produce 2 bytes on some platforms and
    // 4 bytes on others.
    std::cout << "Size of an integer is " << sizeof(int) << " bytes." << std::endl;

    // Unspecified behavior is implementation defined behavior where the
    // compiler implementation need not document the behavior. It is best
    // practice to avoid unspecified and implementation defined behavior.
    return 0;
}