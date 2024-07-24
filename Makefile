# Compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -g

# Output binary
TARGET = main_test

# Source files and object files
SRCS = main_test.cpp hotel_backend.cpp reservation.cpp room_db.cpp room.cpp user_db.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target
.PHONY: all
all: $(TARGET)

# Rule to link object files into the final binary
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove generated files
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
