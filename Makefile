# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -Werror
DEBUG_FLAGS := -g -O0 -DDEBUG

# Directories
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
INC_DIR := include

# Files
SRCS := $(wildcard $(SRC_DIR)/*.c)
HDRS := $(wildcard $(INC_DIR)/*.h)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TARGET := $(BIN_DIR)/tpn

# Valgrind configuration
VALGRIND := valgrind
VALGRIND_FLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes

# Default build
all: release

# Create necessary directories
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(BUILD_DIR) $(BIN_DIR) $(TARGET)

# Release build
release: $(BUILD_DIR) $(BIN_DIR) $(TARGET)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HDRS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Link object files
$(TARGET): $(OBJS)
	@echo "Linking $@..."
	@$(CC) $(OBJS) -o $@

# Run the program
run: $(TARGET)
	@echo "Running $(TARGET)..."
	@./$(TARGET)

# Run with Valgrind
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
	@echo "Flags: $(CFLAGS)"

# Combined targets
.PHONY: clean-debug-run clean-debug-valgrind
clean-debug-run: clean debug run
clean-debug-valgrind: clean debug valgrind

.PHONY: all debug release clean vars run valgrind