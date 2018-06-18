file(GLOB SRCS *.cpp)


#Test all
add_executable(mainTest ${SRCS} primTest.cpp testRecursiveDivision.cpp testRecursiveBacktracker.cpp)

target_link_libraries(mainTest
        prims
        recursiveBacktracker
        recursiveDivision
        gtest
        gmock
        )

include_directories("..")

install(TARGETS mainTest DESTINATION bin)




