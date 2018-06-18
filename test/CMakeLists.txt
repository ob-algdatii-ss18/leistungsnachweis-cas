file(GLOB SRCS *.cpp)


#Test all
add_executable(recBacTest ${SRCS} testRecursiveBacktracker.cpp ../recursiveBacktracker/RecursiveBacktracker.cpp ../recursiveBacktracker/RecursiveBacktracker.h)
target_link_libraries(recBacTest PRIVATE gtest gmock)
add_test(NAME recBacTest COMMAND recBacTest)

add_executable(recDivTest ${SRCS} testRecursiveDivision.cpp)
target_link_libraries(recDivTest PRIVATE gtest gmock)
add_test(NAME recDivTest COMMAND recDivTest)

add_executable(randPrimTest ${SRCS} primTest.cpp )
target_link_libraries(randPrimTest PRIVATE gtest gmock)
add_test(NAME randPrimTest COMMAND randPrimTest)

include_directories("..")

install(TARGETS recBacTest randPrimTest recDivTest DESTINATION bin)


