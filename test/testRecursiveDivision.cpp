//
// Created by chris on 02.05.18.
//

#include "testRecursiveDivision.h"


using namespace std;

TEST(RecursiveDivisionTest, simpleTest) {
    RecursiveDivision rD;
    EXPECT_EQ(3, rD.testMethod());
}

TEST(RecursiveDivisionTest, chooseOrientation) {
    RecursiveDivision rD;

    EXPECT_EQ(RecursiveDivision::HORIZONTAL, rD.chooseOrientation(3, 5));
    EXPECT_EQ(RecursiveDivision::VERTICAL, rD.chooseOrientation(5, 3));

    // Test random orientation:
    int counter = 0;
    bool randomOrientation = false;

    // init orientation.
    int orientation = rD.chooseOrientation(5, 5);

    for (counter; counter < 5; counter++) {
        if (orientation != rD.chooseOrientation(5, 5)) {
            randomOrientation = true;
        }
    }

    EXPECT_TRUE(randomOrientation);
}

TEST(RecursiveDivisionTest, initMaze) {
    RecursiveDivision rD;

    auto* maze = rD.initMaze(10, 10);
//    EXPECT_EQ(10, sizeof(maze));
//
//    for (int index = 0; index < 10; index++) {
//        EXPECT_EQ(10, sizeof(&maze[index]));
//    }
}