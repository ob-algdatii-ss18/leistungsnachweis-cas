//
// Created by chris on 02.05.18.
//

#include "primTest.h"

using namespace std;

TEST(primTest, useHeader) {
    LabGraph underTest{};
}

TEST(primTest, innitTestNodes){
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
TEST(primTest, innitTestEdges){
    LabGraph * testG = new LabGraph();
    testG->initGraph();
    int vis =0, border = 0, conectBorder =0, hor =0;
    EXPECT_EQ((LG_WIDTH-1)*LG_HEIGHT*2, testG->graphEdges.size());
    for(auto e : testG->graphEdges){
        if(e->isBorder())border++;
        if(e->connectBorder())conectBorder++;
        if(e->isVisited())vis++;
        if(e->isHorizontal())hor++;
    }
    EXPECT_EQ(2*(LG_WIDTH-1)+2*(LG_HEIGHT-1),border);
    EXPECT_EQ(2*(LG_WIDTH-2)+2*(LG_HEIGHT-2),conectBorder);
    EXPECT_EQ(border+conectBorder,vis);
    EXPECT_EQ(testG->graphEdges.size()/2,hor);


}
TEST(primTest, compareEdgesTest){
    auto b = new LabGraph::Edge(2);
    auto d = new LabGraph::Edge(33);
    auto c = new LabGraph::Edge(3);
    auto a = new LabGraph::Edge(1);
    auto e = new LabGraph::Edge(7);
    priority_queue<LabGraph::Edge *, vector<LabGraph::Edge*>, LabGraph::Edge::CompareEdges> edges;
    edges.push(b);
    edges.push(d);
    edges.push(c);
    edges.push(a);
    edges.push(e);
    EXPECT_EQ(a, edges.top());
    edges.pop();
    EXPECT_EQ(b, edges.top());
    edges.pop();
    EXPECT_EQ(c, edges.top());
    edges.pop();
    EXPECT_EQ(e, edges.top());
    edges.pop();
    EXPECT_EQ(d, edges.top());
    edges.pop();
    EXPECT_TRUE(edges.empty());
}
TEST(primTest, setDimensionsTest){
    LabGraph * testG = new LabGraph(LG_WIDTH,LG_HEIGHT);
    EXPECT_EQ(testG->height, LG_HEIGHT);
    EXPECT_EQ(testG->width, LG_WIDTH);
    testG->setDimensions(10,20);
    EXPECT_EQ(testG->height, 20);
    EXPECT_EQ(testG->width, 10);
}
TEST(primTest, setLabTest){
    bool toggle = true;
    LabGraph * testG = new LabGraph();
    auto **mazeField = new bool *[20];
    for (int i = 0; i < 20; i++) {
        mazeField[i] = new bool[20];
    }
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            mazeField[i][j] = toggle = !toggle;
        }
    }
    testG->setDimensions(20,20);
    testG->setLab(mazeField);
    toggle=true;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            EXPECT_EQ(toggle = !toggle, testG->graphNodes[i*20+j]->color == BLACK);
        }
    }
}
TEST(primTest, otherEndTest){
    LabGraph::Node *a = new LabGraph::Node(1,1,true);
    LabGraph::Node *b = new LabGraph::Node(2,2);
    LabGraph::Edge *e1 = new LabGraph::Edge(a,b,2);
    EXPECT_EQ(a,e1->otherEnd(b));
    EXPECT_EQ(b,e1->otherEnd(a));
}
TEST(primTest, primsAlgoTestNodes){
    LabGraph * testG = new LabGraph();
    testG->initGraph();
    testG->buildLabWithPrim();
    for(auto n : testG->graphNodes){
        EXPECT_TRUE(n->isVisited());
    }
}
TEST(primTest, primsAlgoTestEdges){
    LabGraph * testG = new LabGraph();
    testG->initGraph();
    testG->buildLabWithPrim();
    for(auto e : testG->graphEdges){
        EXPECT_TRUE(e->isVisited());
    }
}
TEST(primTest, recursiveBacktrackingTestNodes){
    LabGraph * testG = new LabGraph();
    testG->initGraph();
    testG->buildLabWithPrim();
    for(auto n : testG->graphNodes){
        EXPECT_TRUE(n->isVisited());
    }
}
TEST(primTest, recursiveBacktrackingEdges){
    LabGraph * testG = new LabGraph();
    testG->initGraph();
    testG->buildLabWithPrim();
    for(auto e : testG->graphEdges){
        EXPECT_TRUE(e->isVisited());
    }
}
