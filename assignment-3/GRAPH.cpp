#include "GRAPH.h"
//create a an empty GRAPH with n vertices
GRAPH::GRAPH(int n){  
    //create space for the lists
    for(int i=0;i<n;i++){
        struct node* new_node = (struct node*)malloc(sizeof(struct node));
        new_node->n = i+1;
        new_node->next = NULL;
        new_node->weight = 0;
        adjList.push_back(new_node);
    }
    noOfVertices = n;
    noOfEdges = 0;
}

//read adjaceny matrix and convert it to adjaceny list
GRAPH::GRAPH(vector<vector<int>> adjMatrix){  
    noOfVertices = adjMatrix.size();
    noOfEdges = 0;
    weight = adjMatrix;
    //create space for the lists
    for(int i=0;i<noOfVertices;i++){
        struct node* new_node = (struct node*)malloc(sizeof(struct node));
        new_node->n = i+1;
        new_node->next = NULL;
        new_node->weight = 0;
        adjList.push_back(new_node);
    }
    for(int i=0;i<adjMatrix.size();i++){    
        struct node* temp = adjList[i];
        // bool first=true;
        for(int j=0;j<adjMatrix[0].size();j++){
            if(adjMatrix[i][j] !=0 && adjMatrix[i][j]!=-1){  //if weight not equal to 0 and -1 add it to the list
                struct node* new_node = (struct node*)malloc(sizeof(struct node));
                new_node->n = j+1;
                new_node->weight = adjMatrix[i][j];
                new_node->next = NULL;
                temp->next = new_node;
                temp = temp->next;
                if(i<j){
                    noOfEdges++; //counting no of edges
                }
            }
        }
    }
}

//to get adjacent list of a vertex
struct node* GRAPH::getAdjList(int vertex){  
    return adjList[vertex-1]->next;
}

//adding edge to the GRAPH
void GRAPH::addEdge(int n1,int n2,int cost){  
    struct node* new_node1 = (struct node*)malloc(sizeof(struct node));
    struct node* new_node2 = (struct node*)malloc(sizeof(struct node));

    //adding it to adjacent list of n1
    new_node1->n = n2;
    new_node1->weight = cost;
    new_node1->next = NULL;
    struct node* temp = adjList[n1-1]->next;
    adjList[n1-1]->next = new_node1;
    new_node1->next = temp;

    //adding it to adjacent list of n2
    new_node2->n = n1;
    new_node2->weight = cost;
    new_node2->next = NULL;
    temp = adjList[n2-1]->next;
    adjList[n2-1]->next = new_node2;
    new_node2->next = temp;
}

//to print edges in the GRAPH
void GRAPH::printEdges(){  
    for(int i=0;i<noOfVertices;i++){
        struct node* temp;
        temp = adjList[i]->next;
        while(temp!=NULL){
            if(temp->n > i+1){
                cout << "(" << i+1 << "," << temp->n << ")" << endl;
            }
            temp = temp->next;
        }
    }
}

//get weight of an edge
int GRAPH::getWeightOfEdge(int n1,int n2){
    if(n1>n2){
        n1 = n1+n2;
        n2 = n1-n2;
        n1 = n1-n2;
    }
    struct node* temp = adjList[n1-1]->next;
    while(temp != NULL){
        if(temp->n == n2){
            return temp->weight;
        }
        temp = temp->next;
    }
    return -1;
}

//sum of weight of all edges
int GRAPH::cost(){ 
    int cost = 0;
    for(int i=0;i<noOfVertices;i++){
        struct node* temp;
        temp = adjList[i]->next;
        while(temp!=NULL){
            if(temp->n > i+1){
                cost = cost + getWeightOfEdge(i+1,temp->n);
            }
            temp = temp->next;
        }
    }
    return cost;
}
