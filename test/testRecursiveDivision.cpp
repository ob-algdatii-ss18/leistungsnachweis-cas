//
// Created by chris on 02.05.18.
//

#include "testRecursiveDivision.h"

using namespace std;

TEST(RecursiveDivisionTest, simpleTest){
    RecursiveDivision rD;
    EXPECT_EQ(3,rD.testMethod());

}
