file(GLOB SRCS *.cpp)


#Test all
add_executable(mainTest ${SRCS} testRecursiveDivision.cpp testRecursiveBacktracker.cpp primTest.cpp)

target_link_libraries(mainTest
        prims
        recursiveBacktracker
        recursiveDivision
        gtest
        gmock
        )

include_directories("..")

install(TARGETS mainTest DESTINATION bin)


enable_testing()

