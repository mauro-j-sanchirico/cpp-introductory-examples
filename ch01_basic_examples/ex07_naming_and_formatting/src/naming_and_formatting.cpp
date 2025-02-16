/**
 * Naming Conventions
 *
 * As of C++23, C++ reserves 92 keywords or reserved word. Do not try to name
 * variables after these!
 *
 * Official rules for variable names:
 *     1. The identifier cannot be a keyword.
 *     2. The identifier can only be composed of letters, numbers, and the
 *        underscore character. The name cannot contain symbols or whitespace.
 *     3. The identifier must begin with a letter.
 *     4. C++ is case sensitive.
 *
 * Conventions for variable names:
 *     1. Begin with a lowercase letter
 *     2. snake_case or interCappedWithFirstLetterLowercase is conventional.
 *     3. Starting with an underscore is legal but should be avoided (these
 *        names are usually used by the OS, library, or compiler).
 *     4. Use meaningful names.
 *
 * Make identifier length proportional to how specific and accessible the
 * identifier is.
 *     - Identifier that exists only for a few statements can have a short name
 *     - Identifier accessible from anywhere might benefit from a longer name
 *     - Identifier that represents a non-specific number can have a shorter
 *       name
 *     - Identifier that represents a specific value (length of an inseam in
 *       millimeters) needs a longer name.
 *     - Use comments to describe what the variable is going to be used for.
 */

#include <iostream>

int main()
{
    // Good variable names
    int salesPerMonth{5};
    float inseamLengthInches{8.8};

    std::cout << salesPerMonth << std::endl;
    std::cout << inseamLengthInches << std::endl;

    // C++ is whitespace independent. The following statements are equivalent.
    std::cout << "Hello, World!" << std::endl;
    std::cout
        << "Hello, World!"
        << std::endl;

    /**
     * By convention:
     *     - Indent within curly braces.
     *     - Keep lines to 80 characters or less.
     *     - If you are working in someone else's code, adopt their styles.
     */

    return 0;
}