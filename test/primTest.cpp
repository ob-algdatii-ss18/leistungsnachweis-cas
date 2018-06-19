//
// Created by chris on 02.05.18.
//

#include "primTest.h"

using namespace std;

TEST(primTest, useHeader) {
    LabGraph underTest{};
}

TEST(primTest, innitTest){
    LabGraph * testG = new LabGraph();
    testG->initGraph();
    EXPECT_EQ(LG_WIDTH*LG_HEIGHT, testG->graphNodes.size());
    //corners have zero edges in collection
    EXPECT_EQ(0,testG->graphNodes[0]->edges.size());
    EXPECT_EQ(0,testG->graphNodes[LG_WIDTH-1]->edges.size());
    EXPECT_EQ(0,testG->graphNodes[(LG_HEIGHT-1)*LG_WIDTH]->edges.size());
    EXPECT_EQ(0,testG->graphNodes[testG->graphNodes.size()-1]->edges.size());
    //border has 1 that connects t the maze and are marked visited before maze generation
    for(int w =1; w< LG_WIDTH-1;w++){
        EXPECT_EQ(1,testG->graphNodes[w]->edges.size());
        EXPECT_TRUE(testG->graphNodes[w]->isBorder());
        EXPECT_TRUE(testG->graphNodes[w]->isVisited());
        EXPECT_EQ(1,testG->graphNodes[w + (LG_WIDTH * (LG_HEIGHT-1))]->edges.size());
        EXPECT_TRUE(testG->graphNodes[w + (LG_WIDTH * (LG_HEIGHT-1))]->isBorder());
        EXPECT_TRUE(testG->graphNodes[w + (LG_WIDTH * (LG_HEIGHT-1))]->isVisited());
    }
    for(int h=1; h < LG_HEIGHT-1; h++){
        EXPECT_EQ(1,testG->graphNodes[h * LG_WIDTH]->edges.size());
        EXPECT_TRUE(testG->graphNodes[h * LG_WIDTH]->isBorder());
        EXPECT_TRUE(testG->graphNodes[h * LG_WIDTH]->isVisited());
        EXPECT_EQ(1,testG->graphNodes[h * LG_WIDTH + LG_HEIGHT - 1]->edges.size());
        EXPECT_TRUE(testG->graphNodes[h * LG_WIDTH + LG_HEIGHT - 1]->isBorder());
        EXPECT_TRUE(testG->graphNodes[h * LG_WIDTH + LG_HEIGHT - 1]->isVisited());
    }
    //Inner sides have 4 connecting edges and are unvisited
    for(int h=1; h < LG_HEIGHT-1; h++){
        for(int w =1; w< LG_WIDTH-1;w++){
            EXPECT_EQ(4,testG->graphNodes[h*LG_WIDTH + w]->edges.size());
            EXPECT_TRUE(!testG->graphNodes[h*LG_WIDTH + w]->isVisited());
            EXPECT_TRUE(testG->graphNodes[h * LG_WIDTH + LG_HEIGHT - 1]->isBorder());
        }
    }
}
