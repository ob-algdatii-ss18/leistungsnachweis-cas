add_library(prims LabGraph.cpp LabGraph.h)
target_include_directories(prims PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(prims
        gtest)