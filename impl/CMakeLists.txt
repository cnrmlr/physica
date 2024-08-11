project(Impl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
    main.cpp
    graphica.cpp
)

set(HEADERS
    graphica.h
)

add_executable(Impl ${SOURCES} ${HEADERS})
target_link_libraries(Impl PRIVATE Core)

target_include_directories(Impl PRIVATE ${PROJECT_SOURCE_DIR}/core/elements 
                                        ${PROJECT_SOURCE_DIR}/core/utility
)
