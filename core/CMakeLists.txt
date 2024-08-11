cmake_minimum_required(VERSION 3.10)

project(Core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ELEMENTS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/elements/hyperedge.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/elements/hypergraph.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/elements/node.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/elements/rule.cpp
)

set(FUNCTIONS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/functions/pattern_match.cpp
)

set(UTILITY_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/utility/identifiable_base.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utility/uuid.cpp
)

set(ELEMENTS_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/elements/hyperedge.h
    ${CMAKE_CURRENT_SOURCE_DIR}/elements/hypergraph.h
    ${CMAKE_CURRENT_SOURCE_DIR}/elements/node.h
    ${CMAKE_CURRENT_SOURCE_DIR}/elements/rule.h
)

set(FUNCTIONS_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/functions/pattern_match.h
)

set(UTILITY_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/utility/common_utility.h
    ${CMAKE_CURRENT_SOURCE_DIR}/utility/identifiable_base.h
    ${CMAKE_CURRENT_SOURCE_DIR}/utility/uuid.h
)

source_group("Elements\\Source Files" FILES ${ELEMENTS_SOURCES})
source_group("Elements\\Header Files" FILES ${ELEMENTS_HEADERS})
source_group("Functions\\Source Files" FILES ${FUNCTIONS_SOURCES})
source_group("Functions\\Header Files" FILES ${FUNCTIONS_HEADERS})
source_group("Utility\\Source Files" FILES ${UTILITY_SOURCES})
source_group("Utility\\Header Files" FILES ${UTILITY_HEADERS})

set(SOURCES ${ELEMENTS_SOURCES} ${FUNCTIONS_SOURCES} ${UTILITY_SOURCES})
set(HEADERS ${ELEMENTS_HEADERS} ${FUNCTIONS_HEADERS} ${UTILITY_HEADERS})

add_library(Core STATIC ${SOURCES} ${HEADERS})

target_include_directories(Core PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/elements>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/functions>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/utility>
)
