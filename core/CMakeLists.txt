# core/CMakeLists.txt
project(Core)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add source files
set(SOURCES
    src/hyperedge.cpp
    src/hypergraph.cpp
    src/hypervertex.cpp
    src/identifiable_base.cpp
    src/uuid.cpp
)

# Add header files
set(HEADERS
    include/hyperedge.h
    include/hypergraph.h
    include/hypervertex.h
    include/identifiable_base.h
    include/type_defs.h
    include/uuid.h
)

# Create static library
add_library(Core STATIC ${SOURCES} ${HEADERS})

# Make the include directory available to other projects
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
