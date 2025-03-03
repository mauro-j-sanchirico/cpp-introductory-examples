#include <iostream>
#include <chrono>
#include <vector>

auto main() -> int
{
    auto n = int{50000000};
    auto v1 = std::vector<int>{};
    auto v2 = std::vector<int>{};

    v2.reserve(n);

    // Inserting elements without reserve()
    auto start = std::chrono::high_resolution_clock::now();
    for (auto i = int{0}; i < n; ++i)
    {
        v1.push_back(2);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "Time to push elements to unreserved memory vector: " << duration << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (auto i = int{0}; i < n; ++i)
    {
        v2.push_back(2);
    }
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "Time to push elements to reserved memory vector: " << duration << " ms" << std::endl;

    return 0;
}