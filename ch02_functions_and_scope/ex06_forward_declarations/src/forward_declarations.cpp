#include <iostream>

/**
 * Forward Declarations
 *
 * Sometimes we want to use a function before it is defined. Usually, this
 * is because the function is defined in another file and we do not have
 * control over the order it will be used in. We also might just want the
 * freedom to define functions in a particular order.
 *
 * We can achieve this be using a *function declaration* to tell the compiler
 * about a function's name, return type, and parameter types. If we declare
 * a function, we are free to use it in code after the declaration and define
 * it later. Function declarations are also called *function prototypes*.
 *
 * If a function body is not provided, the program will still compile. This is
 * because the compiler just needs to know the function's prototype. However,
 * the code will fail to *link* since there will be no function definition to
 * link to the prototype.
 *
 * Declarations vs. Definitions
 *
 * A *declaration* tells the compiler about the existence of an *identifier*.
 * A *definition* actually implements (for functions) or instantiates
 * (for variables) the identifier.
 *
 * In C++, all definitions are declarations, but not all declarations are also
 * definitions. For example, a forward declaration just declares a function but
 * does not define it. Declarations that are not definitions are called
 * *pure declarations*.
 *
 * One Definition Rule
 *
 * The *one definition rule* (ODR):
 *
 * 1. Within each file, each function, variable, type, or template in a given
 * scope can only have one definition.
 * 2. Within a program, each function, variable, type, or template in a given
 * scope can only have one definition. (Remember programs can have multiple
 * files.)
 * 3. Type, templates, inline functions, and inline variables are allowed to
 * have duplicate definitions in different files as long as each definition is
 * identical.
 *
 * Violating #1 causes a compiler error. Violating #2 causes a linker error.
 * Violating #3 causes undefined behavior.
 */

// Here we forward declare add() so we can use it before it is defined
int add(int x, int y);

/**
 * We could also declare add without x and y: int add(int, int)
 * However, it is a best practice to include the parameter names so we
 * remember what they are.
 */

int main()
{
    /**
     * This line works because we forward declared add. If we had not forward
     * declared add(), the compiler wouldn't know what it is since we didn't
     * define it until after the main() function.
     */
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';
    return 0;
}

// Here we define the body of add
int add(int x, int y)
{
    return x + y;
}