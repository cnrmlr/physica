cmake_minimum_required(VERSION 3.16)

project(physica-tests)

# Add GoogleTest
add_subdirectory(googletest)

# Add include directories for headers
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(./googletest/googletest/)

# List all test source files
set(TEST_SOURCES
    test_hypergraph.cpp
    main.cpp
)

# Add the test executable
add_executable(physica-tests ${TEST_SOURCES})

# Link GoogleTest and other required libraries
target_link_libraries(physica-tests PRIVATE gtest_main)

# Add tests to CTest
add_test(NAME physica-tests COMMAND physica-tests)
