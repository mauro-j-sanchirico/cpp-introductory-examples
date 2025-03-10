/**
 * Lambdas
 *
 * *Lambda expressions* (also called *lambdas* or *closures*) are anonymous
 * functions. Lambdas allow defining functions inside other functions. The
 * main reasons to use lambdas are to define a function as close as possible
 * to where it is used and to avoid polluting the global namespace with
 * another function that will only be used once for a special purpose. A
 * common use case for lambdas is defining functions to be passed as
 * callbacks, e.g., to sorting or other algorithms.
 *
 * The syntax for lambdas is:
 *
 * [ captureClause ] ( parameters ) -> returnType
 * {
 *     statements;
 * }
 *
 * Rules for defining lambdas are as follows.
 *
 *      * The capture clause can be empty.
 *      * The parameter list can be empty if no parameters are needed. It can
 *        be omitted entirely if no return type is specified.
 *      * The return type is optional. If the return type is omitted, auto will
 *        be assumed and the return type will be inferred via type deduction.
 *
 * It is a best practice to define functions, variables, and objects as close
 * as possible to where they will be used, and in the smallest scope possible.
 * In the same way local variables give us the ability to do this, lambda
 * functions allow us to define functions right next to where they will be
 * used. The further away something is defined from where it is used, the
 * more likely its usage is to change without someone remembering to update
 * its definition!
 *
 * Lambda Details
 *
 * Lambdas do not explicitly have types, even when they are assigned a name.
 * The compiler gives a lambda a special type that is unique to that lambda
 * and not exposed to the programmer.
 *
 * Lambdas are not really functions, so there is no inconsistency with the rule
 * that there can be no nested functions in C++. Technically, a lambada is
 * a *functor*, which is an object that overloads the () operator to behave
 * like a function.
 *
 * When coupled with the algorithm and functional library, lambdas can enable
 * writing powerful code without needing to explicitly write any loops or
 * explicitly iterate through any arrays or vectors. Since iterating through
 * arrays and vectors ourselves can be an error prone operation, this can
 * help us write more readable and robust code.
 */

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <string_view>

/**
 * This is a regular function that checks if a string contains the substring
 * nut.
 */
bool containsNutRegularFunction(std::string_view str)
{
    return str.find("nut") != std::string_view::npos;
}

/**
 * There are 4 options to pass a lambda to a function as a parameter:
 *
 *     1. Use std::function (OK, best in C++17).
 *     2. Use a function template (OK, can have lower overhead than
 *        std::function if auto is not available). This can be harder to
 *        read.
 *     3. Using auto (best if using C++20). This is lowest overhead and
 *        most readable if auto is available.
 *     4. Using a raw pointer (bad in modern C++). This only works if the
 *        lambda has no captures.
 */

// Case 1: std::function parameter
void repeat1(int repetitions, const std::function<void(int)> &fn)
{
    for (int i{0}; i < repetitions; ++i)
    {
        fn(i);
    }
}

// Case 2: use a function template with a type template parameter
template <typename T>
void repeat2(int repetitions, const T &fn)
{
    for (int i{0}; i < repetitions; ++i)
    {
        fn(i);
    }
}

// Case 3: use auto
void repeat3(int repetitions, const auto &fn)
{
    for (int i{0}; i < repetitions; ++i)
    {
        fn(i);
    }
}

// Case 4: use a raw pointer
void repeat4(int repetitions, void (*fn)(int))
{
    for (int i{0}; i < repetitions; ++i)
    {
        fn(i);
    }
}

int main()
{
    /**
     * The most trivial lambda possible just needs an empty capture and no
     * statements. The return type can be omitted.
     */
    [] {}; // Trivial lambda

    constexpr std::array<std::string_view, 4> arr{"apple", "banana", "walnut", "lemon"};

    constexpr std::array<int, 6> arr2{1, 2, 3, 4, 5, 6};

    /**
     * Here we see how to use a lambda to pass a comparison function to
     * find_if. Below, we see the equivalent find_if using a regular function.
     * The [[maybe_unused]] attribute is only needed since we will use the
     * result from the lambda in this example and need the compiler to allow
     * us to leave the result from the regular function unused.
     */
    auto found{std::find_if(arr.begin(), arr.end(),
                            [](std::string_view str)
                            {
                                return str.find("nut") != std::string_view::npos;
                            })};
    [[maybe_unused]] auto foundRegularFunction{std::find_if(arr.begin(), arr.end(),
                                                            containsNutRegularFunction)};

    if (found == arr.end())
    {
        std::cout << "No nuts\n";
    }
    else
    {
        std::cout << "Found " << *found << '\n';
    }

    /**
     * To avoid having to write all our code on one line, we can define a
     * lambda in its own statement before using it.
     */

    // Bad: this is hard to read
    [[maybe_unused]] auto result1 = std::all_of(arr2.begin(), arr2.end(), [](int i)
                                                { return ((i % 2) == 0); });

    // Good: this is more legible and still keeps the definition closeby
    auto isEven{
        [](int i)
        {
            return (i % 2) == 0;
        }};

    auto result = std::all_of(arr2.begin(), arr2.end(), isEven);

    std::cout << "\nPrint 1 if all elements of arr2 are 0...\n";
    std::cout << result << '\n';

    /**
     * Lambdas can be stored for use in several ways:
     *
     *     * Using raw function pointers. This only works with an empty
     *       capture clause and there is no reason to resort to a raw function
     *       pointer in modern C++.
     *     * Using std::function. This works with empty or non-empty capture
     *       clauses. Pre-C++17 it is also necessary to explicitly define the
     *       type of function pointer since it will not be inferred using
     *       class template argument deduction (CTAD).
     *     * Using auto. This is the best practice in modern C++ (C++20).
     *
     * When available, auto is the most modern way to store a lambda and
     * provides the least chance of making an error. It has no overhead
     * compared to std::function.
     */

    // Regular function pointer. Only works with an empty capture clause.
    double (*addNumbers1)(double, double){
        [](double a, double b)
        {
            return a + b;
        }};

    std::function addNumbers2{
        [](double a, double b)
        {
            return a + b;
        }};

    auto addNumbers3{
        [](double a, double b)
        {
            return a + b;
        }};

    std::cout << "\nAdd numbers using different lambdas...\n";
    std::cout << addNumbers1(1, 2) << '\n';
    std::cout << addNumbers2(1, 2) << '\n';
    std::cout << addNumbers3(1, 2) << '\n';

    std::cout << "\nRepeat example...\n";
    auto lambda = [](int i)
    {
        std::cout << i << '\n';
    };

    repeat1(3, lambda);
    repeat2(3, lambda);
    repeat3(3, lambda);
    repeat4(3, lambda);

    /**
     * Generic Lambdas
     *
     * Since C++14, lambdas can use auto for parameters. In C++20, regular
     * functions can use auto too. When a lambda has one or more auto parameter
     * the compiler will infer what parameter types are needed from the calls
     * to the lambda. Lambdas with auto parameters are called *generic
     * lambdas*.
     *
     * Below we use auto to capture strings by const reference. Since all
     * string types support access via the [] operator, we can use this
     * lambda regardless of what type of strings are being passed.
     */
    constexpr std::array months{// pre-C++17 use std::array<const char*, 12>
                                "January",
                                "February",
                                "March",
                                "April",
                                "May",
                                "June",
                                "July",
                                "August",
                                "September",
                                "October",
                                "November",
                                "December"};

    // Search for two consecutive months
    const auto sameLetter{std::adjacent_find(months.begin(), months.end(),
                                             [](const auto &a, const auto &b)
                                             {
                                                 return a[0] == b[0];
                                             })};
    // Make sure that two months were found
    std::cout << "\nLetters example...\n";
    if (sameLetter != months.end())
    {
        // std::next returns the next iterator after sameLetter
        std::cout << *sameLetter << " and " << *std::next(sameLetter)
                  << " start with the same letter\n";
    }

    /**
     * One challenge with automatic type deduction is that the compiler might
     * infer a type that is difficult to work with. Here the compiler would
     * infer const char* if we used auto. However, since c-style strings are
     * difficult to work with, with might prefer std::string_view. We can
     * specify this explicitly.
     */

    // Count how many months consist of 5 letters
    const auto fiveLetterMonths{std::count_if(months.begin(), months.end(),
                                              [](std::string_view str)
                                              {
                                                  return str.length() == 5;
                                              })};
    std::cout << "There are " << fiveLetterMonths << " months with 5 letters\n";

    /**
     * constexpr lambdas
     *
     * A of C++17, lambdas are implicitly made constexpr if
     *     * The lambda has no captures or all captures are constexpr,
     *     * AND the functions called by the lambda are all constexpr.
     *
     * Many standard library functions weren't made constexpr until C++20
     * or C++23. In the above example, the lambda wouldn't be implicitly
     * const expr in C++17 but it would be in C++20 since std:count_if was
     * made constexpr in C++20.
     *
     * Generic lambdas and static variables
     *
     * When a function template contains a static local variable, each
     * function instantiated from that template will receive its own
     * independent static local variable. This may cause issues if that is not
     * expected. Generic lambdas work the way - a unique lambda is generated
     * for each different type that auto resolves to. This example uses a
     * static int to keep track of the call counts. Note how the counts are
     * different for each call signature.
     *
     * Capture Motivation
     *
     * Since each lambda has its own version of callCount, if we wanted to
     * define a common count between them we would have to make it a global
     * variable. Since it is poor practice to rely on global variables to
     * communicate between scopes, lambdas provide us with captures so we can
     * capture the variables from the outer scope we wish to use inside the
     * lambda.
     */
    auto print{
        [](auto value)
        {
            static int callCount{0};
            std::cout << callCount++ << ": " << value << '\n';
        }};

    std::cout << "\nGeneric lambdas with static variables are instantiated once per signature...\n";
    print("hello");
    print("hello");

    print(1);
    print(2);
    print(3);

    print("ding");

    /**
     * If return type deduction is used, a lambda's return type is deduced from
     * the return statements inside the lambda and all return statements in the
     * lambda must return the same type.
     *
     * This can cause problems since the compiler will enforce that all returns
     * inside the lambda have the same type.
     *
     * If we're returning different types, we can either use explicit casts
     * to make all the return types match or explicitly explicitly specify a
     * return type. Explicitly specifying the type is generally more readable.
     */
    auto divide{[](int x, int y, bool intDivision) -> double
                {
                    if (intDivision)
                    {
                        return x / y;
                    }
                    else
                    {
                        /**
                         * ERROR: return type doesn't match previous return
                         * statement without "-> double" specified above
                         * causing return x/y to be cast to double.
                         */
                        return static_cast<double>(x) / y;
                    }
                }};

    /**
     * Standard Library Function Objects
     *
     * The standard library provides many function objects for convenience.
     * These are defined in <functional>.
     */
    std::array arr3{13, 90, 99, 5, 40, 80};

    // std::greater provides a built in function to check if a > b
    std::sort(arr3.begin(), arr3.end(), std::greater{});

    std::cout << "\nSort example...\n";
    for (int i : arr3)
    {
        std::cout << i << ' ';
    }

    std::cout << '\n';

    return 0;
}