cmake_minimum_required(VERSION 3.15)
project(Physica)

# Option to build tests
option(BUILD_TESTS "Build tests" OFF)

add_subdirectory(src/app)
add_subdirectory(src/library)

# Enable tests only if Google Test is found
if(BUILD_TESTS)
    find_package(GTest CONFIG REQUIRED)
    if(GTest_FOUND)
        enable_testing()
        add_subdirectory(test)
    else()
        message(WARNING "Google Test not found. Tests will not be built.")
    endif()
endif()
