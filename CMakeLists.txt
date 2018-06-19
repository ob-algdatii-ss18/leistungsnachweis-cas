cmake_minimum_required(VERSION 3.8.2)
project(leistungsnachweis-cas)



set(CMAKE_CXX_STANDARD 11)

SET(COVERAGE OFF CACHE BOOL "Coverage")

add_subdirectory(prims)
add_subdirectory(recursiveDivision)
add_subdirectory(recursiveBacktracker)

set(SOURCE_FILES testMain.cpp)
add_executable(Main ${SOURCE_FILES})
#include_directories(D:\\Programme\\gtest\\googletest-master\\googletest-master\\googletes\\include D:\\Programme\\gtest\\googletest-master\\googletest-master\\googletest)

target_link_libraries(Main LINK_PUBLIC prims recursiveDivision recursiveBacktracker)

if (COVERAGE)
    target_compile_options(test PRIVATE --coverage)
    target_link_libraries(test PRIVATE --coverage)
endif()

#Gtests

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
        "${CMAKE_BINARY_DIR}/googletest-build")



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")


enable_testing()

add_subdirectory(test)

#add_test(prims-Test test/primsTest --gtest_output=xml:report.xml)
#add_test(recBac-Test test/recursiveBacktrackerTest --gtest_output=xml:report.xml)
#add_test(recDiv-Test test/recursiveDivisionTest --gtest_output=xml:report.xml)
add_test(main-Test test/main-Test --gtest_output=xml:report.xml)
#add_test(randPrim-Test test/randPrimTest --gtest_output=xml:report.xml)

