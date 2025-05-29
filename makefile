# Compiler and flags
CXX := g++
CXXFLAGS := -Iinclude -I/usr/include/freetype2 -Wall -Wextra -std=c++17

# Libraries to link
LIBS := -lglfw -lGL -lfreetype -lX11 -pthread

# Source files
SRCS := src/Main.cpp src/Game.cpp src/Renderer.cpp src/TextRenderer.cpp libs/glad.c

# Build directory
BUILD_DIR := build

# Object files (place in build/)
OBJS := $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(filter %.cpp,$(SRCS))) \
        $(patsubst libs/%.c,$(BUILD_DIR)/%.o,$(filter %.c,$(SRCS)))

# Target executable
TARGET := $(BUILD_DIR)/wordle

all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

# Compile C++ source files to object files
$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C source files to object files
$(BUILD_DIR)/%.o: libs/%.c | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
