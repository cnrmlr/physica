cmake_minimum_required(VERSION 3.16)
enable_testing()

project(physica)

# Include Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Add subdirectories
add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(test)
