CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic
CXXLIBS = -lpthread

# Directories
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Source and object files
SRCS = $(shell C:/msys64/usr/bin/bash.exe -c "C:/msys64/usr/bin/find $(SRC_DIR) -name '*.cpp'")
REL_SRCS = $(patsubst $(SRC_DIR)/,, $(SRCS))
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(REL_SRCS))

# Binary executable
TARGET = $(BIN_DIR)/library.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	@echo "Linking $@ ..."
	@$(CXX) $(CXXFLAGS) $^ -o $@ $(CXXLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $< -> $@ ..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean run

clean:
	@echo "Cleaning up ..."
	@rm -rf $(BUILD_DIR)

run: $(TARGET)
	@echo "Running $<"
	@./$<