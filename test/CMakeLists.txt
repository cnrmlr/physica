# Set C++ standard
set(CMAKE_CXX_STANDARD 23)

set(TEST_SOURCES
    test_hypergraph.cpp
)

source_group("Source Files" FILES ${TEST_SOURCES})

# Add the executable for tests
add_executable(physica-test ${TEST_SOURCES})

# Link Google Test libraries
target_link_libraries(physica-test GTest::gtest GTest::gtest_main)

# Link core library
target_link_libraries(physica-test physica-library)

# Specify include directories for the test executable
target_include_directories(physica-test PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Add tests
add_test(NAME physica-test COMMAND physica-test)
