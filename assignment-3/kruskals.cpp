#include <iostream>
#include "MFSET.h"
#include "GRAPH.h"
#include "PRIORITYQUEUE.h"

using namespace std;
GRAPH kruskals(GRAPH graph){
    
    MFSET mfset(graph.noOfVertices); //initialise mfset
    PRIORITYQUEUE PQ; //empty priority queue
    //push all edges in to priority queue
    for(int i=0;i<graph.noOfVertices;i++){
        struct node* temp = graph.getAdjList(i+1);
        while(temp != NULL){
            if(temp->n > i+1){
                 struct nodePQ* tempPQ = (struct nodePQ*)malloc(sizeof(struct nodePQ));
                 tempPQ->src = i+1;
                 tempPQ->des = temp->n;
                 tempPQ->key = temp->weight;
                 PQ.insert(tempPQ);
            }
            temp = temp->next;
        }
    }

    //new graph for MST;
    GRAPH MST(graph.noOfVertices);
    int inMST = 0; //no of edges in mst
    while(inMST < graph.noOfVertices-1 && !PQ.isEmpty()){ //O(E) 
        struct nodePQ* temp = PQ.deleteMin();   //O(logV)
        //check for cycle before adding
        if(mfset.find(temp->src-1) != mfset.find(temp->des-1)){   //O(logV)
            MST.addEdge(temp->src,temp->des,temp->key); //add edge to the MST   //O(1)
            mfset.UNION(temp->src-1,temp->des-1);       // merge those two sets //O(logV)
            inMST++;                                    //increment no of edges in MST
        }
    }

    return MST;

}