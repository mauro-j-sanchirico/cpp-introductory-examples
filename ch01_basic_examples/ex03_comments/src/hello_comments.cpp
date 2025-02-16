#include <iostream>

int main()
{
    // This is a single line comment
    std::cout << "Hello, World!" << std::endl;           // Single line comments can go on the end of a line
    std::cout << "It is nice to meet you!" << std::endl; // Too many of these make code hard to read
    std::cout << "Yeah!" << std::endl;                   // Especially when lines are different lengths

    /* This is a multiline comment.
    This line will be ignored.
    This line will also be ignored.*/

    /* This style with matching asterisks can
     * make the comment easier to read.
     */

    /* Multi-line comments cannot be nested inside other comments
     * For example, you cannot put another multiline comment here -->
     */

    /* In general, comments can be used to describe what, how, and why a
     * program is doing something.
     */

    // Do not make comments redundant

    // The following is a bad comment:

    // Set sight range to 10
    float sight = 10;

    // The following is a good comment:

    // The player just drank a potion of blindness and cannot see anything
    sight = 0;

    std::cout << "Player sight: " << sight << std::endl;

    // Write comments as if speaking to someone who has no idea what the code does!

    return 0;
}