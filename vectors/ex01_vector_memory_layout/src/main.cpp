#include <iostream>
#include <vector>

auto main() -> int
{
    auto data = std::vector<int>{2, 3, 5, 7, 11, 13, 17, 19};

    std::cout << "Address of vector:" << &data << std::endl;
    std::cout << "Addresses of elements:" << std::endl;

    std::cout << "Before push_back..." << std::endl;
    for (auto i = size_t{0}; i < data.size(); ++i)
    {
        std::cout << "Address at position " << i << ": " << &data[i] << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Size of vector: " << data.size() << std::endl;
    std::cout << "Capacity of vector: " << data.capacity() << std::endl;
    std::cout << std::endl;

    // The vector is at capacity - what happens when we add another element?
    data.push_back(21);

    std::cout << "After push_back..." << std::endl;
    std::cout << "Size of vector after push_back: " << data.size() << std::endl;
    std::cout << "Capacity of vector after push_back: " << data.capacity() << std::endl;
    std::cout << std::endl;

    // We can see that the capacity has now doubled and the addresses are allocated contiguously in memory
    // WARNING: This is example code only to show how std::vector allocates memory - do not iterate outside the size of a vector in practice!!
    std::cout << "Example - iterate to capacity (do not do this in practice)..." << std::endl;
    for (auto i = size_t{0}; i < data.capacity(); ++i)
    {
        std::cout << "Address at position " << i << ": " << &data[i] << std::endl;
    }
    std::cout << std::endl;

    // If we try to print the elements we can see the compiler initializes them to 0, but this is not always guaranteed to be true!
    // WARNING: This is example code only to show how std::vector allocates memory - do not iterate outside the size of a vector in practice!!
    std::cout << "Example - iterate to capacity (do not do this in practice)..." << std::endl;
    for (auto i = size_t{0}; i < data.capacity(); ++i)
    {
        std::cout << "Value at position " << i << ": " << data[i] << std::endl;
    }
    std::cout << std::endl;

    return 0;
}