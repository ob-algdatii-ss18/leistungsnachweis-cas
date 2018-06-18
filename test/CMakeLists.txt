file(GLOB SRCS *.cpp)


#Test all
add_executable(recBacTest ${SRCS} testRecursiveBacktracker.cpp ../recursiveBacktracker/RecursiveBacktracker.cpp ../recursiveBacktracker/RecursiveBacktracker.h)
target_link_libraries(recBacTest PRIVATE gtest gmock)
add_test(NAME recBacTest COMMAND recBacTest)



include_directories("..")

install(TARGETS recBacTest DESTINATION bin)


