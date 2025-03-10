/**
 * Dangling Captured Variables
 *
 * When using lambdas, if a variable captured by reference dies before the
 * lambda, the lambda will be left holding a dangling reference.
 *
 * The call to makeWalrus() creates a temporary std::string from the string
 * literal "Roofus". The lambda in makeWalrus() captures the temporary string
 * by reference. The temporary string dies at the end of the full expression
 * containing the call to makeWalrus(), but the lambda sayName still references
 * it past that point. Thus, when we call sayName, the dangling reference is
 * accessed, causing UB.
 *
 * WARNING: capturing variables by reference is dangerous, especially with a
 * default reference capture since you might accidentally capture a reference
 * that goes out of scope before the last call to the lambda, leading to UB.
 *
 * Source: https://www.learncpp.com/cpp-tutorial/lambda-captures/
 */

#include <iostream>
#include <string>

// returns a lambda
auto printNumber(const int &n)
{
    return [&]()
    {
        std::cout << "Your number is " << n << '\n'; // UB
    };
}

int main()
{
    // Dynamically allocate an integer
    int *ptr{new int};
    *ptr = 7;

    /**
     * This call passes printNumber a pointer that can become a dangling
     * reference. This is very dangerous!
     */
    auto sayNumber{printNumber(*ptr)};

    // Delete the integer before calling sayNumber()
    delete ptr;

    // Call the lambda function that uses the dangling reference
    sayNumber(); // prints garbage!
    sayNumber();
    sayNumber();
    sayNumber();

    return 0;
}