file(GLOB SRCS *.cpp)


#Test all
add_executable(recBacTest ${SRCS} ../recursiveBacktracker/RecursiveBacktracker.cpp ../recursiveBacktracker/RecursiveBacktracker.h)
add_executable(recDivTest ${SRCS} ../recursiveDivision/RecursiveDivision.cpp ../recursiveDivision/RecursiveDivision.h)
add_executable(randPrimTest ${SRCS} ../prims/Prims.cpp ../prims/Prims.h)

target_link_libraries(mainTest
        prims
        recursiveBacktracker
        recursiveDivision
        gtest
        gmock
        )

include_directories("..")

install(TARGETS recBacTest recDivTest randPrimTest DESTINATION bin)


