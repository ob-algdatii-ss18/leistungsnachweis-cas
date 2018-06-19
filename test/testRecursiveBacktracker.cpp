//
// Created by chris on 02.05.18.
//

#include "testRecursiveBacktracker.h"

using namespace std;

int xDir[49] = {0,1,2,3,4,5,6,
                0,1,2,3,4,5,6,
                0,1,2,3,4,5,6,
                0,1,2,3,4,5,6,
                0,1,2,3,4,5,6,
                0,1,2,3,4,5,6,
                0,1,2,3,4,5,6};
int yDir[49] = {0,0,0,0,0,0,0,
                1,1,1,1,1,1,1,
                2,2,2,2,2,2,2,
                3,3,3,3,3,3,3,
                4,4,4,4,4,4,4,
                5,5,5,5,5,5,5,
                6,6,6,6,6,6,6};


TEST(RecursiveBacktrackerTest, drawMaze){
    int i;
    vector<Cell *> expectedMaze;
    for(i=0; i<49; i++){
        Cell *current = new Cell();
        current->x = xDir[i];
        current->y = yDir[i];
        current->image = WALL;
        if( i == 8 || i == 10 || i == 12 || i == 22 || i == 24 || i == 26 || i == 36 || i == 38 || i == 40){
            current->image = PATH;
            current->directions = 15;
        }
        expectedMaze.push_back(current);
    }
    RecursiveBacktracker rb;
    rb.setNewcells(expectedMaze);


    ::testing::internal::CaptureStdout();

    rb.drawMaze();

    string capturedStdout = ::testing::internal::GetCapturedStdout().c_str();

    EXPECT_STREQ("########.#.#.#########.#.#.#########.#.#.########", capturedStdout.c_str());
}


TEST(RecursiveBacktrackerTest, initMaze){

    int i;
    vector<Cell * > expectedMaze;
    for(i=0; i<49; i++){
        Cell *current = new Cell();
        current->x = xDir[i];
        current->y = yDir[i];
        current->image = WALL;
        if( i == 8 || i == 10 || i == 12 || i == 22 || i == 24 || i == 26 || i == 36 || i == 38 || i == 40){
        current->image = PATH;
        current->directions = 15;
        }
        expectedMaze.push_back(current);
    }

    RecursiveBacktracker rbt;
    rbt.setWidth(7);
    rbt.setHeight(7);


    ::testing::internal::CaptureStdout();
    rbt.initMaze();

    rbt.drawMaze();

    string capturedStdout = ::testing::internal::GetCapturedStdout().c_str();

    EXPECT_STREQ("########.#.#.#########.#.#.#########.#.#.########", capturedStdout.c_str());
}


/*TEST(RecursiveBacktrackerTest, startMazeNegativeDimensions){
    RecursiveBacktracker rbt;
    rbt.setWidth(-7);
    rbt.setHeight(-7);

    std::streambuf* orig = std::cin.rdbuf();
    std::istringstream input("7\n7");
    std::cin.rdbuf(input.rdbuf());
    // tests go here
    std::cin.rdbuf(orig);
    int result = rbt.startMaze();
    EXPECT_EQ(1,result);
}

TEST(RecursiveBacktrackerTest, startMazeEvenDimensions){
    RecursiveBacktracker rbt;
    rbt.setWidth(6);
    rbt.setHeight(6);

    int result = rbt.startMaze();

    EXPECT_EQ(1,result);
}
/*

TEST(RecursiveBacktrackerTest, backtracking){
RecursiveBacktracker rB;
EXPECT_EQ(8.0,rB.testMethod());
}

 */