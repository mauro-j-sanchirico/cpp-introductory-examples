#include <iostream>

int main()
{
    /**
     * Variables
     */

    int x;    // Define an integer named x
    int y, z; // Define two integer variables

    /**
     * Assignment
     */

    // Note that the = operator is an assignment operator, not an equals sign
    x = 0;
    y = 0;
    z = 0;

    std::cout << x << y << z << std::endl;

    /**
     * Variable Initialization
     */

    // A basic initialization
    int width; // Define an integer, width
    width = 5; // Set width to 5
    std::cout << width << std::endl;
    width = 7;
    std::cout << width << std::endl;

    /**
     * Initialization is surprisingly complex in C++. There are 5 types of
     * basic initialization.
     *
     * 1) Default-initialization
     * 2) Traditional: copy-initialization
     * 3) Traditional: direct-initialization
     * 4) Modern: direct-list-initialization
     * 5) Modern: value-initialization
     *
     * Other more advanced forms of initialization include:
     *  - Aggregate-initialization
     *  - Copy-list-initialization
     *  - Reference-initialization
     *  - Static-initialization
     *  - Zero-initialization
     */

    // Default-initialization
    //
    // This will leave the variable with a garbage value and will not compile
    // with all warnings on.
    // int a;

    // Traditional: copy-initialization
    //
    // Inherited from C; copies the value on the right hand side (RHS)
    // Copy initialization is also used when passing arguments to a function by
    // value or when return from a function by value.
    // Falling out of favor in modern C++ due to inefficiency (though the
    // compiler will fix most issues in > C++17).
    int b = 5;

    // Traditional: direct-initialization
    //
    // Introduced to allow more efficient instantiation of complex objects.
    // Generally superseded by direct-list-initialization in modern C++, though
    // still has some use cases.
    int c(6);

    // Modern: direct-list-initialization
    //
    // Introduced because copy-initialization can be hard to differentiate from
    // copy assignment. Direct-initialization can be hard to differentiate from
    // function-related operations (both use parentheses). List-initialization
    // works in almost all cases and provides an unambiguous syntax.
    //
    // **NOTE**: WHEN WE SEE CURLY BRACES, WE KNOW WE'RE LIST-INITIALIZING AN
    // OBJECT.
    //
    // List-initialization also provides a way to initialize objects that hold
    // a list of values, such as a vector or list.
    int d{7};

    // One of the primary benefits of list-initialization is that if a
    // "narrowing" conversion is made (i.e., a conversion that initializes
    // a variable using a value that it cannot safely hold) the compiler is
    // required to produce a diagnostic (compilation error or warning).

    // Example:
    //
    // An integer can only hold non-fractional values. Initializing an int with
    // a value of 4.5 requires the compiler to convert 4.5 to a value an int
    // can hold. This is a narrowing conversion, since the fractional part of
    // the value will be lost!

    // This will not compile since list-initialization checks against
    // narrowing conversion.
    // int w1{4.5};

    // This will compile since copy-initialization does not perform checking
    // against narrowing conversion.
    int w2 = 4.5;

    // This will compile since direct initialization does not perform checking
    // against narrowing conversion.
    int w3(4.5);

    std::cout << w2 << std::endl;
    std::cout << w3 << std::endl;

    // Modern: value-initialization
    //
    // When a variable is initialized using an empty set of braces a special
    // form of list-initialization called value-initialization takes place. In
    // most cases, value initialization will implicitly initialize the variable
    // to zero (or whatever value is the closest to zero for the given type).
    // This is called zero-initialization.
    //
    // For class objects, value-initialization can initialize the object to a
    // predefined default value which need not be zero.
    int e{};

    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;

    // **IMPORTANT**: Use direct-list-initialization or value-initialization to
    // initialize your variables. Bjarne Stroustrup (creator of C++) and Herb
    // Sutter (C++ expert) also recommend using list-initialization.

    // Use direct-list-initialization when you're actually using the initial
    // value. Use value-initialization when the value will be immediately
    // replaced.

    // Always initialize your variables! Rare exceptions include performance
    // critical code where many variables are used.

    /**
     * Multiple Initialization
     */

    // This is bad practice
    int i, j;
    int k(3), l(4);
    int m{5}, n{6};
    int o{}, p{};

    i = 1;
    j = 2;

    std::cout << i << j << k << l << m << n << o << p << std::endl;

    /**
     * C++17 [[maybe_unused]] attribute
     */

    // The compiler will throw a warning for an unused variable. If warnings
    // are treated as errors, the program will not compile. If there is a valid
    // reason to have unused variables (for example, a list of many physics
    // constants) then the [[maybe_unused]] attribute can be used.

    [[maybe_unused]] double pi{3.14159};
    [[maybe_unused]] double gravity{9.8};
    [[maybe_unused]] double phi{1.61803};

    std::cout << pi << std::endl;
    std::cout << phi << std::endl;

    // The compiler will not warn about gravity not being used

    return 0;
}