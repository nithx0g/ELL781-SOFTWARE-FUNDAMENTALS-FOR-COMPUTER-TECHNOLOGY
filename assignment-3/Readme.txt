To compile:
g++ -o main main.cpp GRAPH.cpp PRIORITYQUEUE.cpp MFSET.cpp
To run:
./main

Files:
1)input_graph.txt = graph in adjacency matrix form
2)GRAPH.h = contains the list of methods and variables used in GRAPH ADT
3)GRAPH.cpp = contains code for GRAPH ADT
4)MFSET.h = contains the list of methods and variables used in MFSET ADT
5)MFSET.cpp = contains code for MFSET ADT
6)PRIORITYQUEUE.h = contains the list of methods and variables used in PRIORITYQUEUE ADT
7)PRIORITYQUEUE.cpp = contains code for PRIORITYQUEUE ADT
8)node.cpp = contains struct declaration for a node in graph and for a node in priority queue.
9)main.cpp = Takes graph from input_graph.txt,runs prims and kruskals to generate MSTs.
