/**
 * Building Programs with Multiple Files
 *
 * It is helpful to break up a large program into multiple files. This enables
 * individual files to be reused and helps keep code organized. In a
 * professional setting, different files might be worked on by different teams
 * as part of a larger organization.
 *
 * The compiler compiles each file individually into an object file. It does
 * not "remember" anything from any of the previous files. This allows
 * the compilation process to treat source files in any order, ensures that
 * only the file changed needs to be recompiled (recompilation times can be
 * long in large programs) and reduces conflicts between files. The linker is
 * then used to link the objects together into a single program that can be
 * executed.
 *
 * Since the compiler treats each file individually, any file that uses
 * functions that require a particular #include directive needs to have that
 * #include directive. It is not enough to only use the #include directive
 * in main.cpp.
 *
 * When an identifier (variable, function, etc.) is invoked in an expression,
 * the identifier must be connected to its definition. If the compiler has not
 * seen a definition or a declaration is will throw an error. If the definition
 * exists in a different file, it is the responsibility of the linker to find
 * it and connect it to the declaration. If the linker cannot do this, (e.g.,
 * because the definition does not exist in any files provided to it) it will
 * issue an error. Understanding whether it was the compiler or linker that
 * issued an error and why the error was issued is helpful when debugging large
 * programs.
 */

#include <iostream>

/**
 * Forward declare add() so we can use it in main even though its definition is
 * in another file. Later, this will be done in a header file that we import.
 * For now, we will write the forward declaration manually.
 */
int add(int x, int y);

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';
    return 0;
}