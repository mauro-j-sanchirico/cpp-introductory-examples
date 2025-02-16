# =============================================================================
# Root Makefile for basic C++ examples
#
# This is a simple Makefile with recipes make, clean, and run the projects in
# any subdirectory which contains a Makefile.
#
# Usage:
#
# Build all:
#     > make all
#
# Clean all:
#     > make clean
# =============================================================================

SUBDIRS_WITH_MAKEFILE:=$(wildcard */*/Makefile)
SUBDIRS_WITH_MAKEFILE:=$(dir $(SUBDIRS_WITH_MAKEFILE))

# Main build all recipe
all: $(SUBDIRS_WITH_MAKEFILE)

$(SUBDIRS_WITH_MAKEFILE):
	$(MAKE) -C $@

# Additional recipes
clean:
	@for dir in $(SUBDIRS_WITH_MAKEFILE); do \
		$(MAKE) -C $$dir clean; \
	done

.PHONY: all clean run $(SUBDIRS_WITH_MAKEFILE)