//
// Created by chris on 02.05.18.
//

#include "testRecursiveDivision.h"


using namespace std;

TEST(RecursiveDivisionTest, testRandomInt) {
    RecursiveDivision underTest{};

    int lower = 2;
    int upper = 9;

    for (int index = 0; index < 20; index++) {
        int random = underTest.generateRandomInt(lower, upper);
        EXPECT_TRUE(random >= lower);
        EXPECT_TRUE(random < upper);
    }
}

TEST(RecursiveDivisionTest, testRandomIntDiff) {
    RecursiveDivision underTest{};

    int lower = 2;
    int upper = 2;

    EXPECT_TRUE(underTest.generateRandomInt(lower, upper) > 0);
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

TEST(RecursiveDivisionTest, testMakeMazeOpening) {
    RecursiveDivision underTest{};

    auto **field = new bool *[6];
    for (int index = 0; index < 6; index++) {
        field[index] = new bool[6];
        for (int index2 = 0; index2 < 6; index2++) {
            field[index][index2] = true;
        }
    }

    underTest.makeMazeOpening(field, 2, 6);

    bool hasStart = false;
    bool hasEnd = false;

    for (int index = 0; index < 6; index++) {
        if (field[index][0]) {
            hasStart = true;
            break;
        }
    }
    for (int index = 0; index < 6; index++) {
        if (field[index][5]) {
            hasEnd = true;
            break;
        }
    }

    EXPECT_TRUE(hasStart);
    EXPECT_TRUE(hasEnd);
}