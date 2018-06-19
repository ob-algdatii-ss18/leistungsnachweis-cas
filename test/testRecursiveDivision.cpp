//
// Created by chris on 02.05.18.
//

#include "testRecursiveDivision.h"


using namespace std;

TEST(RecursiveDivisionTest, testRandomInt) {
    RecursiveDivision underTest{};
    int lower = 2;
    int upper = 9;

    int lastInt = 0;
    for (int index = 0; index < 10; index++) {
        int random = underTest.generateRandomInt(lower, upper);
        EXPECT_TRUE(random >= lower);
        EXPECT_TRUE(random < upper);
        EXPECT_TRUE(random != lastInt);
        lastInt = random;
    }
}

TEST(RecursiveDivisionTest, testRandomBool) {
    RecursiveDivision underTest{};

    bool firstTry = underTest.generateRandomBoolean();
    bool nextTry = underTest.generateRandomBoolean();
    for (int index = 10; index >= 0; index--) {
        nextTry = underTest.generateRandomBoolean();
        if (firstTry != nextTry) {
            break;
        }
    }

    EXPECT_NE (firstTry, nextTry);
}

//
//std::stringstream ss;
//toBeTested(ss);
//assert(ss.str() == "this is the correct output");

//
//TEST(RecursiveDivisionTest, simpleTest) {
//    RecursiveDivision rD;
//    EXPECT_EQ(3, rD.testMethod());
//}
//
//TEST(RecursiveDivisionTest, chooseOrientation) {
//    RecursiveDivision rD;
//
//    EXPECT_EQ(RecursiveDivision::HORIZONTAL, rD.chooseOrientation(3, 5));
//    EXPECT_EQ(RecursiveDivision::VERTICAL, rD.chooseOrientation(5, 3));
//
//    // Test random orientation:
//    int counter = 0;
//    bool randomOrientation = false;
//
//    // init orientation.
//    int orientation = rD.chooseOrientation(5, 5);
//
//    for (counter; counter < 5; counter++) {
//        if (orientation != rD.chooseOrientation(5, 5)) {
//            randomOrientation = true;
//        }
//    }
//
//    EXPECT_TRUE(randomOrientation);
//}

TEST(RecursiveDivisionTest, initMaze) {
    RecursiveDivision rD;

    auto *maze = rD.initMaze(10, 10);
//    EXPECT_EQ(10, sizeof(maze));
//
//    for (int index = 0; index < 10; index++) {
//        EXPECT_EQ(10, sizeof(&maze[index]));
//    }
}