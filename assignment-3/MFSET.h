#ifndef __MFSET__
#define __MFSET__

#include <vector>
using namespace std;

struct subset {
    int parent;
    int rank;
};

class MFSET{
    private:
        int noOfVertices; 
        vector<subset> subsets;   //subset array with each containing parent and rank
    public:
        MFSET(int);               //constructor
        int find(int);           // finding parent of vertex
        void UNION(int,int);      // merging two subsets
};
#endif