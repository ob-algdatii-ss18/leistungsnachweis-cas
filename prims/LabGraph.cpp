//
// Created by chris on 09.05.18.
//

#include <iostream>
#include "LabGraph.h"

using namespace ::std;


LabGraph::~LabGraph() {

}

std::ostream &operator<<(std::ostream &os, const LabGraph &graph) {
    return os;
}

LabGraph::LabGraph(int h, int w) {
    if(h < 5 || w < 5) throw range_error("height and width must greater 5.");
    height = h;
    width = w;
}

void LabGraph::initGraph() {
    Node * nodes [height][width];
    for(int i=0; i<height; i++){
        nodes[i][0] = new Node(0,i);
        for(int j=1; j < width - 1; j++){
            nodes[i][j] = new Node(i,j);
            nodes[i][j]->addEdge(new Edge(nodes[i][j-1],nodes[i][j],5));
        }
        nodes[i][width - 1] = new Node(width -1,i);
        nodes[i][width - 1]->addEdge(new Edge(nodes[i][width - 2],nodes[i][width - 1],5));
    }
}

void LabGraph::easyTest() {
    Node* n = new Node(0,0);
    n->addEdge(new Edge(5));
    n->addEdge(new Edge(3));
    n->addEdge(new Edge(8));


    cout << "First: " << n->edges.top()->weight << endl;
    n->edges.pop();
    cout << "Second: " << n->edges.top()->weight << endl;
    n->edges.pop();
    cout << "Third: " << n->edges.top()->weight << endl;
    n->edges.pop();
    if(n->edges.empty())
        cout << "Empty now " << endl;
    initGraph();
}


LabGraph::Node::Node(int x, int y) : x_pos(x), y_pos(y) {}

void LabGraph::Node::addEdge(LabGraph::Edge * newEdge) {
    edges.push(newEdge);
}
/*
bool operator<(const LabGraph::Edge& toCompare) {
    return this->weight > toCompare.weight;
}
*/
LabGraph::Edge::Edge(LabGraph::Node *left,LabGraph::Node *right, int weight) : left(left), right(right), weight(weight) {}

LabGraph::Edge::Edge(int weight) : weight(weight) {}
