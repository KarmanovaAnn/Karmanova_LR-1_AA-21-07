#include "GraphCycle.h"
#include<iostream>
#include<vector>
#include <list>
#include <stack>
using namespace std;

GraphCycle::GraphCycle(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void GraphCycle::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

// This function is a variation of DFSUytil()
// in https:// www.geeksforgeeks.org/archives/18212
bool GraphCycle::isCyclicUtil(int v, bool visited[], bool* recStack)
{
    if (visited[v] == false) {
        // Mark the current node as visited and part of recursion stack
        visited[v] = true;
        recStack[v] = true;

        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); ++i) {
            if (!visited[*i] && isCyclicUtil(*i, visited, recStack))
                return true;
            else if (recStack[*i])
                return true;
        }
    }
    recStack[v] = false; // remove the vertex from recursion stack
    return false;
}

// Returns true if the graph contains a cycle, else false.
// This function is a variation of DFS()
// in https:// www.geeksforgeeks.org/archives/18212
bool GraphCycle::isCyclic()
{
    // Mark all the vertices as not visited and not part of recursion
    // stack
    bool* visited = new bool[V];
    bool* recStack = new bool[V];
    for (int i = 1; i < V; i++) {
        visited[i] = false;
        recStack[i] = false;
    }

    // Call the recursive helper function to detect cycle in different
    // DFS trees
    for (int i = 1; i < V; i++)
        if (isCyclicUtil(i, visited, recStack))
            return true;

    return false;
}

/*int main()
{
    // Create a graph given in the above diagram
    GraphCycle g(4);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 1);


    if (g.isCyclic())
        cout << "В графе есть цикл";
    else
        cout << "В графе нет цикла";
    return 0;
}*/
