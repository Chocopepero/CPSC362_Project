#!/bin/bash


# Build the C++ backend
echo "Building C++ backend..."
cd ../../  # Replace with your C++ backend directory
cmake .
make

echo "Build process completed."
