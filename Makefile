# Compiler and compiler flags
CXX = clang++
CXXFLAGS = -Wall -std=c++17

# Output binary
TARGET = main_test

# Source files and object files
SRCS = main_test.cpp hotel_backend.cpp reservation.cpp room_db.cpp room.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Rule to link object files into the final binary
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove generated files
clean:
	rm -f $(OBJS) $(TARGET)
