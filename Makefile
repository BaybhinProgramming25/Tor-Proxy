# Will need to eventually learn all this which will be another thing for later 
# Compiler settings
CXX := g++
CXXFLAGS := -Wall -Wextra -Werror -Wpedantic -Wunused -g -Wno-unused-parameter
SANITIZE := -fsanitize=address -fsanitize=undefined

# Directories
SRC_DIR := src
INC_DIR := include
BUILD_DIR := build
BIN_DIR := bin

# Find all source and header files
SRCS := $(wildcard $(SRC_DIR)/*.c)
HDRS := $(wildcard $(INC_DIR)/*.h)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Final executable name
TARGET := $(BIN_DIR)/program

# Include directories
INC_FLAGS := -I$(INC_DIR)

# Debug flags
DEBUG_FLAGS := -DDEBUG -g3 -O0
RELEASE_FLAGS := -O3

# Valgrind settings for memory leak detection
VALGRIND := valgrind
VALGRIND_FLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes

# Default build type
BUILD_TYPE ?= release

ifeq ($(BUILD_TYPE),debug)
    CXXFLAGS += $(DEBUG_FLAGS) $(SANITIZE)
else
    CXXFLAGS += $(RELEASE_FLAGS)
endif

# Make sure these directories exist
$(shell mkdir -p $(BUILD_DIR) $(BIN_DIR))

# Primary targets
.PHONY: all clean debug release run valgrind

all: $(TARGET)

# Debug build
debug: clean
	@$(MAKE) BUILD_TYPE=debug all

# Release build
release: clean
	@$(MAKE) BUILD_TYPE=release all

# Build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HDRS)
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) $(INC_FLAGS) -c $< -o $@

# Link the executable
$(TARGET): $(OBJS)
	@echo "Linking $@..."
	@$(CXX) $(OBJS) $(CXXFLAGS) -o $@
	@echo "Build complete!"

# Run the program
run: $(TARGET)
	@echo "Running $(TARGET)..."
	@./$(TARGET)

# Run with valgrind
valgrind: $(TARGET)
	@echo "Running valgrind..."
	@$(VALGRIND) $(VALGRIND_FLAGS) ./$(TARGET)

# Clean build files
clean:
	@echo "Cleaning build files..."
	@rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*

# Print variables for debugging Makefile
vars:
	@echo "Sources: $(SRCS)"
	@echo "Headers: $(HDRS)"
	@echo "Objects: $(OBJS)"
	@echo "Flags: $(CXXFLAGS)"

# Combined targets
.PHONY: clean-debug-run clean-debug-valgrind

clean-debug-run: clean debug run

clean-debug-valgrind: clean debug valgrind