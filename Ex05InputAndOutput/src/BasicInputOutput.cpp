
// The input/output library is part of the C++ standard library that deals with
// basic input and output. This library gets data from the keyboard and to the
// console.

// To use the functionality in the iostream library, we include it at the top
// of any file that needs it:
#include <iostream>

int main()
{

    /**
     * std::cout
     */

    // The iostream library contains a few pre-defined variables for us to use.
    // One of the most useful is std::cout. This allows us to send data to the
    // console to be printed as text.

    std::cout << "Hello, World!" << std::endl;

    // Here we use std::cout along with the **insertion operator** (<<) to send
    // text to the console.

    // We can also print the value of variables
    int x{5};

    std::cout << x << std::endl;

    // We can print both text and variables

    std::cout << "The value of x is " << x << std::endl;

    // In these examples std::endl is used to print new lines so the text is
    // more legible on the console. // It is a best practice to output a new
    // line at the end of each statement so the next statement is sure to
    // be on its own line.

    // Characters sent to std::cout are "buffered", i.e., stored in a queue
    // which is periodically flushed. This is more efficient than incurring the
    // overhead of pushing each to the console individually.

    /**
     * std::endl vs. \n
     */

    // std::endl prints a new line and flushes the buffer. The \n character is
    // only a new line. Flushing the buffer is slow, so \n is used if
    // performance is critical and the buffer does not need to be immediately
    // flushed. As a best practice, prefer \n.

    // Flush the buffer and print a new line
    std::cout << "Flush the buffer and print a new line.." << std::endl;

    // Print a new line
    std::cout << "Print a new line..." << std::endl;

    /**
     * std::cin
     */

    // std::cin is another predefined variable in the iostream library. Whereas
    // std::cout prints data to the console (using the insertion operator <<
    // to provide the data). std::cin (which stands for character input) reads
    // input from keyboard. We typically use the extraction operator >> to put
    // the input data in a variable (which can then be used in subsequent
    // statements).
    int y{};

    std::cout << "Enter a number: ";
    std::cin >> y;

    std::cout << "You entered " << y << '\n';

    // We can also get multiple numbers separated by a space
    std::cout << "Enter two numbers separated by a space: ";

    int a{};
    int b{};

    std::cin >> a >> b;

    std::cout << "You entered " << a << " and " << b << '\n';

    // **Note**: The C++ I/O library does not provide a way to accept keyboard
    // input without the user pressing enter. Third party libraries are
    // required for this. Examples include pdcurses, FXTUI, cpp-terminal, or
    // notcurses.

    // std::cin is buffered. The individual characters are added to the buffer.
    // The extraction error >> removes characters from the front of the input
    // buffer and converts them into a value that is assigned (via copy
    // assignment) to the associated variable.

    std::cout << "Enter two numbers: ";
    int i{};
    std::cin >> i;
    int j{};
    std::cin >> j;
    std::cout << "You entered " << i << " and " << j << '\n';

    // Notice that if you type "3 4" or "3\n4" the output is still the same.
    // This is because std::cin is buffered. We can enter the input once and
    // the perform multiple extractions from the buffer that was built when the
    // input was first entered!

    // A simplified flow of the extraction process:
    // 1. If the buffer is not in a good state not extraction is attempted
    // 2. Leading whitespace characters are discarded
    // 3. If the buffer is now empty, >> will wait for the user to enter more
    //    data. Any leading whitespace is discarded.
    // 4. The >> operator then extracts as many consecutive characters as it
    //    can, until it encounters either a newline character (representing the
    //    end of the line of input) or a character that is not valid for the
    //    variable being extracted to.
    //
    // As of C++11, if the extraction fails in step 4, the object being
    // extracted is copy-assigned the default value of 0. Any future
    // extractions will immediately fail.

    return 0;
}