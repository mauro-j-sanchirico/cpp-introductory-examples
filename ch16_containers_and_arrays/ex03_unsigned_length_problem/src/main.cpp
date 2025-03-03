/**
 * Unsigned Length and Subscript Problem
 *
 * When the containers in the C++ standard library were designed (in the late
 * 1990s), the designers chose to make the length and indices unsigned since
 * it doesn't make sense to have a negative index and because the extra bit
 * provides double the number of possible indicies. In a signed 16 bit number,
 * one of the bits is for the sign, leaving only 15 bits for the number, i.e.,
 * only half as many values. This was important when memory wasn't as cheap
 * as it is now and when processors didn't support 32 and 64 bit variables.
 *
 * However, this ended up being a choice of consequence since it now forces
 * programmers to mix signed and unsigned values in calculations and the extra
 * bit is less important on modern systems than it was in the 1990s. Since
 * moving from a signed to an unsigned value can potentially cause hard to
 * catch errors or undefined behavior, an argument can be made that the extra
 * bit is not worth the trade for the increased risk of error on modern
 * systems.
 *
 * Unsigned Arithmetic Review
 *
 * To understand this, let's briefly review signed vs. unsigned integers.
 * An unsigned integer uses all of its bits to represent its values. So, an
 * unsigned 8-bit integer has 2^8 values, i.e., can take on values from 0 to
 * 255. By contrast, a signed 8-bit integer has 2^8 values, but since one
 * bit is reserved for the sign, its values range from -128 to 127.
 *
 * If an unsigned value goes out of range, it will wrap back around to the
 * begining. So, in unsigned arithmetic, 255 + 1 will wrap around to 0, 255 + 2
 * will wrap around to 1, and 255 + 3 will wrap around to 2, and so on.
 *
 * Most noteworthy for this discussion, unsigned integer arithmetic will also
 * wrap around at 0. So, 0 - 1 will wrap around to 255, 0 - 2 will wrap around
 * to 254, and so on.
 *
 * When using signed numbers, we have a lot of room for error on both sides of
 * zero before we start getting counter-intuitive wrap-around behavior.
 * However, when using unsigned numbers, if we initialize the number to a value
 * close to 0 and then subtract a value that seems reasonable, we will get
 * counter-intuitive wraparound behavior. This is one of the reasons some
 * developers will avoid using unsigned integers as a best practice.
 *
 * This behavior can arise in unexpected situations when mixing signed and
 * unsigned integers. **If an operation contains both a signed and unsigned
 * integer, the result will usually be unsigned.** See the examples below
 * where this causes problems with arithmetic and comparisons.
 *
 * Bad behavior with unsigned integers can also occur if they are used to
 * govern the number of times something happens. Imagine a function which
 * uses an argument to do something N times. If the argument is unsigned and
 * the function is called with N = -1, something will happen many, many times.
 * For a user, this will cause a program to hang.
 *
 * For these reasons, it is a key best practice to favor signed numbers over
 * unsigned numbers for holding quantities, even when those quantities should
 * be non-negative! Do not mix signed and unsigned numbers.
 *
 * Use unsigned numbers when the wrap-around behavior is desired (e.g., when
 * writing some encryption or random number generation algorithms), when
 * performing low-level bit manipulation, and when programming embedded systems
 * where saving a bit from being wasted on an unused sign is required for
 * performance.
 *
 * Sign Conversion Impacts to Subscripting
 *
 * Sign conversions are *narrowing* conversions. A sign conversion will narrow
 * the signed variable to an unsigned variable which may cause wrap-around
 * behavior.
 *
 * The only exception is when the signed variable is a constexpr. For a
 * constexpr, the compiler can guarantee the conversion is safe or halt the
 * compilation process.
 *
 * This is important to understand since we may use a signed variable to
 * determine which subscript of a container to access, which is where problems
 * may arise!
 *
 * Introducing size_type
 *
 * STL containers define size_type as a type alias for the type of the length
 * of the container and as a type alias for the type of its subscripts.
 * Containers use an alias here since different containers may have different
 * types of subscript indices and lengths based on their size and
 * implementation. size_type is usually an alias for std::size_t, which itself
 * is an alias for the specific flavor of unsigned integer that the container's
 * implementation needs (e.g., long unsigned int or long long unsigned int).
 *
 * We see examples below of getting the length of a vector using the size()
 * member function and using the more generic std::size() function.
 *
 * Accessing Array Elements with  [] vs. .at()
 *
 * The subscript operator enables the fasted access to array elements by
 * performing no bounds checking. This place all responsibility on the user
 * code to avoid accessing array elements out of bounds! This is one of the
 * ways C++ enables speed at the expense of placing responsibility for safety
 * in the hands of the programmer.
 *
 * If bounds checking is desired, the .at() member function can be used instead
 * of the [] operator. Though .at() is safer, it is generally preferred to use
 * [] instead as long as bounds can be checked before indexing.
 */

#include <iostream>
#include <vector>

void doSomethingNTimes(unsigned short int n)
{
    int counter = 0;
    for (int i = 0; i < n; i++)
    {
        // Code here will execute too many times for negative n!
        counter++;
    }
    std::cout << "This code ran " << counter << " times!\n";
}

int main()
{
    /**
     * Review of unsigned integer dangers
     *
     * These code snippets show the dangers of using unsigned integers and put
     * the unsigned length problem into context.
     */

    std::cout << "Unsigned integer dangers:\n";

    // Initialize x to the largest 16 bit value possible
    unsigned short x{65535};

    x += 1; // Increment x by 1

    std::cout << "After incrementing, x = " << x << '\n';

    x = 0;

    x -= 1;

    std::cout << "After decrementing, x = " << x << '\n';

    // Will trigger a warning - try it with -Wsign-conversion turned on!
    x = -80;

    std::cout << "After setting x to a negative value, x = " << x << '\n';

    // Mixing signed and unsigned integers
    unsigned int u{2};
    signed int s{3};
    // Will trigger a warning - try it with -Wsign-conversion turned on!
    std::cout << "Unsigned - signed integer: " << u - s << '\n';

    // Signed and Unsigned comparison dangers
    s = -1;
    u = 1;

    /**
     * This will throw a warning or not compile with some compiler settings:
     *
     * if (s < u) // -1 implicitly converted to unsigned value 4294967295!
     * {
     *     std::cout << "-1 is less than 1\n";
     * }
     * else
     * {
     *     std::cout << "1 is less than -1\n";
     * }
     */

    // The loop in this function will run too many times!
    // Will also trigger a warning - try it with -Wsign-conversion turned on!
    doSomethingNTimes(-1);

    std::cout << "\nSize examples:\n";

    std::vector prime{2, 3, 5, 7, 11};

    std::cout << "Length of prime using .size(): " << prime.size() << '\n';
    std::cout << "Length of prime using std::size: " << std::size(prime) << '\n';

    /**
     * If we want to store the length of a variable in a signed type to avoid
     * dealing with unsigned variables (since this is a best practice) in past
     * versions of the C++ language we would have had to use a cast:
     */
    int length{static_cast<int>(prime.size())};
    std::cout << "Length as an int: " << length << '\n';

    /**
     * To solve the unsigned length problem, C++20 introduces std::ssize()
     * as a non-member function which returns the length as a signed integer
     * type.
     *
     * Note we use auto here to let the compiler deduce which size of signed
     * int we need. This avoids a narrowing conversion in size while using
     * std::ssize() avoids a narrowing conversion in sign. The {} avoids
     * copy-initialization for a fully modern means of getting the size of a
     * vector!
     */
    [[maybe_unused]] auto signed_length{std::ssize(prime)};

    // [] vs. .at()
    std::cout << prime[3] << '\n'; // print the value of element with index 3 (7)
    std::cout << prime[9] << '\n'; // invalid index (undefined behavior)

    std::cout << prime.at(3) << '\n';

    try
    {
        std::cout << prime.at(9) << '\n'; // Throws an exception
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Caught std::out_of_range_error: " << e.what() << '\n';
        std::cout << "Continuing...\n";
    }

    std::cout << "\nVector access examples:\n";

    /**
     * Methods of Accessing Vector Elements
     *
     * Depending on how we access vector elements, we might need to handle
     * type conversions to work with signed integers and then use them to
     * access array elements at unsigned subscripts.
     *
     * 1. (OK) Accessing at a constexpr signed int: Since narrowing conversions
     * are safe for constexpr, we can use a constexpr and no additional
     * conversion is required on our part. The compiler takes care of the rest.
     */
    constexpr int constexpr_index{3};
    // constexpr implicitly converted to size_t by compiler
    std::cout << prime[constexpr_index] << '\n';

    /**
     * 2. (OK) Indexing with a non-constexpr value using size_t: Since we may
     * not know the value of the subscript we want to access at compile time,
     * we can use size_t to specify the type of the value we want to access.
     */
    std::size_t size_t_index{3};
    std::cout << prime[size_t_index] << '\n';

    /**
     * 3. (Bad) Attempting to use a signed integer: using an unsigned type here
     * goes against the best practices motivated above. We could attempt to use
     * a signed int, but the compiler may flag a warning or not compile
     * depending on our settings. Even if the following code compiles it will
     * be problematic if int_index is set to a negative value.
     *
     * This third method is listed here for completeness but is not good
     * practice and should not be used.
     */
    int int_index{3};
    // Will trigger a warning - try it with -Wsign-conversion turned on!
    std::cout << prime[int_index] << '\n';

    /**
     * 4. (OK but still dangerous) Using a signed integer to access the raw
     * C-style array the vector elements are stored in: we can access the raw
     * C-style array the vector elements are stored in using the .data() member
     * function. Note this will still compile even with -Wsign-conversion on.
     * However, we still run the risk of our signed integer causing us to
     * access an out of bounds index.
     */
    std::cout << prime.data()[int_index] << '\n';

    /**
     * If it seems like there is no great way to use integers to access the
     * elements of an array, that is correct! As a best practice, avoid
     * using integers to access the elements of an array unless absolutely
     * necessary. Instead, use range based for loops and iterators where
     * possible.
     */

    return 0;
}