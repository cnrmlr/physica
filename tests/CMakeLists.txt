# Set C++ standard
set(CMAKE_CXX_STANDARD 14)

set(TEST_ELEMENTS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/elements/test_hyperedge.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/elements/test_hypergraph.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/elements/test_vertex.cpp
)

set(TEST_UTILITY_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/utility/test_common_utility.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utility/test_identifiable_base.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utility/test_uuid.cpp
)

source_group("Elements\\Source Files" FILES ${TEST_ELEMENTS_SOURCES})
source_group("Utility\\Source Files" FILES ${TEST_UTILITY_SOURCES})

# Add the executable for tests
add_executable(Tests ${TEST_ELEMENTS_SOURCES} ${TEST_UTILITY_SOURCES})

# Link Google Test libraries
target_link_libraries(Tests GTest::gtest GTest::gtest_main)

# Link core library
target_link_libraries(Tests Core)

# Specify include directories for the test executable
target_include_directories(Tests PRIVATE
    ${PROJECT_SOURCE_DIR}/core/elements
    ${PROJECT_SOURCE_DIR}/core/utility
)

# Add tests
add_test(NAME Tests COMMAND Tests)
