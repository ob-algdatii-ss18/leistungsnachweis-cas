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

TEST(RecursiveDivisionTest, testDrawMaze) {
    RecursiveDivision underTest{};
    underTest.debugMode = true;

    auto **field = new bool *[2];
    for (int i = 0; i < 2; i++) {
        field[i] = new bool[2];
        for (int j = 0; j < 2; j++) {
            field[i][j] = true;
        }
    }

    std::stringstream ss;
    underTest.drawMaze(field, ss);

    EXPECT_EQ(ss.str(), "\n");
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

TEST(RecursiveDivisionTest, testDivideVertical) {
    RecursiveDivision underTest{};
    underTest.debugMode = true;

    auto **field = new bool *[3];
    for (int i = 0; i < 3; i++) {
        field[i] = new bool[3];
        for (int j = 0; j < 3; j++) {
            field[i][j] = false;
        }
    }

    underTest.divideVertical(field, 0, 2, 0, 2);

    bool hasWall1 = false;
    bool hasWall2 = false;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (field[i][j]) {
                if (!hasWall1 && !hasWall2) {
                    hasWall1 = true;
                } else if (hasWall1 && !hasWall2) {
                    hasWall2 = true;
                } else {
                    // There should be only 2 walls in a 3x3 field!
                    EXPECT_TRUE(false);
                }
            }
        }
    }

    EXPECT_TRUE(hasWall1);
    EXPECT_TRUE(hasWall2);
}

TEST(RecursiveDivisionTest, testDivideHorizontal) {
    RecursiveDivision underTest{};
    underTest.debugMode = true;

    auto **field = new bool *[3];
    for (int i = 0; i < 3; i++) {
        field[i] = new bool[3];
        for (int j = 0; j < 3; j++) {
            field[i][j] = false;
        }
    }

    underTest.divideHorizontal(field, 0, 2, 0, 2);

    bool hasWall1 = false;
    bool hasWall2 = false;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (field[i][j]) {
                if (!hasWall1 && !hasWall2) {
                    hasWall1 = true;
                } else if (hasWall1 && !hasWall2) {
                    hasWall2 = true;
                } else {
                    // There should be only 2 walls in a 3x3 field!
                    EXPECT_TRUE(false);
                }
            }
        }
    }

    EXPECT_TRUE(hasWall1);
    EXPECT_TRUE(hasWall2);
}

TEST(RecursiveDivisionTest, testDivideFieldCase1) {
    RecursiveDivision underTest{};
    underTest.debugMode = true;

    auto **field = new bool *[10];
    for (int i = 0; i < 10; i++) {
        field[i] = new bool[10];
        for (int j = 0; j < 10; j++) {
            field[i][j] = false;
        }
    }
    underTest.divideField(field, 0, 5, 0, 3);
    bool hasWall = false;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (field[i][j]) {
                if (!hasWall) {
                    hasWall = true;
                    break;
                }
            }
        }
    }

    EXPECT_TRUE(hasWall);
}

TEST(RecursiveDivisionTest, testDivideFieldCase2) {
    RecursiveDivision underTest{};
    underTest.debugMode = true;

    auto **field = new bool *[10];
    for (int i = 0; i < 10; i++) {
        field[i] = new bool[10];
        for (int j = 0; j < 10; j++) {
            field[i][j] = false;
        }
    }
    underTest.divideField(field, 0, 3, 0, 5);
    bool hasWall = false;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (field[i][j]) {
                if (!hasWall) {
                    hasWall = true;
                    break;
                }
            }
        }
    }

    EXPECT_TRUE(hasWall);
}

TEST(RecursiveDivisionTest, testDivideFieldCase3) {
    RecursiveDivision underTest{};
    underTest.debugMode = true;

    auto **field = new bool *[10];
    for (int i = 0; i < 10; i++) {
        field[i] = new bool[10];
        for (int j = 0; j < 10; j++) {
            field[i][j] = false;
        }
    }

    // Because of random orientation: execute several times:

    for (int iteration = 0; iteration < 10; iteration++) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                field[i][j] = false;
            }
        }
        underTest.divideField(field, 0, 3, 0, 3);
        bool hasWall = false;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (field[i][j]) {
                    if (!hasWall) {
                        hasWall = true;
                        break;
                    }
                }
            }
        }
        EXPECT_TRUE(hasWall);
    }
}

TEST(RecursiveDivisionTest, testDivideFieldCase4) {
    RecursiveDivision underTest{};
    underTest.debugMode = true;

    auto **field = new bool *[10];
    for (int i = 0; i < 10; i++) {
        field[i] = new bool[10];
        for (int j = 0; j < 10; j++) {
            field[i][j] = false;
        }
    }
    underTest.divideField(field, 0, 4, 0, 1);
    bool hasWall = false;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (field[i][j]) {
                if (!hasWall) {
                    hasWall = true;
                    break;
                }
            }
        }
    }
    EXPECT_TRUE(hasWall);
}

TEST(RecursiveDivisionTest, testDivideFieldCase5) {
    RecursiveDivision underTest{};
    underTest.debugMode = true;

    auto **field = new bool *[10];
    for (int i = 0; i < 10; i++) {
        field[i] = new bool[10];
        for (int j = 0; j < 10; j++) {
            field[i][j] = false;
        }
    }
    underTest.divideField(field, 0, 1, 0, 4);
    bool hasWall = false;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (field[i][j]) {
                if (!hasWall) {
                    hasWall = true;
                    break;
                }
            }
        }
    }
    EXPECT_TRUE(hasWall);
}

TEST(RecursiveDivisionTest, testDivideFieldCase6) {
    RecursiveDivision underTest{};
    underTest.debugMode = true;

    auto **field = new bool *[10];
    for (int i = 0; i < 10; i++) {
        field[i] = new bool[10];
        for (int j = 0; j < 10; j++) {
            field[i][j] = false;
        }
    }
    underTest.divideField(field, 0, 1, 0, 1);
    bool hasWall = false;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (field[i][j]) {
                if (!hasWall) {
                    hasWall = true;
                    break;
                }
            }
        }
    }
    EXPECT_FALSE(hasWall);
}

TEST(RecursiveDivisionTest, testInitMaze) {
    RecursiveDivision underTest{};
    underTest.debugMode = true;

    int width = 10;
    int height = 10;

    bool **field = underTest.initMaze(width, height);

    for (int index = 0; index < 10; index++) {
        // Top border
        EXPECT_TRUE(field[0][index]);
        // Bottom border
        EXPECT_TRUE(field[9][index]);
        // Left border
        EXPECT_TRUE(field[index][0]);
        // Right border
        EXPECT_TRUE(field[index][9]);
    }
}


TEST(RecursiveDivisionTest, testGenerateMaze) {
    RecursiveDivision underTest{};
    underTest.debugMode = true;

    std::istringstream ss("3\n3\n");
    underTest.generateMaze(ss);
}
