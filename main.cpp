// Jazveer Kaler
// 06/04/24
// Graph Creator
// Used some code from Jayden Huang's repository


#include "graph.h"
#include <cstring>

//main loop
int main() {
    Graph graph;
    bool running = true;

    while (running) {
        cout << "Please enter your input. Enter ADD to add a vertex, EDGE to add an edge, DE to delete an edge, DV to delete a vertex, PRINT to print the adjacency table, PATH to find shortest path, and QUIT to quit the program: " << endl;
        string command;
        cin >> command;

        if (command == "ADD") {
            string label;
            cout << "Enter vertex label: ";
            cin >> label;
            graph.addVertex(label);
        } 
        
        else if (command == "EDGE") {
            string start, end;
            int weight;
            cout << "Enter edge start vertex, end vertex, and weight (seperated by spaces): ";
            cin >> start >> end >> weight;
            graph.addEdge(start, end, weight);
        } 
        
        else if (command == "DE") {
            string start, end;
            cout << "Enter edge start vertex and end vertex to delete (seperated by spaces): ";
            cin >> start >> end;
            graph.removeEdge(start, end);
        } 
        
        else if (command == "DV") {
            string label;
            cout << "Enter vertex label to delete: ";
            cin >> label;
            graph.removeVertex(label);
        } 
        
        else if (command == "PRINT") {
            graph.printTable();
        } 
        
        else if (command == "PATH") {
            string start, end;
            cout << "Enter start and end vertex to find shortest path (seperated by spaces): ";
            cin >> start >> end;
            graph.findShortestPath(start, end);
        } 
        
        else if (command == "QUIT") {
            running = false;
        } 
        
        else {
            cout << "Please enter a valid input" << endl;
        }
    }

    return 0;
}
