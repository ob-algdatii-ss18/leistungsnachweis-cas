file(GLOB SRCS *.cpp)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

#Test all
add_executable(recBacTest ${SRCS} testRecursiveBacktracker.cpp ../recursiveBacktracker/RecursiveBacktracker.cpp ../recursiveBacktracker/RecursiveBacktracker.h)
target_link_libraries(recBacTest PRIVATE gtest gmock testRecursiveBacktracker)

add_executable(recDivTest ${SRCS} testRecursiveDivision.cpp )
target_link_libraries(recDivTest PRIVATE gtest gmock testRecursiveDivision)

add_executable(randPrimTest ${SRCS} primTest.cpp ../prims/Prims.h ../prims/Prims.cpp ../prims/LabGraph.h ../prims/LabGraph.cpp)
target_link_libraries(randPrimTest PRIVATE gtest gmock prims)

include_directories("..")

install(TARGETS recBacTest randPrimTest recDivTest DESTINATION bin)

add_test(NAME recBac-Test COMMAND recBacTest)
add_test(NAME recDiv-Test COMMAND recDivTest)
add_test(NAME randPrim-Test COMMAND randPrimTest)

