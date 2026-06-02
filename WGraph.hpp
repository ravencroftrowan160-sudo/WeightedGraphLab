#ifndef WGRAPH_H
#define WGRAPH_H

#include <string>
using namespace std;

// Edge structure
struct Edge {
    char value;
    int weight;
    Edge* next;

    Edge(char v, int w);
};


// Node structure

struct Node {
    char value;
    bool visited;
    Edge* adjList;

    Node();
};


class WGraph {
private:
    Node G[20];
    int M[20][20];
    int size;

    int findNode(char value);
    void resetVisited();
    void depthFirstHelper(int index, bool edge, stringstream& ss);

public:
    // Constructor
    WGraph();
    ~WGraph();

    // Core functions
    
    void addNode(char value);
    void addEdge(char start, char end, int weight);
    string listNodes();
    string displayAdjacency();
    string displayMatrix();

    // Traversals
    string breadthFirst(char start, bool edge = false, bool unreachable = true);
    string depthFirst(char start, bool edge = false, bool unreachable = true);

    // Advanced
    string minCostTree(char start);   // Prim
    string minCostPaths(char start);  // Dijkstra
};

#endif