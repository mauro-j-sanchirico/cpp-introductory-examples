#include <iostream>

/**
 * A *function* is a reusable sequence of statements designed to do a job.
 *
 * C++ libraries provide many pre-written functions. Functions written by
 * users of the C++ language are called *user-defined functions*.
 *
 * Under the hood, functions tell the CPU to *jump* from one line of execution
 * to another line where a useful routine that must be reused is defined.
 *
 * A good analogy is reading a textbook. There may be steps to solve a specific
 * problem in chapter 1. When you get to chapter 5, solving a problem from
 * chapter 1 might be required as a substep to solve a problem from chapter 5.
 * As a student, you would save time during studying by placing a bookmark at
 * the useful page where the steps are defined in chapter 1. Then, when you
 * encounter the larger problem in chapter 5, you can jump to chapter 1 to
 * use the steps defined there to solve the subproblem and then jump back to
 * chapter 5 to finish solving your main problem.
 *
 * A *function call* tells the CPU to jump from the current line in the current
 * function to execute another function.
 *
 * The function initiating the call is the *caller*, the function being
 * *called* is the *callee*. A function call can also be called an *invocation*
 * and it is common to say "invoke the function".
 */

// Definition of a user-defined function doPrint()
// doPrint() is the called function in this example
void doPrint()
{
    std::cout << "    In doPrint()\n";
}

void doB()
{
    std::cout << "        In doB()\n";
}

void doA()
{
    std::cout << "    Starting doA()\n";
    std::cout << "    Calling doB()...\n";
    doB();
    std::cout << "    Returned control to doA()\n";
    std::cout << "    Ending doA()\n";
}

// Definition of user-defined function main()
int main()
{
    // doPrint() example
    std::cout << "Starting main()\n";
    std::cout << "Calling doPrint()...\n";
    doPrint();
    std::cout << "Returned control to main()\n";
    std::cout << "Calling doPrint() again...\n";
    doPrint();
    std::cout << "Returned control to main()\n\n";

    // doA() example
    std::cout << "Calling doA()...\n";
    doA();
    std::cout << "Returned control to main()\n";

    std::cout << "Ending main()\n";

    return 0;
}

/**
 * Here we use print statements to show which order the statements in the
 * program execute in. This can also be a useful debugging technique for
 * beginners. Note that we can call doPrint() more than once.
 *
 * Also note that we called the function "doPrint" rather than just "print".
 * It is common practice to use verbs for function names so the code reads like
 * prose. Similarly, it is common practice to use nouns for variable names.
 *
 * Note that nested functions are not supported in C++. The following code will
 * not compile:
 *
 * #include <iostream>
 *
 * int main()
 * {
 *      void foo() // This is illegal!
 *      {
 *          std::cout << "foo\n";
 *      }
 *
 *      foo(); // function call to foo()
 *
 *      return 0;
 * }
 */