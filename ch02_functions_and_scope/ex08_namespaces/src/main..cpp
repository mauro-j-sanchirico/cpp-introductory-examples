/**
 * Naming Conflicts
 *
 * As a program gets larger, the chances there will be multiple identifiers
 * with the same name get larger. If two identifiers share the same name in a
 * file, the compiler will report an error. If two identifiers share the same
 * name across files the linker will report an error. These errors are called
 * *naming collisions* or *naming conflicts*.
 *
 * Managing Naming Conflicts
 *
 * C++ enables managing naming collisions with scope and namespaces. We have
 * already seen scope in basic examples. Variables are destroyed when the
 * local scope they are declared in ends. Their identifiers can then be reused
 * in other local scopes. More generally, a *scope region* is an area of
 * code where all declared identifiers are considered distinct from identifiers
 * declared in other scopes.
 *
 * A namespace provides another type of scope region that is used entirely for
 * disambiguation. While some local scopes (like function bodies) are used for
 * other purposes, a namespace provides a means for declaring a *namespace
 * scope* that is used to deconflict identical names. Only declarations and
 * definitions can appear in the scope of a namespace (not executable
 * statements). A function can be defined in a namespace though, and the
 * function body can contain executable statements.
 *
 * Global Namespace
 *
 * Any identifier not part of another namespace (inside a function body, class,
 * or other namespace) is implicitly part of the *global namespace* (also
 * called the global scope).
 *
 * The std Namespace
 *
 * When C++ was originally designed, all of the identifiers in the C++
 * standard library (e.g., cin and cout) were available to be used as part of
 * the global namespace (i.e., they did not need the std:: prefix). This meant
 * that as identifiers were added to the standard library, there was a chance
 * they could conflict with user defined identifiers. This means that if a
 * program worked in one version of C++, there was a chance it would not work
 * in a later version of C++ because new identifiers could be added to the
 * global namespace. To solve this problem, the std namespace was introduced
 * to deconflict identifiers in the standard library with user defined
 * identifiers.
 *
 * For this reason, it is generally considered bad practice to use
 * "using namespace std;" to avoid having to type the std:: prefix. Among other
 * reasons, this is because if this code is reused in a new version of C++
 * there is a chance that "using namespace std;" could pull identifiers added
 * to the std namespace into the global scope where they might conflict with
 * user defined identifiers. As a best practice, avoid these consequences by
 * not using "using namespace std;" in the global namespace in production code.
 * However, you might see "using namespace std;" in academic examples where a
 * small number of identifiers (like x and y) are used which will not conflict
 * with identifiers in the std namespace. In these, and similar non-production
 * cases, it is ok to use "using namespace std;".
 *
 * Scope Resolution Operator
 *
 * Formally, the "::" used in std::cout and std::cin is called the *scope
 * resolution operator* and it is used to access a variable in a named scope.
 * When an identifier includes a namespace prefix, it is called a *qualified
 * name*.
 */

#include <iostream>

// foo() is defined in the global scope and x is defined in the scope of foo()
void foo(int x)
{
    std::cout << x << '\n';
} // x goes out of scope here

int main()
{ // begin the scope for main()
    foo(5);

    // This is not the same x that is defined in foo
    int x{6}; // x is defined within the scope of main

    std::cout << x << '\n';

} // main()'s x goes out of scope here
// foo, main, (and std::cout) go out of scope here (the end of the file)