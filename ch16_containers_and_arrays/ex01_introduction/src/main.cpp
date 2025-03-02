#include <array>
#include <iostream>
#include <string>

int main()
{
    /**
     * Variables are not always scalable for all tasks. Consider computing the
     * average of several numbers.
     */
    float n1 = 1;
    float n2 = 2;
    float n3 = 3;
    float n4 = 4;
    float n5 = 5;
    float n6 = 6;
    float n7 = 7;

    // This is bad
    float average = (n1 + n2 + n3 + n4 + n5 + n6 + n7) / 7;

    std::cout << "Average: " << average << '\n';

    /**
     * This is difficult to type as is, and does not follow the DRY paradigm.
     * Taking averages and other simple operations of multiple numbers this
     * way would be completely impractical for large amounts of numbers.
     * We would also need to modify the code every time we added a new value.
     * Any time we modify code we risk introducing bugs, so we want to write
     * code that is as reusable and *scalable* as possible.
     *
     * Further, we would have to pass all these variables to functions
     * individually. This would mean our functions would need a large number of
     * parameters - one for each variable! Imagine what this would look like if
     * we wanted to write a function to compute an average of 1000 numbers.
     * Usually, functions in production code should have few arguments to make
     * them easier to write and maintain, and we should not have to change our
     * functions to change the size and shape of the data we pass in.
     *
     * We can partially solve the problem by making our variables members of
     * a struct to allow us to pass all our numbers to a function more
     * easily, it does not help us iterate through them in a more generic and
     * scalable manner.
     */

    // This is not much better
    struct MyNumbers
    {
        int n1 = {1};
        int n2 = {2};
        int n3 = {3};
        int n4 = {4};
        int n5 = {5};
        int n6 = {6};
        int n7 = {7};
    };

    auto n = MyNumbers{};

    average = (n.n1 + n.n2 + n.n3 + n.n4 + n.n5 + n.n6 + n.n7) / 7;

    std::cout << "Average: " << average << '\n';

    /**
     * *Containers* provide a better way to organize many related data points,
     * especially when we need code that is *scalable* to large numbers or
     * variable numbers of data points. Containers in software are analogous
     * to the containers we use to organize many parts and pieces in a room
     * in the physical world. They can hold a variable number of parts and
     * allow us to grab all the parts they hold at once rather than forcing us
     * to grab them one by one. In C++, containers hold a collection of
     * unamed (no identifier assigned) object called *elements*. The elements
     * of a container can be any objects, including instances of a class,
     * variable, or even other containers!
     *
     * Since the elements of a container are not named, each container provides
     * means to access them using only the name of the container. A container's
     * length is the number of elements inside it.
     *
     * std::string is an example of a container in the general programming
     * definition of the word "container".
     */

    std::string hello{"Hello World!"};
    std::cout << "String \"" << hello << "\" has " << hello.length() << " characters\n";

    /**
     * Containers typically support many operations. Examples include creation,
     * access to elements, element insertion or removal, getting the number of
     * elements in the container, and many more.
     *
     * Each container implements a different type of *data structure* and
     * provides different *algorithms* for performing operations on it. The
     * different data structures and algorithms implemented carry different
     * strengths and weaknesses.
     *
     * In C++, containers are homogenous, meaning all elements must be of the
     * same type. Scripting languages (e.g., Python) usually provide support
     * for heterogenous containers. This makes programming easier in some
     * cases but also places more responsibility on the programmer to ensure
     * that different potential types in containers are handled correctly.
     *
     * C++ provides many types of containers as part of the standard library.
     * They are listed here: https://en.cppreference.com/w/cpp/container.
     *
     * Though the following are all containers in the general programming
     * sense of the word containers, they are not formally containers in C++:
     *     - C-style arrays
     *     - std::string
     *     - std::vector<bool>
     *
     * For a class to be a container in C++, it must meet the requirements
     * listed here: https://en.cppreference.com/w/cpp/named_req/Container. This
     * includes implementing certain member functions and other requirements.
     *
     * The most commonly used containers in C++ are std::vector and std::array.
     * We'll look at an example of std::array here and an example of
     * std::vector next.
     */
    std::array<int, 3> a1{1, 2, 3};
    std::array<int, 3> a2{4, 5, 6};

    std::cout << "\nArrays example:\n";
    std::cout << "Address of array a1: " << &a1 << '\n';
    std::cout << "Address of array a2: " << &a2 << "\n\n";

    /**
     * This shows us where the two arrays are stored in memory. One of the
     * guarantees that arrays provide is the elements will be stored
     * contiguously in memory. Let's see is we can use the address operator,
     * `&`, to see that in action.
     */

    std::cout << "\nAddresses and elements of a1 - attempt 1\n";
    for (auto element : a1)
    {
        std::cout << "Accessing element value " << element << " at address " << &element << '\n';
    }

    /**
     * That doesn't look right... why are all the elements at the same address?
     * Why is this address different than the address where the array was
     * stored? This is because using "auto element : a1" gets us a copy of
     * each element of a1 by default. The address we are getting with
     * &element is the address of the copy.
     *
     * To get a reference to the element instead we can use
     * "auto &element: a1". This reference gives us the address of each element
     * in the array that we are iterating through.
     */

    std::cout << "\nAddresses and elements of a1 - attempt 2 with auto &\n";
    // auto &it gets a reference to the object in the vector, rather than
    for (auto &element : a1)
    {
        std::cout << "Accessing element value " << element << " at address " << &element << '\n';
    }

    std::cout << "\nAddresses and elements of a2\n";
    // auto &it gets a reference to the object in the vector, rather than
    for (auto &element : a2)
    {
        std::cout << "Accessing element value " << element << " at address " << &element << '\n';
    }

    /**
     * C++ supports three types of arrays:
     *     1. C-style arrays inherited from C
     *     2. The std::vector container
     *     3. The std::array container
     *
     * C-style arrays are called "arrays" in the C++ standard but in modern
     * C++ they are more often called "C-style arrays", "C arrays", or
     * "naked arrays". Since their size is fixed, they also may be called
     * "fixed-size arrays" or "fixed arrays". Since they do not require any
     * libraries, they also may be called "built-in" arrays. C-style arrays
     * provide none of the protections that modern C++ arrays provide (hence
     * the slang term "naked") and are considered dangerous and bad practice
     * in modern C++. Valid use cases include backwards compatibility and
     * low-level device programming.
     *
     * The std::vector class was introduced in C++03 to help make arrays
     * safer and easier to use. It is flexible and includes many useful
     * capabilities. std::vector is a workhorse of scientific computing in the
     * C++ language.
     *
     * The std::array class was introduced in C++11 to directly replace C-style
     * arrays. Since std::vector implements many conveniences that make large
     * vectors easy to use, there was still a temptation to try to use C-style
     * arrays for performance gains. The std::array class was introduced to
     * mostly eliminate the need to use C-style arrays. It does not provide all
     * the features of std::vector but can be more efficient, especially for
     * smaller arrays. In modern C++, std::vector is preferred and std::array
     * should be used if there is a requirement for optimization. C-style
     * arrays should almost never be used except in rare cases for low-level
     * programming, educational examples, or to meet backwards compatibility
     * requirements.
     */

    return 0;
}