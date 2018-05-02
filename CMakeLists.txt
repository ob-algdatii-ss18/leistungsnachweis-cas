cmake_minimum_required(VERSION 3.7)
project(leistungsnachweis-cas)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(prims)
add_subdirectory(recursiveDivision)
add_subdirectory(recursiveBacktracker)

set(SOURCE_FILES testMain.cpp)
add_executable(Main ${SOURCE_FILES})

target_link_libraries(Main LINK_PUBLIC prims recursiveDivision recursiveBacktracker)

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

add_subdirectory(test)

enable_testing()

add_test(primTest test/primTest --gtest_output=xml:report.xml)
add_test(testRecursiveBacktracker test/testRecursiveBacktracker --gtest_output=xml:report.xml)
add_test(testRecursiveDivision test/testRecursiveDivision --gtest_output=xml:report.xml)