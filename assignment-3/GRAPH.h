#ifndef __graph__
#define __graph__
#include "node.cpp"
#include <vector>
#include <iostream>
using namespace std;
class GRAPH{
    private:
        std::vector<node*> adjList;              //adjacent list representation
    public:
        int noOfVertices;
        int noOfEdges;
        vector<vector<int>> weight;
        GRAPH(int);                              //constructor with input = no of vertices
        GRAPH(vector<vector<int>>);              // constructor with input adjacency matrix
        struct node* getAdjList(int);            //to adjacent vertices of a vertex
        void addEdge(int,int,int);               //adding an edge to the graph
        void printEdges();                       //print edges of the graph
        int getWeightOfEdge(int,int);            //get weight of an edge
        int cost();                              //return sum of weights of all edges in the graph
};
#endif