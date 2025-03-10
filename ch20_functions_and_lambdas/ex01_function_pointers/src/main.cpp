/**
 * Function Pointers
 *
 * A pointer is a variable that holds the address of another variable. A
 * *function pointer* is a variable that holds the address of a function.
 *
 * Functions are stored at an assigned memory address and when we invoke them
 * with the `()` operator, we ask the CPU to *jump* to the address in memory
 * where the function lives.
 *
 * This is analogous to solving a problem in chapter 5 of a book by jumping to
 * a solution to a subproblem that is part of that larger problem introduced
 * in an early chapter, invoking the method presented there, and then returning
 * to back to the original problem to finish solving it.
 *
 * Function pointers allow passing functions to functions and storing
 * references to functions in variables. This has many applications but one of
 * the most common is implementing callbacks, i.e., letting the user pass a
 * function to pre-implemented function to define some of its implementation.
 *
 * Function pointer syntax can be ugly and confusing. It is best practice in
 * modern C++ to simplify function pointer use by using std::function and
 * letting the compiler infer types with auto.
 */

#include <functional>
#include <iostream>

int foo()
{
    return 5;
}

int goo()
{
    return 6;
}

int take_int_return_int(int x)
{
    return x;
}

double return_double()
{
    return 6.0;
}

void name_conflict(int x)
{
    std::cout << "name_conflict(int): " << x << '\n';
}

void name_conflict(int x, int y = 10)
{
    std::cout << "name_conflict(int, int): " << x << ' ' << y << '\n';
}

double square(double x)
{
    return x * x;
}

double transform(double x, double (*transform_function)(double) = square)
{
    return transform_function(x);
}

/**
 * We can use type aliases to make function pointers easier to read.
 */
using TransformFunction = double (*)(double);
double transform2(double x, TransformFunction transform_function = square)
{
    return transform_function(x);
}

/**
 * We can use std::function with type aliasing for the most readable
 * implementation of a callback in modern C++.
 */
using TransformFunction3 = std::function<double(double)>;
double transform3(double x, TransformFunction3 transform_function = square)
{
    return transform_function(x);
}

int main()
{
    auto x = foo();

    // This will not compile with -Werror=address
    // std::cout << foo << '\n';

    /**
     * Tell the compiler explicitly to interpret as a generic pointer
     * This cast is not supported on all platforms - behavior is implementation
     * defined.
     */
    std::cout << "Function address: " << reinterpret_cast<void *>(foo) << '\n';

    // This prints the variable where we stored the value returned
    std::cout << x << '\n';

    /**
     * The syntax for a non-const function pointer is ugly...
     *
     * This line creates a function pointer to a function that returns an
     * integer. The curly braces initialize it to the address of the function
     * foo().
     */
    int (*my_function_pointer1)(){&foo};

    // Create an uninitialized function pointer
    int (*my_function_pointer2)();

    // Initialize it to goo
    my_function_pointer2 = &goo;

    // By default, cout will interpret these as bools...
    std::cout << "By default, cout will interpret these as bools...\n";
    std::cout << "Function pointer 1: " << my_function_pointer1 << '\n';
    std::cout << "Function pointer 2: " << my_function_pointer2 << '\n';

    std::cout << "\nUsing a cast we can print the values of the pointers...\n";
    std::cout << "Function pointer 1: " << reinterpret_cast<void *>(my_function_pointer1) << '\n';
    std::cout << "Function pointer 2: " << reinterpret_cast<void *>(my_function_pointer2) << '\n';

    // Common mistake - this will try to assign the return value to the pointer
    // my_function_pointer1 = goo()

    /**
     * Function pointer initializations must match the function signature in
     * return type and parameter type.
     */
    int (*fp1)(int){&take_int_return_int}; // Good
    double (*fp2)(){&return_double};       // Good

    // Bad:
    // [[maybe_unused]] int (*fp3)(){&take_int_return_int};

    /**
     * The address of (&) operator is technically optional. C++ will implicitly
     * convert the function to a function pointer.
     */
    [[maybe_unused]] int (*fp3)(int){take_int_return_int}; // No error

    /**
     * Functions can be called by *explicit dereference* using the dereference
     * operator (*) or by *implicit dereference* using the name of the function
     * pointer. Implicit dereference is analogous to normal function calls
     * since function names are pointers to functions.
     */

    // Explicit dereference
    (*fp1)(2);
    (*fp2)();

    // Implicit dereference
    fp1(2);
    fp2();

    /**
     * Function pointers can be NULL. Dereferencing a null pointer leads to
     * undefined behavior. It is a best practice to check to make sure a
     * function pointer is not NULL before using it if working with raw
     * function pointers.
     */

    if (fp1)
    {
        fp1(2);
    }

    /**
     * Default arguments do not work for functions called through function
     * pointers. This means if two functions have the same name and one has
     * default arguments, and a function pointer is created to the shared
     * name of both functions that function pointer will resolve to the
     * function with no default arguments as long as it matches its signature.
     */
    using vptr = void (*)(int);
    vptr pi{name_conflict};

    std::cout << "\nThis will resolve to the function with no default arguments...\n";
    pi(1);

    // We can use a cast to disambiguate the functions
    std::cout << "\nThis will also resolve to the function with no default arguments...\n";
    static_cast<void (*)(int)>(name_conflict)(1);

    /**
     * Functions used as arguments to other functions are called *callback
     * functions*. Callbacks are useful when a function's operation needs to be
     * further specified by a user-defined function. This is common in
     * implementation of sorting and other algorithms. This design paradigm
     * is useful when there are many variants of a callback a user might want
     * to define AND the callback is easier to write than the base function
     * itself. This means having the base function available saves the user
     * from having to rewrite it without sacrificing flexibility.
     */
    double y{2};
    std::cout << "\nTransformed y...\n";
    std::cout << transform(y, square) << '\n';

    /**
     * Since we provided a default function, we don't need to specify the
     * callback function explicitly if we want to use the default.
     */
    std::cout << "\nTransformed y by default function...\n";
    std::cout << transform(y) << '\n';

    std::cout << "\nTransformed y with function using type aliases...\n";
    std::cout << transform2(y) << '\n';

    /**
     * The standard library provides std::function in the <functional> header
     * to provide standard tools for function pointers.
     */
    std::function<int()> fp4{&foo};
    fp4 = &goo;
    std::cout << "\nCalled foo() using std::function...\n";
    std::cout << fp4() << '\n';

    /**
     * Class Template Argument Deduction (CTAD) (introduced in C++17) allows
     * the compiler to infer the template arguments.
     */
    std::function fp5{&foo};

    std::cout << "\nCalled foo() using std::function with CTAD...\n";
    std::cout << fp5() << '\n';

    std::cout << "\nTransformed y using std::function and type aliases...\n";
    std::cout << transform3(y) << '\n';

    /**
     * Finally, auto can be combined with std::function and CTAD for the
     * cleanest function pointer syntax using modern C++.
     */
    auto fp6{&foo}; // Let the compiler infer the type and template!
    std::cout << "\nCalled foo() using auto...\n";
    std::cout << fp6() << '\n';
}