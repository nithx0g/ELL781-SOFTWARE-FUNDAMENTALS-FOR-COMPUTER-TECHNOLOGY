#ifndef __PRIORITYQUEUE__
#define __PRIORITYQUEUE__

#include <iostream>
#include <bits/stdc++.h>
#include <queue>
#include "node.cpp"
using namespace std;


struct fibonacci_heap{
    struct nodePQ* min;
    int count;
};

class PRIORITYQUEUE{
    private:
        struct fibonacci_heap* PQ;                   //fibonacci heap pointer
    public:
        PRIORITYQUEUE();                             //constructor
        void insert(nodePQ*);                        //insert node in to priority queue
        struct nodePQ* deleteMin();                  // getting the minimum value
        void consolidate(fibonacci_heap*);                        //consolidate after deleting min
        void fib_heap_link(fibonacci_heap*,nodePQ*,nodePQ*);      // link two nodes in the root list
        struct nodePQ* find_min();                   //find min key in the priority queue
        void decreaseKey(nodePQ*,int);               //decrease key of a node in priority queue                 
        void cascading_cut(fibonacci_heap*,nodePQ*);  //cascading cut after decreaseKey operation
        void cut(fibonacci_heap*,nodePQ*,nodePQ*);    // cut after decrease key operation
        void print_fibonacci_heap();                 // print fibonacci heap
        bool isEmpty();                              //check if the fibonacci heap is empty
};

#endif