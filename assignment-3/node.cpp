#include <iostream>
#ifndef __node__
#define __node__
using namespace std;

//node struct for fibonacci heap
struct nodePQ {
    int key=-1;
    int src=-1;
    int des=-1;
    struct nodePQ* parent = NULL;
    struct nodePQ* child = NULL;
    struct nodePQ* left = NULL;
    struct nodePQ* right = NULL;
    int degree = 0;
    bool mark = false;
};

//node for adjacent list of a graph
struct node {
    int n;                            //vertex
    int weight;                       //weight
    struct node* next = NULL;         //pointer to next node in the list
};
#endif