cmake_minimum_required(VERSION 3.10)

project(Core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ELEMENTS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/elements/hyperedge.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/elements/hypergraph.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/elements/vertex.cpp
)

set(UTILITY_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/utility/identifiable_base.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utility/uuid.cpp
)

set(ELEMENTS_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/elements/hyperedge.h
    ${CMAKE_CURRENT_SOURCE_DIR}/elements/hypergraph.h
    ${CMAKE_CURRENT_SOURCE_DIR}/elements/vertex.h
)

set(UTILITY_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/utility/common_utility.h
    ${CMAKE_CURRENT_SOURCE_DIR}/utility/identifiable_base.h
    ${CMAKE_CURRENT_SOURCE_DIR}/utility/uuid.h
)

source_group("Elements\\Source Files" FILES ${ELEMENTS_SOURCES})
source_group("Elements\\Header Files" FILES ${ELEMENTS_HEADERS})
source_group("Utility\\Source Files" FILES ${UTILITY_SOURCES})
source_group("Utility\\Header Files" FILES ${UTILITY_HEADERS})

set(SOURCES ${ELEMENTS_SOURCES} ${UTILITY_SOURCES})
set(HEADERS ${ELEMENTS_HEADERS} ${UTILITY_HEADERS})

add_library(Core STATIC ${SOURCES} ${HEADERS})

target_include_directories(Core PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/elements>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/utility>
)
