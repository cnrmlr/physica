# impl/CMakeLists.txt
project(Impl)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add source files
set(SOURCES
    src/main.cpp
    src/instance.cpp
)

# Add header files
set(HEADERS
    include/instance.h
)

# Create executable and link with the core library
add_executable(Impl ${SOURCES} ${HEADERS})
target_link_libraries(Impl PRIVATE Core)

# Make the include directories from Core available to this project
target_include_directories(Impl PRIVATE ${PROJECT_SOURCE_DIR}/core/include)
