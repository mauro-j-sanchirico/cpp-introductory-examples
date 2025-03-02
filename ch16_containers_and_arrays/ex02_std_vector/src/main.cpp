/**
 * Introduction to std::vector
 *
 * std::vector is one of the means by which C++ supports arrays. The vector
 * header implements std::vector as a class template, which means user code
 * can specify the type of element the vector will hold by specifying a type
 * in the angle brackets, e.g.,
 *
 * std::vector<int> x{};
 *
 * Vector are initialized using the list initialization syntax (i.e., with {}).
 * An added benefit of list initialization syntax is that it provides a common
 * syntax for initialization that works safely for vectors and individual
 * variables.
 *
 * Most containers support a *list constructor* which allows initializing the
 * container with a list of values. The list constructor:
 *    - Ensures the container has enough storage to hold all the values
 *      provided to the initializer
 *    - Sets the length of the container to the number of elements in the
 *      initializer list
 *    - Initializes the elements to the values in the initializer list (in
 *      sequential order)
 *
 * Using list initialization is a key best practice in modern C++.
 *
 * Accessing Elements using the Subscript ([]) Operator
 *
 * In C++, the most common way to access array elements is with the subscript
 * operator, i.e., with square brackets: []. The subscript operator accepts
 * an integer value (formally called a *subscript* or less formally called an
 * *index*) and allows us to access the element at the corresponding position.
 *
 * In C++ and most programming languages, subscripts start counting at 0 rather
 * than starting at 1. This means subscript 1 gives us the second element.
 * Subscript 0 gives us the first.
 *
 * Under the hood, indices are a *distance* offset from the start of an array.
 * This means that index 0 is referring to the start of the array, since the
 * start of the array is distance 0 from where the array begins in memory.
 *
 * Subscript Out of Bounds
 *
 * Be warned that no checking is performed to make sure that your subscript is
 * in bounds. This is for performance reasons - it is up to you to expend CPU
 * cycles to perform these checks if you need them. Keep in mind that a common
 * mistake new programmers make is to iterate up to index N for an array
 * having N elements. Since we start counting at 0, an array with N elements
 * has indices from 0 to 1. Accessing elements outside the bounds of an array
 * results in undefined behavior!
 *
 * Contiguous Storage
 *
 * Elements of arrays are stored contiguously in memory. This means adjacent
 * element will be adjacent in memory. This facilitates fast *random access*,
 * i.e., ability to access any element of an array we want with the same O(1)
 * time complexity. This is because, since elements are adjacent, the compiler
 * can do some basic math to determine the address of the element that needs
 * to be accessed.
 *
 * Creating a Vector of a Specific Length
 *
 * If we know how many elements we need in advance, we can tell the compiler
 * to reserve that much memory in a vector. One was to do this is using direct
 * initialization.
 *
 * std::vector<int> data(10); // Initialize a vector with 10 elements
 *
 * Note: this is different than the following
 *
 * std::vector<int> data{10};
 *
 * This seems ambiguous, as if it could be interpretted as a vector with 10
 * elements value initialized to 0 (like data(10)) or as if it could be
 * interpretted as a vector with one element list initialized to 10.
 *
 * In this case, {10} is interpretted as a list constructor, and a vector with
 * one integer element of value 10 is created. List constructors take
 * precedence over value initialization in this case. Note: this is the
 * exception in C++. In most cases, ambiguous class type definitions matching
 * more than one constructor will cause a compiler error.
 *
 * Due to ambiguity in initialization syntax, it is a best practice to use
 * direct initialization to initialize a vector with a specific number of
 * elements whose values are unknown.
 *
 * Disambiguation with Vectors in Mathematics
 *
 * According to Alexander Stepanov in "From Mathematics to Generic Programming"
 * the name vector in the STL was taken from earlier programming languages.
 * In programming, the term vector is sometimes viewed as inconsistent with
 * usage of the term in math. This is confusing to many new programmers who
 * might be familiar with math vectors. This is especially true for new
 * programmers used to thinking of vectors as geometrical objects in 2D or 3D
 * space. The fact that vectors in C++ can have many elements are are used to
 * store many different kind of data might seem foreign from the geometrical
 * meaning. However, in many advanced branches of mathematics, vectors can have
 * many elements. In some contexts related to differential equations, functions
 * can even be thought of as vectors having continuous elements. This is
 * consistent with the way vectors are often used in scientific computing, to
 * store the input and output values of a function or process.
 */

#include <iostream>
#include <vector>

int main()
{
    // List construction with explicit type specification
    std::vector<int> primes{2, 3, 5, 7};

    // Infers type (introduced in C++17)
    std::vector vowels{'a', 'e', 'i', 'o', 'u'};

    // Use the subscript operator to perform some operations
    std::cout << "\nInteger array subscripting example 1:\n";
    std::cout << "The first prime number is: " << primes[0] << '\n';
    std::cout << "The second prime number is: " << primes[1] << '\n';

    /**
     * This is undefined behavior!! It will compile and link but the values
     * will be garbage (they could be different every time) and this may even
     * cause the program to crash if we access protected memory. This is
     * because the subscript operator will blindly give us the element that is
     * offset the given distance from the start of the array, regardless of
     * whether or not that element is in the array. If the element is in memory
     * that is protected by the operating system, this will cause the program
     * to crash!
     */
    std::cout << "\nInteger array subscripting example 2:\n";
    std::cout << primes[5] << '\n';
    std::cout << primes[6] << '\n';
    std::cout << primes[7] << '\n';
    std::cout << primes[8] << '\n';

    /**
     * Since arrays (of any type) are contiguous in memory, this will show
     * adjacent memory addresses offset by the size of an element. Here we use
     * the reference operator (&) to get the addresses of the elements.
     */
    std::cout << "\nInteger array addressing example:\n";
    std::cout << "An int is " << sizeof(int) << " bytes\n";
    std::cout << &(primes[0]) << '\n';
    std::cout << &(primes[1]) << '\n';
    std::cout << &(primes[2]) << '\n';

    /**
     * Initialization examples: these example show the different ways to
     * initialize (and not initialize) a vector.
     *
     * This will cause a compiler error:
     */
    // std::vector<int> v1 = 10;

    /**
     * Direct initialization syntax - 10 is not an initializer list. This
     * matches explicit single argument constructor and makes a vector with
     * 10 elements initialized to 0.
     */
    std::vector<int> v2(10);

    /**
     * List initialization syntax - {10} is interpretted as an initialization
     * list and matches the list constructor, resulting in a vector with a
     * single element initialized to 10.
     */
    std::vector<int> v3{10};

    /**
     * Copy list initialization syntax - both of these forms of copy list
     * initialization syntax will instantiate a copy of the list in the
     * initializer and assign it to the vector.
     */
    std::vector<int> v4 = {10}; // Interpretted as initializer list
    std::vector<int> v5({10});  // Interpretted as initializer list

    /**
     * Empty list initialization syntax - both these will initialize an empty
     * vector.
     */
    std::vector<int> v6{};
    std::vector<int> v7 = {};

    std::cout << "\nVector initialization examples:\n";
    std::cout << "Size after v2(10) initialization: " << v2.size() << '\n';
    std::cout << "Size after v3{10} initialization: " << v3.size() << '\n';
    std::cout << "Size after v4{10} initialization: " << v4.size() << '\n';
    std::cout << "Size after v5({10}) initialization: " << v5.size() << '\n';
    std::cout << "Size after v6{} initialization: " << v6.size() << '\n';
    std::cout << "Size after v7 = {} initialization: " << v7.size() << '\n';

    /**
     * Note: when making vectors members of structs, the direct initialization
     * syntax is problematic. This is because direct initialization is not
     * allowed for member default initializers. The following will not compile:
     * struct Foo
     * {
     *     std::vector<int> v1(8);
     * };
     *
     * The following is one valid alternative:
     */

    struct Foo
    {
        std::vector<int> v{std::vector<int>(8)};
    };

    /**
     * Const and constexpr
     *
     * std::vector objects can be made const - this makes them unmodifiable.
     */
    const std::vector<int> prime{2, 3, 5, 6, 11}; // cannot be modified

    // Will not compile since prime is const
    // prime[2] = 10;

    /**
     * Note: the element type of a vector cannot be defined as const!
     * STL containers were not designed to have const elements. Since the STL
     * uses homogenous containers, if const elements are desired, the entire
     * vector should be made const.
     */

    return 0;
}