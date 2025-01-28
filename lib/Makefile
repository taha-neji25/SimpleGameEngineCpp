# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Include directories
INCLUDES = -I../include

# Libraries to link
LIBS = -lglfw -lGL -ldl

# Source files (relative to the Makefile location)
SRCS = ../src/main.cpp ../src/glad.c

# Output executable
TARGET = main

# Build target
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(SRCS) $(LIBS)

# Clean build files
clean:
	rm -f $(TARGET)

.PHONY: all clean