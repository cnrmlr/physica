cmake_minimum_required(VERSION 3.16)

project(physica)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES 
   pattern_match.cpp
)

add_library(physica STATIC ${SOURCES})
include_directories(PRIVATE ${CMAKE_SOURCE_DIR}/include)