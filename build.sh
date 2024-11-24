#!/bin/bash

# Define the directory to search
PROJECT_DIR=$(pwd)

# Find all relevant files (C++ source and headers) excluding the `test/googletest/` directory
find "$PROJECT_DIR" \( -path "$PROJECT_DIR/test/googletest" -prune \) -o \
    \( -name "*.cpp" -o -name "*.h" \) -print | xargs clang-format -i

echo "Code formatted successfully."

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

# Create and navigate to the build directory
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" || exit

# Run CMake to configure the project
cmake -DCMAKE_BUILD_TYPE="$BUILD_TYPE" ..

# Build the project
cmake --build . --config "$BUILD_TYPE"

# Run the tests
ctest --output-on-failure --verbose

# Return to the root directory
cd ../..
