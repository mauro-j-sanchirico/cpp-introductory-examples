#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";

    int num{};
    std::cin >> num;

    // Here we use an expression to multiply the number inline. If all we need
    // to do is print the number, it is preferable to multiply it inline rather
    // than create another variable or reuse the first variable.
    std::cout << "Double that number is: " << num * 2 << '\n';

    return 0;
}

/**
 * Tips:
 *
 * It is often necessary to write a program once as a prototype to learn how to
 * rewrite the production version correctly.
 *
 * The primary objective of programming is to make your program work. Once the
 * program is working though, your job is not finished. The program needs to be
 * made well-structured, reusable, and maintainable. The program will need to
 * run on other systems and be used and modified by other people.
 *
 * When writing a new program, first make the program work. Do not fall into
 * anti-patterns like premature productionization or premature optimization.
 * Premature productionization is when advanced architectural elements, like
 * complex object oriented structures, messaging layers, and other abstractions
 * are added before the program is fully designed and before it is clear these
 * abstractions are needed. Premature optimization is when non-intuitive code
 * changes are made early in a program's design to enhance runtime or memory
 * footprint when it is not yet clear these optimizations are needed.
 *
 * Once the program is working, refactor the code to make it more readable and
 * maintainable by other developers on your team, and by your future self.
 * Remove any debugging code or dead code no longer necessary. Focus on making
 * the program more robust. Check for error cases or exceptional conditions and
 * handle them appropriately. Check if any sections of the program can be made
 * more concise. Ensure all applicable best practices are followed. Once those
 * considerations are accounted for, seek to add abstractions to generalize the
 * program and enable it to integrate with larger systems. Optimize runtime and
 * memory performance if required.
 */