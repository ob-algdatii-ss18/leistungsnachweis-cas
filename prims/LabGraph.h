//
// Created by chris on 09.05.18.
//

#ifndef LEISTUNGSNACHWEIS_CAS_LABGRAPH_H
#define LEISTUNGSNACHWEIS_CAS_LABGRAPH_H


#include <ostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <chrono>
#include <stack>
#include <algorithm>
#include "gtest/gtest.h"

using namespace std;

#define VIDEO false
#define LG_WIDTH 30
#define LG_HEIGHT 30
#define  BLACK "black"
#define WHITE "white"

class LabGraph {

private:
    struct Node;
    struct Edge;
    /**
     * Height and width of the Labyrinth
     */
    int height, width;
    /**
     * Start- and endpoint of the Labyrinth
     */
    Node *start = nullptr,*exit = nullptr,*current = nullptr;
    /**
     * Vector that holds all the Edges of the Graph
     */
    vector<Edge *> graphEdges;
    /**
     * Vector that holds all the Nodes of the Graph
     */
    vector<LabGraph::Node *> graphNodes;
    /**
     * Creates an new edge from start to end. Graph is undirected.
     * @param start "start node of the edge"
     * @param end "Endpoint of the edge"
     */
    void newEdge(LabGraph::Node *start, LabGraph::Node *end);
    /**
     * Creates a new node at position x,y. Sets the border member acoordingliy.
     * @return Pointer to the new node
     */
    Node* newNode(int y, int x);
    /**
     * Represents a weighted edge in the graph. Connects two nodes.
     */
    struct Edge {
        /**
         * Start and endpoint of the edge.
         */
        LabGraph::Node *left,*right;
        /**
         * Weight of the edge.
         */
        int weight;
        /**
         * Indicates if this edge is a wall or a passage.
         */
        bool wall = true;
        /**
         * Indicates if this edge has been visited in creation process of the labyrinth.
         */
        bool visited = false;
        /**
         * Compare function for two edges. Compares two edges by weight. Needed to manage edgepointers in a priority queue.
         */
        struct CompareEdges : public std::binary_function<LabGraph::Edge*, LabGraph::Edge*, bool>
        {
            bool operator()(const LabGraph::Edge* lhs, const LabGraph::Edge* rhs) const
            {
                return lhs->weight > rhs->weight;
            }
        };
        /**
         * Constructor.
         * @param weight Weight of the edge.
         */
        explicit Edge(int weight);
        /**
         * Constructor.
         * @param left Left node.
         * @param right Right node.
         * @param weight weight of the edge.
         */
        Edge(Node *left, Node *right, int weight);
        /**
         * Just for graphical layout of the graph via graphviz.
         * @return True if left and right have the same x-coordinate.
         */
        bool isHorizontal();
        /**
         * Setter for wall.
         */
        void setWall(bool);
        /**
         * Getter for wall.
         * @return True if this edge is a wwall.
         */
        bool isWall();
        /**
         * Setter for visited.
         */
        void setVisited(bool);
        /**
         * Getter for visited.
         * @return True if this edge has been visited.
         */
        bool isVisited();
        /**
         * Tests if this edge is part of the outer boarder of the graph. Outer borders are always a wall and no part of the creation of the actual labyrinth.
         * @return True if this edge is part of the outer border of the lab.
         */
        bool isBorder();
        /**
         * Tests if this edge connects the border of the labyrinth to the labyrinth itself. This connectors are not passable but are not shown as a wall in the graphical layout.
         * @return True if this edge connects the lab with the border.
         */
        bool connectBorder();
        /**
         * Returns the other end of this edge.
         * @return The other end of this edge.
         */
        Node* otherEnd(Node *);
    };
    /**
     * A node in the graph. Represents a crossing in the labyrinth.
     */
    struct Node {
        /**
         * Constructor.
         * @param x X-coordinate of the node.
         * @param y Y-coordinate of the node.
         */
        Node(int x, int y);
        /**
         * Constructor.
         * @param x X-coordinate of the node.
         * @param y Y-coordinate of the node.
         * @param border Is this node part of the outer border of the labyrinth.
         */
        Node(int x, int y, bool border);
        /**
         * X and y coordinate of the node.
         */
        string color = WHITE;
        int x_pos,y_pos;
        /**
         * Indicates if this node has been visited in creation process of the labyrinth.
         */
        bool visited = false;
        /**
         * Marker if this node is part of the outer border. The outer border is not part of the labyrinth.
         */
        bool border = false;
        /**
         * Holds a pointer to all edges that connect this node.
         */
        vector<LabGraph::Edge*>  edges;
        /**
         * Connects a new edge to this node.
         */
        void addEdge(LabGraph::Edge*);
        /**
         * For graphical layout. The id is the x and y coordinate of the node. E.g.: "N_X_Y"
         * @return ID of the node.
         */
        string getId();
        /**
         * Setter for visited.
         */
        void setVisited(bool);
        /**
         * Getter for visited.
         * @return True if this node has been visited.
         */
        bool isVisited();
        /**
         * Getter for border.
         * @return
         */
        bool isBorder();
    };
    /**
     * Directory for plots and animation. Only set on linux.
     */
    string dirPath;
    FRIEND_TEST(primTest, innitTestNodes);
    FRIEND_TEST(primTest, innitTestEdges);
    FRIEND_TEST(primTest, compareEdgesTest);
    FRIEND_TEST(primTest, setDimensionsTest);
    FRIEND_TEST(primTest, setLabTest);
    FRIEND_TEST(primTest, otherEndTest);
public:
    LabGraph();
    /**
     * Constructor.
     * @param height Height of the graph.
     * @param width Width of the graph.
     */
    LabGraph(int height, int width);
    /**
     * Destructor of the graph.
     */
    ~LabGraph();
    /**
     * Creates a square with heigt x width nodes connected by edges.
     */
    void initGraph();
    /**
     * Creates a Labyrinth on the Graph with prims algorithm.
     */
    void buildLabWithPrim();
    /**
     * Creates a Labyrinth on the Graph with recursive backtracing algorithm.
     */
    void buildLabWithRecBac();
    /**
     * Creates a picture of the current graph using graphviz.
     * @param format Outputformat of the picture e.g. "jpg" "png"...
     */
    void graphToPic(string format);
    /**
     * Makes a video of the graph creation.
     */
    void makeVideo();

    /**
     * Sets the color of all edges to black or white. This is used to diplay the labyrinth created by recursive division.
     */
    void setLab(bool **);
    /**
     * Can only be used on an uninizialized graph. Sets the height and width and initializes the graph. This is used to diplay the labyrinth created by recursive division.
     */
    void setDimensions(int, int);
    /**
     * Once a simple test method this became the starter:).
     */
    void easyTest();
    /**
     * Outputs the graph in DOT-form so it can be interpreted by graphviz.
     * @return
     */
    friend std::ostream &operator<<(std::ostream &, const LabGraph &);
};


#endif //LEISTUNGSNACHWEIS_CAS_LABGRAPH_H
