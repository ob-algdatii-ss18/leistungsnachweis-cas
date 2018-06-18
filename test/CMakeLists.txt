file(GLOB SRCS *.cpp)


#Test all
add_executable(mainTest ${SRCS} ../recursiveDivision/RecursiveDivision.cpp ../recursiveDivision/RecursiveDivision.h ../recursiveBacktracker/RecursiveBacktracker.cpp ../recursiveBacktracker/RecursiveBacktracker.h)

target_link_libraries(mainTest
        prims
        recursiveBacktracker
        recursiveDivision
        gtest
        gmock
        )

include_directories("..")

install(TARGETS mainTest DESTINATION bin)


