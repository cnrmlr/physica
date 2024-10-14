project(physica-app)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    main.cpp
	physica.cpp
)

add_executable(physica-app ${SOURCES} ${HEADERS})

target_link_libraries(physica-app PRIVATE physica-library)