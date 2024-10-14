cmake_minimum_required(VERSION 3.10)

project(physica-library)

add_compile_options(/std:c++17)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(PRIVATE ${CMAKE_SOURCE_DIR}/include)

set(FUNCTIONS_SOURCES
    functions/pattern_match.cpp
)

set(STRUCTURES_SOURCES
    structures/hyperedge.cpp
    structures/hypergraph.cpp
    structures/node.cpp
    structures/rule.cpp
)

set(UTILITY_SOURCES
    utility/identifiable_base.cpp
    utility/uuid.cpp
)

set(FUNCTIONS_HEADERS
    ${CMAKE_SOURCE_DIR}/include/physica/library/functions/pattern_match.h
)

set(STRUCTURES_HEADERS
    ${CMAKE_SOURCE_DIR}/include/physica/library/structures/hyperedge.h
    ${CMAKE_SOURCE_DIR}/include/physica/library/structures/hypergraph.h
    ${CMAKE_SOURCE_DIR}/include/physica/library/structures/node.h
    ${CMAKE_SOURCE_DIR}/include/physica/library/structures/rule.h
)

set(UTILITY_HEADERS
    ${CMAKE_SOURCE_DIR}/include/physica/library/utility/common_utility.h
    ${CMAKE_SOURCE_DIR}/include/physica/library/utility/identifiable_base.h
    ${CMAKE_SOURCE_DIR}/include/physica/library/utility/uuid.h
)

source_group("Functions\\Source Files" FILES ${FUNCTIONS_SOURCES})
source_group("Functions\\Header Files" FILES ${FUNCTIONS_HEADERS})
source_group("Structures\\Source Files" FILES ${STRUCTURES_SOURCES})
source_group("Structures\\Header Files" FILES ${STRUCTURES_HEADERS})
source_group("Utility\\Source Files" FILES ${UTILITY_SOURCES})
source_group("Utility\\Header Files" FILES ${UTILITY_HEADERS})

set(SOURCES ${STRUCTURES_SOURCES} 
            ${FUNCTIONS_SOURCES} 
            ${UTILITY_SOURCES}
            model.cpp
)

set(HEADERS ${STRUCTURES_HEADERS} 
            ${FUNCTIONS_HEADERS}  
            ${UTILITY_HEADERS}
            ${CMAKE_SOURCE_DIR}/include/physica/library/physica.h
            ${CMAKE_SOURCE_DIR}/include/physica/library/model.h
)

add_library(physica-library STATIC ${SOURCES} ${HEADERS})

target_include_directories(physica-library PUBLIC
	$<BUILD_INTERFACE:functions>
    $<BUILD_INTERFACE:structures>
    $<BUILD_INTERFACE:utility>
)
