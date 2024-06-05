#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits.h>

using namespace std;

class Graph {
    unordered_map<string, int> vertexIndex;  // Keep track of vertex indices
    vector<string> indexVertex;  // Vertex labels
    vector<vector<int> > adjMatrix;  // Adjacency matrix
    int vertexCount;  // Number of vertices

public:
    Graph();
    void addVertex(const string& label);
    void addEdge(const string& start, const string& end, int weight);
    void removeVertex(const string& label);
    void removeEdge(const string& start, const string& end);
    void printTable() const;
    void findShortestPath(const string& start, const string& end) const;
};

#endif
