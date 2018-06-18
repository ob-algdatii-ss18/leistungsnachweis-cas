file(GLOB SRCS *.cpp)


#Test all
add_executable(mainTest ${SRCS} ../recursiveDivision/RecursiveDivision.cpp ../recursiveDivision/RecursiveDivision.h)

target_link_libraries(mainTest
        prims
        recursiveBacktracker
        recursiveDivision
        gtest
        gmock
        )

include_directories("..")

install(TARGETS mainTest DESTINATION bin)


