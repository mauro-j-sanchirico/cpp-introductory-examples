/**
 * Issues Making Copies of Mutable Lambdas
 *
 * Since lambdas are implemented as functors (i.e., objects) they can be
 * copied. This can cause problems in several ways:
 *
 *     1. Lambdas are copied in place, which means the state of the underlying
 *        object is copied to the new object, which can lead to
 *        counter-intuitive results.
 *     2. Unintended copies can take place when passing a lambda to a function
 *        that expects a different type.
 *     3. Intended copies can have unintended behavior since mutable variables
 *        may or may not be shared between the copies depending on how the
 *        copies are made.
 *
 * Because of these issues, it is a best practice to try to avoid mutable
 * lambdas. Non-mutable lambdas are easier to understand and don't suffer from
 * these issues with copying. The dangers of mutable lambdas are exacerbated
 * with parallel execution.
 */

#include <iostream>
#include <functional>

void myInvoke(const std::function<void()> &fn)
{
    fn();
}

int main()
{
    /**
     * Basic Lambda Copy Example
     *
     * We might expect this to print 1, 2, 1, or 1, 2, 3. However, this code
     * will print 1, 2, 2. This is because the counter had already been
     * incremented once when the first call to count happened. Then the
     * functor object (remember that lambdas are truly objects) was copied in
     * place with its current state. So otherCount starts at the state count
     * was in when it was copied, and each now have their own i.
     */
    std::cout << "Basic lambda copy example...\n";

    int i{0};

    // Create a new lambda named count
    auto count{[i]() mutable
               {
                   std::cout << ++i << '\n';
               }};

    count(); // invoke count

    auto otherCount{count}; // Create a copy of count

    // invoke both count and the copy
    count();
    otherCount();

    /**
     * Unintended Lambda Copy via Function Argument
     *
     * In this example, each time we call myInvoke() a new copy of count2 is
     * instantiated on the stack. Since the type of the lambda doesn't match
     * the type of the parameter in myInvoke(), myInvoke() will make a copy
     * of the lambda as a temporary std::function. The copy is then executed,
     * not the base lambda! This means the counter never increments...
     */
    std::cout << "\nBasic lambda copy example...\n";
    int j{0};

    // Increments and prints its local copy of @i
    auto count2{[j]() mutable
                {
                    std::cout << ++j << '\n';
                }};

    myInvoke(count2);
    myInvoke(count2);
    myInvoke(count2);

    /**
     * Proper Lambda Copy with Type Alignment
     *
     * In this example, we initialize the lambda with std::function to align
     * with the parameter type expected by myInvoke. This prevents the compiler
     * from making a copy of it. Now the count increments as expected.
     */
    std::cout << "\nType alignment example...\n";

    int k{0};

    std::function count3{[k]() mutable
                         {
                             std::cout << ++k << '\n';
                         }};

    myInvoke(count3);
    myInvoke(count3);
    myInvoke(count3);

    /**
     * Proper Lambda Copy with a Reference Wrapper
     */
    std::cout << "\nReference wrapped example...\n";

    int m{0};

    auto count4{[m]() mutable
                {
                    std::cout << ++m << '\n';
                }};

    /**
     * std::ref() ensures count4() is treated like a reference in these calls
     * rather than copied. Anything that tries to copy count4 will actually
     * copy the reference.
     *
     * Note that this means even if the myInvoke takes its fn parameter by
     * value, passing with std::ref will still pass a reference!
     */
    myInvoke(std::ref(count4));
    myInvoke(std::ref(count4));
    myInvoke(std::ref(count4));

    return 0;
}