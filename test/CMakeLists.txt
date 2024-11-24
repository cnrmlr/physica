cmake_minimum_required(VERSION 3.16)

add_subdirectory(googletest)

function(addTest TEST_NAME TEST_SOURCE)
  add_executable(${TEST_NAME} ${TEST_SOURCE})
  target_link_libraries(${TEST_NAME} gtest_main physica)
  add_test(${TEST_NAME} ${TEST_NAME})
  target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
endfunction()

include_directories(./googletest/googletest/)
include_directories(PRIVATE ${CMAKE_SOURCE_DIR}/include)

addTest(test-hypergraph test_hypergraph.cpp)
