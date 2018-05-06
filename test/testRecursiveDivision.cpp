//
// Created by chris on 02.05.18.
//

#include "testRecursiveDivision.h"


using namespace std;

TEST(RecursiveDivisionTest, simpleTest){
    RecursiveDivision rD;
    EXPECT_EQ(3, rD.testMethod());
}

TEST(RecursiveDivisionTest, chooseOrientation){
    RecursiveDivision rD;

    EXPECT_EQ(RecursiveDivision::HORIZONTAL,  rD.chooseOrientation(3,5));
    EXPECT_EQ(RecursiveDivision::VERTICAL,  rD.chooseOrientation(5,3));
}