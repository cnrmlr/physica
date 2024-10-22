#!/bin/bash

# Set the build directory
BUILD_DIR="build"

# Create the build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
  mkdir "$BUILD_DIR"
fi

# Navigate to the build directory
cd "$BUILD_DIR"

# Run CMake to configure the project with GCC and use C++17
cmake .. -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_CXX_STANDARD=23

# Build the project
make

# Return to the root directory
cd ..

# Output the result
echo "Build completed. Executables can be found in the build directory."
