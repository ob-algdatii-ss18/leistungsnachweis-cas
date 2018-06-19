file(GLOB SRCS *.cpp)


#Test all
add_executable(mainTest main.cpp primTest.cpp testRecursiveBacktracker.cpp testRecursiveDivision.cpp)

target_link_libraries(mainTest
        prims
        recursiveBacktracker
        recursiveDivision
        gtest
        gmock
        )


#include_directories("..")

#install(TARGETS mainTest DESTINATION bin)




