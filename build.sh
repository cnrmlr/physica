#!/bin/bash

# Format all C++ and header files using clang-format
find . -name "*.cpp" -o -name "*.h" | xargs clang-format -i

# Default build type
BUILD_TYPE="Release"

# Check if an argument is provided for build type
if [ $# -gt 0 ]; then
    BUILD_TYPE="$1"
fi

# Validate build type
if [[ "$BUILD_TYPE" != "Debug" && "$BUILD_TYPE" != "Release" && "$BUILD_TYPE" != "RelWithDebInfo" && "$BUILD_TYPE" != "MinSizeRel" ]]; then
    echo "Invalid build type: $BUILD_TYPE"
    echo "Valid options are: Debug, Release, RelWithDebInfo, MinSizeRel"
    exit 1
fi

echo "Building with configuration: $BUILD_TYPE"

# Define build directories
BUILD_DIR="build"
TEST_BUILD_DIR="build/test"
CONAN_DIR="$BUILD_DIR/conan"

# Install Conan dependencies
mkdir -p "$CONAN_DIR"
conan install . --build=missing -pr:b="$BUILD_TYPE" -pr:h=default -of="$CONAN_DIR"

# Create and navigate to the build directory
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" || exit

# Run CMake to configure the project using Conan's toolchain
cmake -DCMAKE_TOOLCHAIN_FILE="$CONAN_DIR/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" ..

# Build the project
cmake --build . --config "$BUILD_TYPE"

# Navigate back to the root directory
cd ..

# Build the tests
mkdir -p "$TEST_BUILD_DIR"
cd "$TEST_BUILD_DIR" || exit

# Run CMake to configure the tests using Conan's toolchain
cmake -DCMAKE_TOOLCHAIN_FILE="conan/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" ../../test

# Build the test targets
cmake --build . --config "$BUILD_TYPE"

# Run the tests
ctest --output-on-failure

# Return to the root directory
cd ../..
