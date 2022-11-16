#include <iostream>
#include <vector>
#include "prims.cpp"
#include "kruskals.cpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main(){
    vector<vector<int>> adjacencyMatrix;
    fstream file;
    file.open("test2.txt",ios::in);
    string line;
    char* values;
    if(file.is_open()){
        char* values;
        while(getline(file,line)){ //read line by line
            char c[line.size()+1];
            strcpy(c,line.c_str());
            values = strtok(c," ");  //split line by spaces
            vector<int> temp;
            while(values != NULL){
                temp.push_back(stoi(values));
                values = strtok(NULL," ");
            }
            adjacencyMatrix.push_back(temp); //building the adjacency matrix
        }
    }
    GRAPH graph(adjacencyMatrix); //create a graph with the adjaceny matrix
    
    auto start = high_resolution_clock::now();
    GRAPH PrimsMST = prims(graph); // Get MST using prims algorithm
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop-start);

    cout << "Prim's algorithm MST (total cost: " << PrimsMST.cost() << "; runtime: " << duration.count()/1000000.0 << "ms )" << endl;
    PrimsMST.printEdges();  //print edges of the prims MST

    start = high_resolution_clock::now();
    GRAPH KruskalsMST = kruskals(graph); // Get MST using kruskals algorithm
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop-start);

    cout << "Kruskal's algorithm MST (total cost: " << KruskalsMST.cost() << "; runtime: " << duration.count()/1000000.0 << "ms )" << endl;
    KruskalsMST.printEdges(); //print edges of the kruskals MST
}
