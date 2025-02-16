/**
 * Preprocessor
 *
 * Before compilation, each C++ file goes through a *preprocessing* phase.
 * In this phase, a *preprocessor* makes changes to the text in the file.
 * The preprocessor does not actually modify the original code though and
 * these changes are made under the hood as part of the overall process of
 * building your project. The output of the preprocessor is called a
 * *translation unit*. The entire process of preprocessing, compiling and
 * linking is called *translation*.
 *
 * The preprocessor looks for *preprocessor directives* which are used to
 * control what changes it will make to the source file. Preprocessor
 * directives start with a # and end with a newline (not a semicolon).
 *
 * The #include directive tells the preprocessor to replace the line with
 * the contents of the file named in the angle brackets, i.e., the <>, after
 * it.
 *
 * The #define directive is used to create a *macro*. A macro is a rule that
 * defines how input text is converted into replacement output text. There are
 * two basic macros: object-like macros and function-like macros.
 *
 * Function-like macros act like functions and serve a similar purpose. They
 * are generally considered unsafe. Usually, a normal function can be used
 * instead. However, there are some valid use cases for function-like macros
 * such as debugging and some optimizations.
 *
 * Object-like identifiers are used like variables and are often used to
 * substitute text or as a switch to control whether or not some code is
 * compiled.
 *
 * An object-like macro with substitution text is defined like:
 *
 *     # define IDENTIFIER substitution_text
 *
 * This used to define constants in some legacy code but is generally avoided
 * in modern C++.
 *
 * An object-like macro without a substitution is defined like:
 *
 *     # define IDENTIFIER
 *
 * Macros of this form are used as switches to control compilation or as
 * a means of keeping track of files that have been included (since including
 * the file defines the identifier). This is common in modern C++.
 *
 * In the example below we see #ifdef and #ifndef used to check if macros of
 * this form are defined.
 *
 * Note that the preprocessor does NOT understand C++ constructs like
 * functions. Instead, the preprocessor resolves directives before compilation
 * from top to bottom in each file.
 *
 * IMPORTANT: a preprocessor directive defined in another file has no effect
 * on other files UNLESS those files are included in the current file with
 * a #include directive. This is important for understanding header guards
 * (next).
 */

// This will tell the preprocessor to substitute the contents of iostream here
#include <iostream>

// This is a macro with substitution text - not good practice in modern C++!
#define MY_NAME "Alex"

// Define a macro with no substitution text
#define PRINT_JOE

int main()
{

#ifdef PRINT_JOE          // Here we use ifdef to check if PRINT_JOE is defined
    std::cout << "Joe\n"; // Will be compiled if PRINT_JOE is defined
#endif                    // This ends the #ifdef

#ifdef PRINT_BOB
    std::cout << "Bob\n"; // Will be excluded since PRINT_BOB is not defined
#endif

#ifndef PRINT_ALICE
    std::cout << "Alice\n"; // Will be compiled because Alice is NOT defined
#endif

    // Prints "My name is: Alex" - not good practice in modern C++!
    std::cout << "My name is: " << MY_NAME << '\n';

#if 0
    /**
     * This is a multiline comment. Having it here can make it difficult to
     * comment out multiple lines when debugging.
     */
    std::cout << "Inside #if 0\n";
    std::cout << "These lines will not get printed\n";
#endif

#if 1
    /**
     * This is a multiline comment. Having it here can make it difficult to
     * comment out multiple lines when debugging.
     */
    std::cout << "Inside #if 1\n";
    std::cout << "These lines WILL get printed\n";
#endif

    return 0;
}