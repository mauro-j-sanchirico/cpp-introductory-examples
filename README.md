# C++ Introductory Examples

This repository contains introductory C++ programs to be used alongside introductory live tutorials in a virtual classroom setting.

The examples are largely based on those in [https://www.learncpp.com/](https://www.learncpp.com/) with additional comments added from experience.

The examples are designed to be basic so students can focus on introductory topics specific to learning the C++ language itself and not particular to any given toolchain.

Additional examples from other sources and from experience may be added later.

## Structure

Examples are grouped into chapters. Each chapter contains several examples. Each example is its own C++ program which compiles and links independently of any other examples.

Each example has its own Makefile. No knowledge of Make is required to use and experiment.

A top level Makefile is provided to compile and link all examples.

A basic Python environment managed with Poetry is also provided to enable using matplotlib and other basic Python packages to visualize data generated by some more involved examples.

## Usage

### Building All Examples

To build all examples use the recipe in the top level Makefile.

```bash
cd /workspaces/cpp-introductory-examples
make all
```

### Cleaning All Examples

To clean all examples (remove all objects and binaries) use the `clean` recipe in the top level Makefile.

```bash
cd /workspaces/cpp-introductory-examples
make clean
```

### Building and Running a Specific Example

To build and run a specific example, navigate to its directory and use its individual recipes.

```bash
cd /workspaces/cpp-introductory-examples/ch01_basic_examples/ex01_basics
make clean  # Clean any old binaries and objects
make        # Build the example
make run    # Run the example
```

### Using the Python Virtual Environment

The container provided will configure Poetry and generate the Python virtual environment automatically. This will ensure Poetry is on the PATH and configured to use virtual environments in the project. These commands are executed in `.devcontainer/post_attach.sh`.

An alias is provided to the local Python environment. To use it, type `localpy`.

```bash
localpy
```

Use alias to see the path to the local Python.

```bash
alias localpy
```

## References

These examples are largely based on those from [https://www.learncpp.com/](https://www.learncpp.com/).

They are made to complement live tutorials stepping through the lessons in `learncpp.com` with some notes added from experience.

## Contact

Please email Mauro J. Sanchirico III ([sanchirico.mauro@gmail.com](sanchirico.mauro@gmail.com)) with questions, comments, bug reports, or suggestions.