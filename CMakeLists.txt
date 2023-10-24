cmake_minimum_required(VERSION 3.21.1)
project(edge_detection C)

set(CMAKE_C_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O2")

include_directories(lib_edge/inc)
add_subdirectory(lib_edge)

add_executable(test test-edge.c)

target_link_libraries(test PRIVATE m)
target_link_libraries(test PUBLIC lib_edge)