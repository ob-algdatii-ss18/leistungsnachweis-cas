//
// Created by chris on 09.05.18.
//

#include <iostream>
#include <array>


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
                    os << "    \"" << curNode->getId() << "\" [label=\"\" style=filled color="<< curNode->color <<" rank="  << curNode->y_pos << "];" << endl;
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

LabGraph::LabGraph() {
    long ms = chrono::system_clock::now().time_since_epoch().count();


#ifdef __linux__
    dirPath = "../Plots/bsp" + to_string(ms);
    const string sysCom = "mkdir -p " + dirPath;
    system(sysCom.data());
#else
    dirPath = "";
#endif

    height = LG_HEIGHT;
    width = LG_WIDTH;
}
LabGraph::LabGraph(int w, int h) {
    if(h < 5 || w < 5) throw range_error("height and width must greater 5.");
    long ms = chrono::system_clock::now().time_since_epoch().count();
    dirPath = "../Plots/bsp" + to_string(ms);
    const string sysCom = "mkdir -p " + dirPath;
    system(sysCom.data());
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
 //   buildLabWithRecBac();
    buildLabWithPrim();
    if(VIDEO)makeVideo();
    graphToPic("png");
}

void LabGraph::buildLabWithPrim() {
    bool hasChanged = false;
    if(VIDEO)graphToPic("jpe");

    //Priority queue with all unvisited edges.
    priority_queue<LabGraph::Edge *, vector<LabGraph::Edge*>, LabGraph::Edge::CompareEdges> labEdges;
    //Random start node. Don't start at the border...
    int x = rand() % (width -2) + 1;
    int y = rand() % (height -2) + 1;
    int random = y*height  + x;

    start = current = graphNodes[random];;
    //Add all edges of the start node to the queue.
    for(auto cur: current->edges){
        labEdges.push(cur);
    }
    current->setVisited(true);
    //While there are undiscovered edges do...
    do{
        //Select edge with minimum weight
        auto curEdge = labEdges.top();
        labEdges.pop();
        //If the connected node i not already visited, add it to the labyrinth and make the edge a passage.
        if(curEdge->left->isVisited() && curEdge->right->isVisited()){

            hasChanged = false;
            //do nothing
        }else{
            hasChanged = true;
            if(curEdge->left->isVisited()){
                current = curEdge->right;
            }else if(curEdge->right->isVisited()){
                current = curEdge->left;
            }else{
                throw logic_error("...");
            }
            curEdge->setWall(false);
            curEdge->setVisited(true);
            //Add all unvisited edges to the queue.
            for(auto cur: current->edges){
                if(!cur->isVisited())labEdges.push(cur);
            }
            current->setVisited(true);
        }
        //output
        if(hasChanged && VIDEO) graphToPic("jpe");

    }while(!labEdges.empty());
    //output
    if(VIDEO)graphToPic("jpe");

}
void LabGraph::buildLabWithRecBac(){
    if(VIDEO)graphToPic("jpe");
    int visitedNodes = 1;
    Edge* curEdge;
    //Stack to trace back the last visited node.
    stack<Node*> nodeStack;
    //Random start node.
    int x = rand() % (width -2) + 1;
    int y = rand() % (height -2) + 1;
    int random = y*height  + x;
    start = current = graphNodes[random];
    current->setVisited(true);
    nodeStack.push(current);
    do{
        curEdge = nullptr;
        random_shuffle(current->edges.begin(),current->edges.end());
        for(auto c : current->edges){
            if(!c->isVisited()){
                if(!c->otherEnd(current)->isVisited()) {
                    curEdge = c;
                    break;
                }
            }
        }
        if(curEdge != nullptr){
            nodeStack.push(current);
            if(curEdge->left->isVisited()){
                current = curEdge->right;
            }else if(curEdge->right->isVisited()){
                current = curEdge->left;
            }else{
                throw logic_error("...");
            }
            curEdge->setVisited(true);
            curEdge->setWall(false);
            current->setVisited(true);
            visitedNodes++;
        }else{
            current = nodeStack.top();
            nodeStack.pop();
        }
        if(VIDEO)graphToPic("jpe");
    }while(!nodeStack.empty() && visitedNodes < (height-2) * (width-2));
    if(VIDEO)graphToPic("jpe");

}


void LabGraph::graphToPic(string format) {
    ofstream myfile;

    long ms = chrono::system_clock::now().time_since_epoch().count();
  //  string fileName = "../Plots/graph" + to_string(ms) + ".dot";
    string picName = dirPath + "/graph" + to_string(ms) + "." + format;
    string fileName = dirPath + "/graph2.dot";
    //  string picName = "graph.png";
    const string dotExec = "dot -T"+format+" -v " + fileName + " -o " + picName;
    myfile.open(fileName);
    myfile << *this;
    myfile.close();
    system(dotExec.data());
}

void LabGraph::makeVideo() {
    const string sysCom = "mencoder mf://" + dirPath + "/*.jpe -mf w=800:h=600:fps=15:type=jpg -ovc lavc -lavcopts vcodec=mpeg4:mbd=2:trell -oac copy -o "+ dirPath+"/animation.avi";
 //   const string rmCom = "rm "+ dirPath + "/*.jpe";
    system(sysCom.data());
  //  system(rmCom.data());
}

void LabGraph::setLab(bool ** boolArray) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if(boolArray[i][j]) graphNodes[i*height+j]->color = BLACK;
        }
    }
}

void LabGraph::setDimensions(int x, int y) {
    height = y;
    width = x;
    initGraph();
    for(auto e: graphEdges)e->setWall(false);
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

LabGraph::Node *LabGraph::Edge::otherEnd(LabGraph::Node *oneEnd) {
    if(left == oneEnd)
        return right;
    else if(right == oneEnd)
        return left;
    else
        return nullptr;
}
