cmake_minimum_required(VERSION 3.15)
project(Graphica)

# Option to build tests
option(BUILD_TESTS "Build tests" OFF)

# Add core and impl subdirectories
add_subdirectory(core)
add_subdirectory(impl)

# Enable tests only if Google Test is found
if(BUILD_TESTS)
    find_package(GTest CONFIG REQUIRED)
    if(GTest_FOUND)
        enable_testing()
        add_subdirectory(tests)
    else()
        message(WARNING "Google Test not found. Tests will not be built.")
    endif()
endif()
