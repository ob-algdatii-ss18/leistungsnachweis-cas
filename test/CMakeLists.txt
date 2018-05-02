file(GLOB SRCS *.cpp)


#Test all
add_executable(mainTest ${SRCS})

target_link_libraries(mainTest
        prims
        recursiveBacktracker
        recursiveDivision
        gtest
        gmock
        )

include_directories("..")

install(TARGETS mainTest DESTINATION bin)

#Test for prims
add_executable(primsTest ${SRCS})

target_link_libraries(primsTest
        prims
        gtest
        gmock
        )

include_directories("..")

install(TARGETS primsTest DESTINATION bin)

#Tests for recBac
add_executable(recursiveBacktrackerTest ${SRCS})

target_link_libraries(recursiveBacktrackerTest
        recursiveBacktracker
        gtest
        gmock
        )

include_directories("..")

install(TARGETS recursiveBacktrackerTest DESTINATION bin)

#Tests for recDiv
add_executable(recursiveDivisionTest ${SRCS})

target_link_libraries(recursiveDivisionTest
        recursiveDivision
        gtest
        gmock
        )

include_directories("..")

install(TARGETS recursiveDivisionTest DESTINATION bin)

