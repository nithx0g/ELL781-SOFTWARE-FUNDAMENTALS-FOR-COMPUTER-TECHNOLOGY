#include "MFSET.h"

//constructor
MFSET::MFSET(int noOfVertices){
    for(int i=0;i<noOfVertices;i++){
        struct subset new_subset ;//= (struct subset*)malloc(sizeof(subset));
        new_subset.parent = i;
        new_subset.rank = 0;
        subsets.push_back(new_subset);
    }
}

//finding parent
int MFSET::find(int i){  
    if(subsets[i].parent != i){  // if its not the parent
        subsets[i].parent = find(subsets[i].parent); // then recursively find the parent and do path compression
    }
    return subsets[i].parent;
}

void MFSET::UNION(int n1,int n2){  
    int root_n1 = find(n1); //finding roots of n1 and n2
    int root_n2 = find(n2);
    //making larger rank tree as root of smaller rank tree. (union by rank)
    if(subsets[root_n1].rank > subsets[root_n2].rank){
        subsets[root_n2].parent = root_n1;
    }
    else if(subsets[root_n1].rank == subsets[root_n2].rank){ //if both are equal
        subsets[root_n1].parent = root_n2;
        subsets[root_n2].rank++;
    }
    else{
        subsets[root_n1].parent = root_n2;
    }
}
        

