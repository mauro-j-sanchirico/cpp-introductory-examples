/**
 * Lambda Captures
 *
 * Within lambdas, we only have access to variables in the lambda's scope
 * or to parameters of the lambda.
 *
 * Lambdas can only access certain types of objects outside their scope:
 *
 *     * Objects with static (or thread local) storage duration (includes
 *       global variables and static locals).
 *     * Objects that are constexpr (explicitly or implicitly).
 *
 * If we use static variables with auto they will only persist within a given
 * function signature.
 *
 * If the compiler gave us access to all variables outside the lambda's scope,
 * it would have to make room for these on the stack. This is potentially very
 * inefficient. This is because lambdas are different from nested blocks of
 * code.
 *
 * Captures solve this problem by giving us a way to access only the variables
 * we want to access from the outer scope of a function. This is how we can
 * access variables that are not captured in the lambda's scope by default.
 *
 * Captures also allow us to capture variables from outer scope *without*
 * changing the signature of the lambda, which might be expected by function
 * that accepts it as a callback.
 *
 * How Captures Work
 *
 * Since lambdas are not code blocks, for each captured variable, a clone of
 * that variable is made inside the lambda with an identical name. When we
 * access captured variables inside a lambda, we are not accessing the original
 * variables.
 *
 * Since lambdas are actually implemented as functors, each captured variable
 * is really a data member of the object under the hood.
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>
#include <string>

int main()
{
    std::array<std::string_view, 4> arr{"apple", "banana", "walnut", "lemon"};

    std::cout << "Seach for: ";

    std::string search{};
    std::cin >> search;

    // Capture @search
    auto found{std::find_if(arr.begin(), arr.end(), [search](std::string_view str)
                            { return str.find(search) != std::string_view::npos; })};

    if (found == arr.end())
    {
        std::cout << "Not found\n";
    }
    else
    {
        std::cout << "Found " << *found << '\n';
    }

    /**
     * Mutable Captures
     *
     * Captures are const by default. Code that attempts to modify captures
     * won't compile. To allow modifications of variables that were captured
     * we can mark the lambda as mutable.
     *
     * Since captured variables are members of the lambda object, their values
     * persist across multiple calls to the lambda.
     */
    int shells{3};

    auto throwShell{
        [shells]() mutable
        {
            // Allowed to modify - this would not compile without mutable
            --shells;
            std::cout << "Threw shell! " << shells << " shells left.\n";
        }};

    throwShell();
    throwShell();

    std::cout << "\nThis will be wrong...\n";
    std::cout << shells << " shells left.\n\n";

    /**
     * Capture By Reference
     *
     * If we want to change the value of the variable in the outside scope, we
     * can capture it by reference using &. Capture by reference allows passing
     * mutable arguments without making a copy of the entire argument.
     */
    int bananas{3};

    auto throwBanana{
        // No need for mutable if we're passing by reference
        [&bananas]()
        {
            --bananas;
            std::cout << "Threw banana! " << " bananas left.\n";
        }};

    throwBanana();
    throwBanana();

    std::cout << "\nThis will be right...\n";
    std::cout << bananas << " left.\n";

    /**
     * Capturing Multiple Variables
     *
     * Multiple variables can be captured by separating them with a comma.
     */
    int health{33};
    int armor{100};
    int nEnemies{3};

    [health, armor, &nEnemies]()
    {
        std::cout << "health: " << health << '\n';
        std::cout << "armor: " << armor << '\n';
        --nEnemies;
    };

    std::cout << "\nMultiple captures example...\n";
    std::cout << "enemies left: " << nEnemies << '\n';

    /**
     * Default Capture
     *
     * If we don't want to explicitly capture all the variables we need, we can
     * use a *default capture* to tell the compiler to capture only the
     * variables that we need. To capture all used variables by value we use
     * = in the capture expression, to capture all used variables by reference
     * we use &.
     */

    std::array areas{100, 25, 121, 40, 56};

    int width{};
    int height{};

    std::cout << "\nDefault capture example...\n";
    std::cout << "Enter width and height: ";
    std::cin >> width >> height;

    // Default capture by value
    auto foundArea{std::find_if(areas.begin(), areas.end(),
                                [=](int knownArea)
                                {
                                    return width * height == knownArea;
                                })};

    if (foundArea == areas.end())
    {
        std::cout << "I don't know this area :(\n";
    }
    else
    {
        std::cout << "Area found :)\n";
    }

    /**
     * Default captures can be mixed with normal captures. We can capture some
     * variables by reference and others by value, but can only capture each
     * variable once.
     * int health{ 33 };
     * int armor{ 100 };
     * std::vector<CEnemy> enemies{};
     *
     * // Capture health and armor by value, and enemies by reference.
     * [health, armor, &enemies](){};
     *
     * // Capture enemies by reference and everything else by value.
     * [=, &enemies](){};
     *
     * // Capture armor by value and everything else by reference.
     * [&, armor](){};
     *
     * // Illegal, we already said we want to capture everything by reference.
     * [&, &armor](){};
     *
     * // Illegal, we already said we want to capture everything by value.
     * [=, armor](){};
     *
     * // Illegal, armor appears twice.
     * [armor, &health, &armor](){};
     *
     * // Illegal, the default capture has to be the first element in the capture group.
     * [armor, &](){};
     */

    /**
     * Defining Variable in the lambda-capture
     *
     * We can capture a variable with a modification or declare a new variable
     * visible only inside the lambda.
     *
     * This can make code less readable however and it is a best practice to
     * avoid initializing variables inside the capture unless their value and
     * type will be obvious.
     */
    auto foundArea2{std::find_if(areas.begin(), areas.end(),
                                 // Declare a new variable that's visible only to the lambda
                                 // The type of userArea is automatically deduced to int.
                                 [userArea{width * height}](int knownArea)
                                 {
                                     return userArea == knownArea;
                                 })};

    std::cout << "\nDefining Variable in Capture Example...\n";
    if (foundArea2 == areas.end())
    {
        std::cout << "I don't know this area :(\n";
    }
    else
    {
        std::cout << "Area found :)\n";
    }

    return 0;
}