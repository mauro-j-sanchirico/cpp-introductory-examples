# =============================================================================
# Makefile for basic C++ examples
#
# This is a simple Makefile intended for instructional or basic C++ examples.
#
# Usage:
#
# Build the program:
#     > make
#
# Run the program:
#     > make run
#
# Clean:
#     > make clean
# =============================================================================

# Compiler flags
CXX:=g++
STD:=-std=c++20
CFLAGS:=-Wall -Werror -Wextra -Weffc++ -Wsign-conversion -pedantic
DEFINITIONS:= -DFMT_HEADER_ONLY
DEBUG_FLAGS:=-g

# Directory configuration
EXE_NAME:=main
BIN_DIR:=bin
OBJ_DIR:=obj
SRC_DIR:=src
INC_DIR:=include

# File extensions
SRC_EXT:=.cpp
INC_EXT:=.h

# Sources, headers and objects
SRC:=$(wildcard $(SRC_DIR)/*$(SRC_EXT))
INC:=$(wildcard $(INC_DIR)/*$(INC_EXT))
OBJ:=$(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
INCLUDES:=-I$(INC_DIR)

# Target executable
TRGT_EXE:=$(BIN_DIR)/$(EXE_NAME)

# Setup
ifeq ($(SRC),)
$(error No source files found!)
endif

# Main recipe
$(TRGT_EXE): $(OBJ)
	mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ) -o $@

obj/%.o: src/%.cpp $(INC)
	mkdir -p $(OBJ_DIR)
	$(CXX) $(STD) $(DEBUG_FLAGS) $(CFLAGS) $(DEFINITIONS) $(INCLUDES) -c $< -o $@

# Additional recipes
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) $(TRGT_EXE)

run:
	./$(TRGT_EXE)

.PHONY:clean run