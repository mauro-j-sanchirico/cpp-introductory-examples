/**
 * Headers and Include Guards
 *
 * Splitting a program across multiple files drives a need to forward
 * declare functions in the main code so that the functions can be used before
 * their definition. To avoid having to make the forward declarations
 * manually, they are usually included in a header file via a #include
 * directive. The preprocessor we the substitute in the forward declarations.
 * Header files usually have a .h extension but can also have other extensions.
 * It is a best practice to use the .h extension and to give the header file
 * the same basename as the corresponding source file, e.g., add.h and add.cpp.
 *
 * Since header files will be included in multiple source files, in basic
 * architectures they will only include forward declarations and will not
 * include function and variable definitions. This will avoid functions being
 * defined twice and violating the one definition rule (ODR).
 *
 *
 * Best Practice: Include the Paired Header in the Corresponding Source
 *
 * As a best practice, include the paired header with a source file. Having the
 * preprocessor insert the forward declarations in the source file ensures
 * that the compiler will catch conflicts between the declarations and the
 * definitions. This allows bugs due to these conflicts to be caught sooner
 * in the build process. Since building can take a long time for large projects
 * catching errors at compile time instead of linking time can save significant
 * effort.
 *
 * Best Practice: Do not use #include to Include Source Files
 *
 * While the preprocessor will allow using #include to include .cpp files, this
 * should not be done. This can lead to multiple definitions, name collisions,
 * and cause the need to recompile files to propagate through any files which
 * include the .cpp file. If you change a function definition in one file and
 * then recompile, any file that includes that file will then need to recompile
 * which can waste significant time in large projects.
 *
 * Angle Brackets vs. Double Quotes
 *
 * Angle brackets (<>) are used to include standard libraries that come with
 * a compiler, OS, or third parties. Double quotes ("") are used to include
 * libraries written as part of a project or otherwise expected to be found
 * in the current directory.
 *
 * History: Why doesn't iostream have a .h extension?
 *
 * Historically, all standard library headers had a .h extension. The original
 * versions declared keywords like cout and cin in the global namespace.
 * Declaring identifiers in the global namespace was liable to cause problems
 * between versions of the language. If user code used an identifier that did
 * not conflict with the standard library, but a later version of C++ then
 * added that identifier, the name conflict would cause compilation errors.
 * To solve this, new headers without the .h extension were developed (e.g.,
 * iostream). This allowed new code to use the new headers and legacy code
 * to continue using the old headers (e.g., iostream.h). C++ also includes
 * headers named <cxx> (i.e., names that start with c) for backwards
 * compatibility with C. Modern best practice is to use the new C++ libraries
 *
 * VS Code Tip:
 *
 * If you get an error like "#include errors detected. Please update your
 * includePath." click on the error and then click on "Quick fixes". Under
 * quick fixes select the option to add the include directory to your
 * includePath. This will tell VS Code where to look for your includes.
 *
 * Best Practice: Avoid Referencing Directory Structure in Code
 *
 * It is legal to use relative paths(e.g., #include ../dirA/lib.h). However,
 * this is brittle since code will need to be changed if the directory
 * structure changes. Configure VS Code and/or your compiler to know where to
 * look for your includes.
 *
 * Best Practice: Do Not Rely on Transitive Includes
 *
 * If a file is included in one file, and then that file is included in another
 * file, that file will include both files. This is called a *transitive
 * include* (like the transitive property in math). However, it is not good
 * practice to rely on a transitive include being present. Explicitly include
 * every header in every other header or source file that needs it.
 *
 * To ensure that the compiler WILL report an error for missing includes (this
 * is desired since it helps us catch problems early) order includes as
 * follows:
 *
 *      1. The paired header file for a source file
 *      2. Other headers from the same project
 *      3. Third party libraries (e.g., Boost or Eigen)
 *      4. Standard library headers (e.g., iostream).
 *
 * Header Guards
 *
 * Since it is best practice to include a header in each file it is needed in,
 * and since the preprocessor will blindly make this substitution for us
 * without checking if it violates the ODR, we need a way to tell the
 * preprocessor to only make a substitution of a header once. This is done with
 * *header guards* (also called *include guards*). Header guards use an
 * #ifndef directive to check that the header has not already been defined. If
 * the header has not already been defined, then an indicator is defined using
 * #define. This way, next time the header is included, the preprocessor will
 * see that the indicator has already been defined and avoid the duplicate
 * inclusion.
 *
 * Best Practice: Use Descriptive Include Guard Names
 *
 * In large projects there is a chance that two files will have the same name.
 * Sometimes, different files will be written by different departments or
 * even different organizations. For this reason, large projects will adopt
 * a naming convention for include guards. This will often include the
 * organization name, project name, component name, file name, and sometimes
 * a unique identifier.
 *
 * For example, instead of SQUARE_H, a large project might use:
 * TEAM_PROJECT_GEOMETRY_SQUARE_02162025_H.
 *
 * Header guards appear in the example in this directory.
 *
 * Note that when defined in this way, header guards only prevent a header from
 * being included in a specific file multiple times. The header will still be
 * included in each file it is needed in. This is ok and intentional as long
 * as the header only includes declarations and not definitions (since this
 * would violate the ODR).
 */

// Include project-specific header, square.h
#include "square.h"

// Include standard header, iostream
#include <iostream>

int main()
{
    // Use functions from square.h (since they are forward declared in the header)
    std::cout << "a square has " << getSquareSides() << " sides\n";
    std::cout << "a square of length 5 has perimeter length " << getSquarePerimeter(5) << '\n';

    return 0;
}

/**
 * Best Practices Summary:
 *
 *      1. Always use header guards.
 *      2. Do not define variables and functions in headers (as a beginner).
 *      3. Always give a header the same basename as its source.
 *      4. Give each header one specific job and do not make it do more.
 *      5. Avoid transitive includes. Include all needed headers explicitly.
 *      6. Do not include a header if it is not actually needed.
 *      7. Do not include source files.
 *      8. Put comments on how to use a library in its header.
 *      9. Put comments on how a library works (for developers) in its source.
 */