CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic -MMD -MP -I. -Iftxui/include
CXXLIBS = -Lftxui/lib -lftxui

# Directories
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
DEP_DIR = $(BUILD_DIR)/dep
BIN_DIR = $(BUILD_DIR)/bin

# Source and object files
SRCS = $(shell C:/msys64/usr/bin/bash.exe -c "C:/msys64/usr/bin/find $(SRC_DIR) -name '*.cpp'")
SRCS := $(patsubst $(SRC_DIR)/%, %, $(SRCS))
OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))
DEPS = $(patsubst $(OBJ_DIR)/%.o, $(DEP_DIR)/%.d, $(OBJS))

TARGET := $(BIN_DIR)/lib.exe

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	@echo "Linking $@ ..."
	@$(CXX) $(CXXFLAGS) $^ $(CXXLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(eval DEP = $(patsubst $(OBJ_DIR)/%.o, $(DEP_DIR)/%.d, $@))
	@mkdir -p $(dir $@) $(dir $(DEP))
	@echo "Compiling $< ..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@ -MF $(DEP)

-include $(DEPS)

clean:
	@echo "Cleaning up ..."
	@rm -rf $(BUILD_DIR)

run: $(TARGET)
	@echo "Running $< ..."
	@pwsh -Command "Start-Process $(subst /,\, $(patsubst /c/%, C:/%, $(abspath $<)))"