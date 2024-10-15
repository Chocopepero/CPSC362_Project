#!/bin/bash

# Build the Vite frontend
echo "Building Vite frontend..."
cd CPSC362Front-main/client  # Replace with your Vite frontend directory
npm install
npm run build

# Build the C++ backend
echo "Building C++ backend..."
cd ../../  # Replace with your C++ backend directory
cmake .
make

echo "Build process completed."
