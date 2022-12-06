#pragma once
#include<iostream>
#include<vector>
#include <list>
#include <stack>
using namespace std;

class GraphCycle {
    int V; // No. of vertices
    list<int>* adj; // Pointer to an array containing adjacency lists
    bool isCyclicUtil(int v, bool visited[], bool* rs); // used by isCyclic()
public:
    GraphCycle(int V); // Constructor
    void addEdge(int v, int w); // to add an edge to graph
    bool isCyclic(); // returns true if there is a cycle in this graph
};



