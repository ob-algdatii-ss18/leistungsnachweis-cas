//
// Created by chris on 09.05.18.
//

#ifndef LEISTUNGSNACHWEIS_CAS_LABGRAPH_H
#define LEISTUNGSNACHWEIS_CAS_LABGRAPH_H


#include <ostream>
#include <queue>

using namespace std;


class LabGraph {

private:
    struct Node;
    struct Edge;

    int height, width;
    Node *start = nullptr,*exit = nullptr;



    struct Edge {

        LabGraph::Node *left,*right;

        int weight;

        struct CompareEdges : public std::binary_function<LabGraph::Edge*, LabGraph::Edge*, bool>
        {
            bool operator()(const LabGraph::Edge* lhs, const LabGraph::Edge* rhs) const
            {
                return lhs->weight > rhs->weight;
            }
        };

        Edge(int weight);

        Edge(Node *left, Node *right, int weight);
// friend bool operator<(const Edge &);
    };

    struct Node {
        Node(int x, int y);

        int x_pos,y_pos;

        LabGraph::Edge * top,*right,*bot,*left;

        priority_queue<LabGraph::Edge *, vector<LabGraph::Edge*>, LabGraph::Edge::CompareEdges> edges;

        void addEdge(LabGraph::Edge*);
    };


public:

    LabGraph(int height, int width);

    ~LabGraph();

    void initGraph();

    void easyTest();

    friend std::ostream &operator<<(std::ostream &os, const LabGraph &graph);
};


#endif //LEISTUNGSNACHWEIS_CAS_LABGRAPH_H
