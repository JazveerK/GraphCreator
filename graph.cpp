#include "graph.h"
#include <algorithm> //need this package for windows
#include <iostream>
#include <vector>

// Initialize the graph
Graph::Graph() : vertexCount(0) {}

// Add a vertex
void Graph::addVertex(const string& label) {
    if (vertexIndex.find(label) != vertexIndex.end()) {
        cout << "Vertex already exists." << endl;
        return;
    }
    vertexIndex[label] = vertexCount;
    indexVertex.push_back(label);
    vertexCount++;

    // Resize the adjacency matrix
    for (size_t i = 0; i < adjMatrix.size(); i++) {
        adjMatrix[i].push_back(INT_MAX);
    }
    vector<int> newRow(vertexCount, INT_MAX);
    adjMatrix.push_back(newRow);

    // Set the diagonal to 0
    adjMatrix[vertexCount - 1][vertexCount - 1] = 0;
}

// Add an edge
void Graph::addEdge(const string& start, const string& end, int weight) {
    if (vertexIndex.find(start) == vertexIndex.end() || vertexIndex.find(end) == vertexIndex.end()) {
        cout << "One or both vertices do not exist." << endl;
        return;
    }
    int startIndex = vertexIndex[start];
    int endIndex = vertexIndex[end];
    adjMatrix[startIndex][endIndex] = weight;
}

// Remove a vertex
void Graph::removeVertex(const string& label) {
    if (vertexIndex.find(label) == vertexIndex.end()) {
        cout << "Vertex does not exist." << endl;
        return;
    }
    int index = vertexIndex[label];

    // Remove vertex from the maps
    vertexIndex.erase(label);
    indexVertex.erase(indexVertex.begin() + index);

    for (unordered_map<string, int>::iterator it = vertexIndex.begin(); it != vertexIndex.end(); ++it) {
        if (it->second > index) {
            it->second--;
        }
    }

    // Remove the row and column from the adjacency matrix
    adjMatrix.erase(adjMatrix.begin() + index);
    for (size_t i = 0; i < adjMatrix.size(); i++) {
        adjMatrix[i].erase(adjMatrix[i].begin() + index);
    }

    vertexCount--;
}

// Remove an edge
void Graph::removeEdge(const string& start, const string& end) {
    if (vertexIndex.find(start) == vertexIndex.end() || vertexIndex.find(end) == vertexIndex.end()) {
        cout << "One or both vertices do not exist." << endl;
        return;
    }
    int startIndex = vertexIndex[start];
    int endIndex = vertexIndex[end];
    adjMatrix[startIndex][endIndex] = INT_MAX;
}

// Print the adjacency table
void Graph::printTable() const {
    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            if (adjMatrix[i][j] == INT_MAX) {
                cout << "INF ";
            } else {
                cout << adjMatrix[i][j] << " ";
            }
        }
        cout << endl;
    }
}

// Find the shortest path
void Graph::findShortestPath(const string& start, const string& end) const {
    if (vertexIndex.find(start) == vertexIndex.end() || vertexIndex.find(end) == vertexIndex.end()) {
        cout << "One or both vertices do not exist." << endl;
        return;
    }

    int src = vertexIndex.at(start);
    int dest = vertexIndex.at(end);
    vector<int> dist(vertexCount, INT_MAX);
    vector<int> parent(vertexCount, -1);
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

    dist[src] = 0;
    pq.push(make_pair(0, src));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int v = 0; v < vertexCount; v++) {
            if (adjMatrix[u][v] != INT_MAX && dist[v] > dist[u] + adjMatrix[u][v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
                pq.push(make_pair(dist[v], v));
                parent[v] = u;
            }
        }
    }

    if (dist[dest] == INT_MAX) {
        cout << "No path exists from " << start << " to " << end << endl;
    } 
    
    else {
        cout << "Shortest path from " << start << " to " << end << ":" << endl;
        vector<int> path;
        for (int v = dest; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        for (size_t i = 0; i < path.size(); i++) {
            cout << indexVertex[path[i]];
            if (i != path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
        cout << "Total cost: " << dist[dest] << endl;
    }
}
