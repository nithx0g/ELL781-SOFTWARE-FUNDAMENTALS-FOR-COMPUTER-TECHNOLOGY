#include <iostream>
#include "GRAPH.h"
#include "PRIORITYQUEUE.h"
#include <bits/stdc++.h>
using namespace std;

GRAPH prims(GRAPH graph){
    int keys[graph.noOfVertices]={0};
    bool inMST[graph.noOfVertices]={false};
    int parents[graph.noOfVertices]={-1};
    nodePQ* nodePQArray[graph.noOfVertices];
    PRIORITYQUEUE PQ;
    
     //taking source vertex as the first vertex
    struct nodePQ* temp = (struct nodePQ*)malloc(sizeof(struct nodePQ));
    temp->src = 1;
    temp->key = 0;
    
    PQ.insert(temp);
    // cout << "aaa" << endl;
    nodePQArray[0] = temp;
    keys[0] = 0;
    for(int i=1;i<graph.noOfVertices;i++){
        keys[i] = INT_MAX;
        struct nodePQ* temp = (struct nodePQ*)malloc(sizeof(struct nodePQ));
        temp->src = i+1;
        temp->key = keys[i];
        nodePQArray[i] = temp;
        PQ.insert(temp);
    }
    
    while(!PQ.isEmpty()){    
        struct nodePQ* min = PQ.deleteMin();  
        inMST[min->src-1] = true;
        struct node* list = graph.getAdjList(min->src);
        struct node* temp = list;
        while(temp!=NULL){    
            if(inMST[temp->n-1]== false && keys[temp->n-1] > temp->weight){
                
                keys[temp->n-1] = temp->weight;
                
                PQ.decreaseKey(nodePQArray[temp->n-1],temp->weight);  
                
                parents[temp->n-1] = min->src-1; 

            }
            temp = temp->next;
        }
    }

    //convert parent array to graph 
    GRAPH MST(graph.noOfVertices);
    for(int i=1;i<graph.noOfVertices;i++){  
        if(parents[i]!=-1){
            MST.addEdge(i+1,parents[i]+1,graph.weight[i][parents[i]]);
        }
    }
    return MST;
}