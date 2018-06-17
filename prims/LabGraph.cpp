//
// Created by chris on 09.05.18.
//

#include <iostream>


#include "LabGraph.h"


using namespace ::std;


LabGraph::~LabGraph() = default;

std::ostream &operator<<(std::ostream &os, const LabGraph &graph) {
    string constraint, style;
    os << "graph Labyrinth {" << endl;
    if (graph.graphNodes.empty()) {
        os << "    null " << "[shape=point];" << endl;
    } else {
//        os << "graph [ratio=fill size=\"" << graph.width / 10  << "," << graph.height / 10  << "\" splines=line  rankdir=\"TB\"];" << endl;
        os << "graph [ratio=fill size=\"10,10\" splines=line  rankdir=\"TB\"];" << endl;
        //---start and end for format
        os << "{ node [style=invis root=true color=green] \"root\" }" << endl;
        os << "{ node [style=invis] \"end\" }" << endl;

        //-----------NODES--------------
        os << "{ node [fixedsize=true shape=square width=3 style=dotted] " << endl;
        for(LabGraph::Node* curNode : graph.graphNodes){
            if(curNode->isBorder())
                os << "    \"" << curNode->getId() << "\" [label=\"\" style=filled color=black rank="  << curNode->y_pos << "];" << endl;
            else
                if(curNode == graph.start)
                    os << "    \"" << curNode->getId() << "\" [label=\"\" color=red style=filled rank="  << curNode->y_pos << "];" << endl;
                else if(curNode == graph.current)
                    os << "    \"" << curNode->getId() << "\" [label=\"\" color=green style=filled rank="  << curNode->y_pos << "];" << endl;
                else
                    os << "    \"" << curNode->getId() << "\" [label=\"\" rank="  << curNode->y_pos << "];" << endl;
        }
        os << "}" << endl;

        //-------invis format edges-------
        os << "{ edge [style=invis len=0.01 ] " << endl;
        for(int i=0; i < graph.width ; i++){
            os << "\"root\" -- \"" << graph.graphNodes[i]->getId() << "\"" << endl;
        }
        os << "}" << endl;
        os << "{ edge [style=invis len=0.01] " << endl;
        for(int i=0; i < graph.width ; i++){
            os  << "\"" << graph.graphNodes[graph.width*(graph.height-1) + i]->getId() << "\" -- \"end\""<< endl;
        }
        os << "}" << endl;

        //------------------------------------------EDGES-----------------------------------------------
        os << "{ edge [penwidth=255  len=0.01] " << endl;
        for(LabGraph::Edge* curEdge : graph.graphEdges){

            if(!curEdge->isHorizontal())
                constraint = "false";
            else
                constraint = "true";
            if(curEdge->isWall() && !curEdge->connectBorder())
                style = "\"\"";
            else
                style = "invis";
            if(curEdge->isBorder())
                style += " penwidth=210";

            os << "    \"" << curEdge->left->getId() << "\" -- \"" << curEdge->right->getId() << "\" [constraint=" << constraint << " style=" << style << "];" << endl;

        }
        os << "}" << endl;
    }

    os << "}" << endl;
    return os;
}

LabGraph::LabGraph(int w, int h) {
    if(h < 5 || w < 5) throw range_error("height and width must greater 5.");
    height = h;
    width = w;
}

void LabGraph::initGraph() {
    //seed random
    srand(static_cast<unsigned int>(time(nullptr)));
    Node * nodes [height][width];
    for(int i=0; i<height; i++){ // i == height == y

        nodes[i][0] = newNode(i,0);

        if(i>0)
            newEdge(nodes[i-1][0],nodes[i][0]);

        for(int j=1; j <= width - 1; j++){ // j == width == x

            //connect to the left
            nodes[i][j] = newNode(i,j); //newNode(y,x)
            newEdge(nodes[i][j-1],nodes[i][j]);

            //connect the rows
            if(i>0){
                newEdge(nodes[i-1][j],nodes[i][j]);
            }
        }
    }
}

void LabGraph::newEdge(LabGraph::Node *start, LabGraph::Node *end) {
    //rand() % 10 + 1
    Edge * newEdge;
    newEdge = new Edge(start, end, rand() % 10 + 1);
    if(newEdge->isBorder()){
        newEdge->setWall(true);
        newEdge->setVisited(true);
    }else if(newEdge->connectBorder()){
        newEdge->setWall(false);
        newEdge->setVisited(true);
        start->addEdge(newEdge);
        end->addEdge(newEdge);
    }else{
        newEdge->setWall(true);
        newEdge->setVisited(false);
        start->addEdge(newEdge);
        end->addEdge(newEdge);
    }
    graphEdges.push_back(newEdge);
}
LabGraph::Node* LabGraph::newNode(int y, int x) {
    Node* newNode;
    newNode = new Node(x, y, (x == 0 || x == width - 1 || y == 0 || y == height - 1));
    if(newNode->isBorder())newNode->setVisited(true);
    this->graphNodes.push_back(newNode);
    return newNode;
}


void LabGraph::easyTest() {


    Node* n = new Node(0,0);
    n->addEdge(new Edge(5));
    n->addEdge(new Edge(3));
    n->addEdge(new Edge(8));

    initGraph();
    buildLabWithPrim();
    graphToPng();
}

void LabGraph::buildLabWithPrim() {
    int count = 1;
    bool hasChanged = false;


    graphToPng();
    priority_queue<LabGraph::Edge *, vector<LabGraph::Edge*>, LabGraph::Edge::CompareEdges> labEdges;
    int x = rand() % (width -2) + 1;
    int y = rand() % (height -2) + 1;
    int random = y*height  + x;
    auto curNode = graphNodes[random];
    start = current = curNode;
    for(auto cur: curNode->edges){
        labEdges.push(cur);
    }
    curNode->setVisited(true);
    do{

        auto curEdge = labEdges.top();
        labEdges.pop();
        if(curEdge->left->isVisited() && curEdge->right->isVisited()){
            hasChanged = false;
            //do nothing
        }else{
            hasChanged = true;
            if(curEdge->left->isVisited()){
                curNode = current = curEdge->right;
            }else if(curEdge->right->isVisited()){
                curNode = current = curEdge->left;
            }else{
                throw logic_error("...");
            }
            count++;
            curEdge->setWall(false);
            curEdge->setVisited(true);

            for(auto cur: curNode->edges){
                if(!cur->isVisited())labEdges.push(cur);
            }
            curNode->setVisited(true);
        }

        if(hasChanged) graphToPng();

    }while(!labEdges.empty());

    graphToPng();
    if(count == (height-2) * (width-2));
        cout << "all nodes visited !" << endl;
    cout << "fertig !" << "size:" << graphNodes.size() << " loops:" << count <<endl;
}

void LabGraph::graphToPng() {
    ofstream myfile;
    long ms = chrono::system_clock::now().time_since_epoch().count();
  //  string fileName = "../Plots/graph" + to_string(ms) + ".dot";
    string picName = "../Plots/bsp6/graph" + to_string(ms) + ".jpe";
        string fileName = "graph2.dot";
    //  string picName = "graph.png";
    const string dotExec = "dot -Tjpe -v " + fileName + " -o " + picName;
    myfile.open(fileName);
    myfile << *this;
    myfile.close();
    system(dotExec.data());
}

LabGraph::Node::Node(int x, int y) : x_pos(x), y_pos(y) {}

void LabGraph::Node::addEdge(LabGraph::Edge * newEdge) {
    edges.push_back(newEdge);
}

string LabGraph::Node::getId() {
    stringstream idStream;
    idStream << "N_" << x_pos << "_" << y_pos;
    return idStream.str();
}

bool LabGraph::Node::isVisited() {
    return visited;
}

void LabGraph::Node::setVisited(bool setTo) {
    visited = setTo;
}

bool LabGraph::Node::isBorder() {
    return border;
}

LabGraph::Node::Node(int x, int y, bool b) {
    border = b;
    x_pos = x;
    y_pos = y;
}

LabGraph::Edge::Edge(LabGraph::Node *left,LabGraph::Node *right, int weight) : left(left), right(right), weight(weight){}

LabGraph::Edge::Edge(int weight) : weight(weight) {}

bool LabGraph::Edge::isHorizontal() {
    return left->x_pos == right-> x_pos;
}

bool LabGraph::Edge::isWall() {
    return wall;
}

void LabGraph::Edge::setWall(bool setTo) {
    wall = setTo;
}

bool LabGraph::Edge::isBorder() {
    return left->isBorder() && right->isBorder();
}

bool LabGraph::Edge::connectBorder() {
    return (left->isBorder() && !right->isBorder()) || (!left->isBorder() && right->isBorder());
}

void LabGraph::Edge::setVisited(bool setTo) {
    visited = setTo;
}

bool LabGraph::Edge::isVisited() {
    return visited;
}
