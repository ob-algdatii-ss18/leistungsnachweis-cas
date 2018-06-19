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

add_test(NAME main-Test  COMMAND  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests --gtest_output=xml:report.xml)
#include_directories("..")

#install(TARGETS mainTest DESTINATION bin)




