cmake_minimum_required(VERSION 3.16)
project(test)

# Include GoogleTest from Conan
find_package(GTest REQUIRED)

# Function to easily add tests
function(addTest TEST_NAME TEST_SOURCE)
  add_executable(${TEST_NAME} ${TEST_SOURCE})
  target_link_libraries(${TEST_NAME} PRIVATE GTest::GTest GTest::Main)
  add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
  target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
endfunction()

# Add the tests
addTest(test-hypergraph test_hypergraph.cpp)
