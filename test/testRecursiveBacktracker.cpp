//
// Created by chris on 02.05.18.
//

#include "testRecursiveBacktracker.h"

using namespace std;

TEST(RecursiveBacktrackerTest, simpleTest){
    RecursiveBacktracker rB;
    EXPECT_EQ(8.0,rB.testMethod());
}
