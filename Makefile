#=============================================================================
# UNIVERSAL OPTIMIZER LIBRARY (C++) - Top-level Makefile
#=============================================================================
# This Makefile orchestrates the build of the whole project.
#=============================================================================

CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2 -Iinclude

SRC_DIR     := src
INCLUDE_DIR := include
TEST_DIR    := tests
BUILD_DIR   := build
LIB_DIR     := lib

SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
LIBRARY := $(LIB_DIR)/libuo.a

all: dirs $(LIBRARY)

dirs:
	@mkdir -p $(BUILD_DIR) $(LIB_DIR)
	@mkdir -p $(BUILD_DIR)/tests

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LIBRARY): $(OBJECTS)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^
	@echo "Library built: $@"

test: dirs $(LIBRARY)
	@echo "Testing requires test framework; implement in sub-Makefiles."

clean:
	rm -rf $(BUILD_DIR) $(LIB_DIR)
	@echo "Cleaned."

distclean: clean
	rm -rf docs

format:
	@find $(SRC_DIR) $(INCLUDE_DIR) -name '*.cpp' -o -name '*.hpp' | xargs clang-format -i -style=file 2>/dev/null || echo "clang-format not found; skip."

docs:
	@doxygen Doxyfile 2>/dev/null || echo "Doxygen not found."

.PHONY: all dirs test clean distclean format docs
