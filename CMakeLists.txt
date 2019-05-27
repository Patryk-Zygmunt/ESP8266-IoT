cmake_minimum_required(VERSION 2.8)

project(xp)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(src)
add_subdirectory(test)

message(STATUS "main script finished")
