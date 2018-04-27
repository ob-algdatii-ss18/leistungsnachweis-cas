cmake_minimum_required(VERSION 3.7)
project(leistungsnachweis-cas)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(prims)
add_subdirectory(recursiveDivision)
add_subdirectory(recursiveBacktracker)

set(SOURCE_FILES testMain.cpp )
add_executable(Main ${SOURCE_FILES})

target_link_libraries(Main LINK_PUBLIC prims recursiveDivision recursiveBacktracker)

