CXX = g++
CXXFLAGS = -Wall -Wextra -g -O2 -std=c++17 -Iinclude
LDFLAGS =

# Find all .cpp files in the src directory
SRCS = $(wildcard src/*.cpp)
# Generate object file names by replacing src/%.cpp with obj/%.o
OBJS = $(patsubst src/%.cpp,obj/%.o,$(SRCS))

TARGET = tinyshell.exe
OBJDIR = obj

# Default target
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

# Rule to compile source files into object files
# Creates the object directory if it doesn't exist
$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to create the object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean rule
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean

