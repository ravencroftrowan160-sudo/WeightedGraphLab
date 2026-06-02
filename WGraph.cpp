#include "WGraph.hpp"
#include <iostream>
#include <queue>
#include <stack>
#include <sstream>  // add this at top
using namespace std;

const int INF = 999999;
// ===== Edge Constructor =====
Edge::Edge(char v, int w) {
    value = v;
    weight = w;
    next = nullptr;
}

Node::Node() {
    value = '\0';   // null character instead of ""
    visited = false;
    adjList = nullptr;
}

// ===== WGraph Constructor =====
WGraph::WGraph() {
    size = 0;

    for(int i = 0; i < 20; i++){
        G[i] = Node();
        for(int j = 0; j < 20; j++){
            M[i][j] = INF;
        }
    }
}

WGraph::~WGraph() {
    for (int i = 0; i < size; i++) {
        Edge* temp = G[i].adjList;

        while (temp != nullptr) {
            Edge* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }

        G[i].adjList = nullptr;
    }
}

// ===== Helper Functions =====
int WGraph::findNode(char value) {
    for (int i = 0; i < size; i++) {
        if (G[i].value == value) {
            return i;
        }
    }
    return -1;
}

void WGraph::resetVisited() {
    for (int i = 0; i < size; i++) {
        G[i].visited = false;
    }
}

void WGraph::depthFirstHelper(int index, bool edge, stringstream& ss) {
    // mark current node as visited
    G[index].visited = true;

    // always print the node itself
    ss << G[index].value << " ";

    // traverse adjacency list
    Edge* temp = G[index].adjList;

    while (temp != nullptr) {
        int neighborIndex = findNode(temp->value);

        if (!G[neighborIndex].visited) {

            // if edge printing is enabled (rarely used in this lab)
            if (edge) {
                ss << G[index].value << "-" << G[neighborIndex].value << " ";
            }

            depthFirstHelper(neighborIndex, edge, ss);
        }

        temp = temp->next;
    }
}



// ===== Core Functions =====

void WGraph::addNode(char value) {
    if (size >= 20) {
        throw runtime_error("Graph full");
    }

    G[size].value = value;
    G[size].visited = false;
    G[size].adjList = nullptr;

    size++;
}


void WGraph::addEdge(char start, char end, int weight) {
    int s = findNode(start);
    int e = findNode(end);

    // Error check
    if (s == -1 || e == -1 || s == e) {
        throw runtime_error("Invalid edge");
    }

    // ---- Add edge s -> e ----
    Edge* newEdge1 = new Edge(end, weight);

    if (G[s].adjList == nullptr) {
        G[s].adjList = newEdge1;
    } else {
        Edge* temp = G[s].adjList;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newEdge1;
    }

    // ---- Add edge e -> s (because UNDIRECTED) ----
    Edge* newEdge2 = new Edge(start, weight);

    if (G[e].adjList == nullptr) {
        G[e].adjList = newEdge2;
    } else {
        Edge* temp = G[e].adjList;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newEdge2;
    }

    // ---- Update adjacency matrix ----
    M[s][e] = weight;
    M[e][s] = weight;
}

string WGraph::listNodes() {
    string result = "";

    for (int i = 0; i < size; i++) {
        result += G[i].value;
        result += " ";
    }

    return result;
}

string WGraph::displayAdjacency() {
    stringstream ss;

    for (int i = 0; i < size; i++) {
        ss << G[i].value << ": ";

        Edge* temp = G[i].adjList;

        while (temp != nullptr) {
            ss << temp->value << "(" << temp->weight << ") ";
            temp = temp->next;
        }

        ss << "\n";
    }

    return ss.str();
}

string WGraph::displayMatrix() {
    stringstream ss;

    // header row
    ss << "  ";
    for (int i = 0; i < size; i++) {
        ss << " " << G[i].value;
    }
    ss << "\n";

    // matrix rows
    for (int i = 0; i < size; i++) {
        ss << G[i].value << " ";

        for (int j = 0; j < size; j++) {
            if (M[i][j] == INF)
                ss << "∞ ";
            else
                ss << M[i][j] << " ";
        }

        ss << "\n";
    }

    return ss.str();
}


// ===== Traversals =====

string WGraph::breadthFirst(char start, bool edge, bool unreachable) {
    resetVisited();

    int s = findNode(start);
    if (s == -1) return "";

    stringstream ss;

    queue<int> q;
    q.push(s);
    G[s].visited = true;

    ss << G[s].value << ": ";

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        Edge* temp = G[current].adjList;

        while (temp != nullptr) {
            int neighborIndex = findNode(temp->value);

            if (!G[neighborIndex].visited) {
                G[neighborIndex].visited = true;
                q.push(neighborIndex);

                if (edge) {
                    ss << G[current].value << "-" << G[neighborIndex].value << " ";
                } else {
                    ss << G[neighborIndex].value << " ";
                }
            }

            temp = temp->next;
        }
    }

    if (unreachable) {
        ss << "with ";
        for (int i = 0; i < size; i++) {
            if (!G[i].visited) {
                ss << G[i].value << " ";
            }
        }
        ss << "unreachable ";
    }

    return ss.str();
}

string WGraph::depthFirst(char start, bool edge, bool unreachable) {
    resetVisited();

    int s = findNode(start);
    if (s == -1) return "";

    stringstream ss;

    ss << G[s].value << ": ";

    // DFS helper already prints the starting node
    depthFirstHelper(s, edge, ss);

    if (unreachable) {
        ss << "with ";
        for (int i = 0; i < size; i++) {
            if (!G[i].visited) {
                ss << G[i].value << " ";
            }
        }
        ss << "unreachable";
    }

    return ss.str();
}

// ===== Advanced =====
string WGraph::minCostTree(char start) {
    resetVisited();

    int s = findNode(start);
    if (s == -1) return "";

    stringstream ss;
    ss << G[s].value << ": ";

    // Min-heap of (weight, fromIndex, toIndex)
    priority_queue<
        tuple<int,int,int>,
        vector<tuple<int,int,int>>,
        greater<tuple<int,int,int>>
    > pq;

    G[s].visited = true;

    // Push all edges from the start node
    Edge* temp = G[s].adjList;
    while (temp != nullptr) {
        int ni = findNode(temp->value);
        pq.push({temp->weight, s, ni});
        temp = temp->next;
    }

    // Prim's algorithm
    while (!pq.empty()) {
        auto [w, from, to] = pq.top();
        pq.pop();

        if (G[to].visited) continue;

        // Accept this edge
        G[to].visited = true;
        ss << G[from].value << "-" << G[to].value << " ";

        // Add new edges from this node
        Edge* e = G[to].adjList;
        while (e != nullptr) {
            int ni = findNode(e->value);
            if (!G[ni].visited) {
                pq.push({e->weight, to, ni});
            }
            e = e->next;
        }
    }

    return ss.str();
}

string WGraph::minCostPaths(char start) {
    resetVisited();

    int s = findNode(start);
    if (s == -1) return "";

    vector<int> dist(size, INF);
    dist[s] = 0;

    // Min-heap of (distance, nodeIndex)
    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (G[u].visited) continue;
        G[u].visited = true;

        // Relax edges
        Edge* temp = G[u].adjList;
        while (temp != nullptr) {
            int v = findNode(temp->value);
            int w = temp->weight;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }

            temp = temp->next;
        }
    }

    // Build output
    stringstream ss;
    ss << G[s].value << ": ";

    for (int i = 0; i < size; i++) {
        if (i == s) continue;

        ss << G[i].value << "(";
        if (dist[i] == INF)
            ss << "inf";
        else
            ss << dist[i];
        ss << ") ";
    }

    return ss.str();
}