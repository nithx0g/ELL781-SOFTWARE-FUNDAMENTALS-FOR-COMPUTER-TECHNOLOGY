#include "PRIORITYQUEUE.h"

//constructor to intialise an empty queue
PRIORITYQUEUE::PRIORITYQUEUE(){
    struct fibonacci_heap* newHeap = (struct fibonacci_heap*)malloc(sizeof(struct fibonacci_heap));
    newHeap->min = NULL;
    newHeap->count=0;
    PQ = newHeap;
}

//insert into priority queue
void PRIORITYQUEUE::insert(nodePQ* x){
    fibonacci_heap* H = PQ;
    if(H->min == NULL){ //if no node is present
        x->left = x;
        x->right = x;
        H->min = x;
    }
    else{  //if there are nodes present
        struct nodePQ* temp;
        temp=H->min->left;
        H->min->left = x;
        x->left = temp;
        x->right = H->min;
        temp->right = x;
        if(x->key < H->min->key){
            H->min = x;
        }
    }
    H->count = H->count + 1;
}

 //return the min value 
nodePQ* PRIORITYQUEUE::find_min(){
    return PQ->min;      
}

//to check if the priority queue(fibonaccii heap) is empty
bool PRIORITYQUEUE::isEmpty(){  
    if(PQ->count == 0){
        return true;
    }
    return false;
}

//delete the min element
struct nodePQ* PRIORITYQUEUE::deleteMin(){
    fibonacci_heap* H = PQ;
    nodePQ* min = H->min;
    int child_count = H->min->degree;
    if(min != NULL){
        nodePQ* start = H->min->child;
        nodePQ* temp = start;
        // only if a child is present
        if(child_count != 0){ 
            temp->parent = NULL;
            temp = temp->right;
            while(temp!=start){
                temp->parent = NULL; //setting parent to NULL to each child
                temp = temp->right;
            }
            //Adding children to the root list
            temp = start->left;
            start->left = min;
            temp->right = min->right;
            min->right = start;
            temp->right->left = temp;
        }
        //removing min from the root list
        temp = min->left;
        temp->right = min->right;
        min->right->left = temp;
        if(min == min->right){
            H->min = NULL;
        }
        else{
            H->min = min->right;
            consolidate(H);  //consolidate to efficiently organize the heap
        }
        H->count = H->count - 1;
    }
    return min;
}

void PRIORITYQUEUE::consolidate(fibonacci_heap* H){
    int D = log(H->count)/log(1.61803); // upper bound (max possible degree)
    struct nodePQ* A[D+1];  //auxiliary array
    for(int i=0;i<=D;i++){
        A[i] = NULL;
    }

    nodePQ* start = H->min;
    nodePQ* temp1 = start;
    int d;

    //counting number of nodePQs in rootlist
    int rootlist_count=1;
    temp1 = start->right;
    while(temp1 != start){
        rootlist_count++;
        temp1 = temp1->right;
    }

    temp1 = start;

    //traversing the root list
    while(rootlist_count){
        d = temp1->degree;
        nodePQ* temp3=temp1->right;
        while(A[d]!=NULL){
            nodePQ* temp2 = A[d];
            if(temp1->key > temp2->key){
                temp2 = temp1;
                temp1 = A[d];
            }
            fib_heap_link(H,temp2,temp1); //link two nodes in to same tree
            A[d] = NULL;
            d = d + 1;
        }
        A[d] = temp1;
        temp1 = temp3;
        rootlist_count--;
    }

    H->min = NULL;
    //traversing the auxiliary array
    for (int i=0;i<=D;i++){
        if(A[i] != NULL){
            if(H->min == NULL){
                nodePQ* n = A[i];
                n->left = n;
                n->right = n;
                H->min = n;
            }
            else{
                nodePQ* n = A[i];
                n->left = H->min->left;
                n->right = H->min;
                n->left->right = n;
                H->min->left = n;
                if(n->key < H->min->key){
                    H->min = n;
                }
            }
        }
    }
}

void PRIORITYQUEUE::fib_heap_link(fibonacci_heap* H,nodePQ* n2,nodePQ* n1){
    //removing n2 from root list
    n2->right->left = n2->left;
    n2->left->right = n2->right;
    //making n2 a child of n1
    if(n1->child == NULL){  // if n1 has no child
        n1->child = n2;
        n2->left = n2;
        n2->right = n2;
        n2->parent = n1;
    }
    else{ //if n1 has children then add it to the child list
        nodePQ* child = n1->child;
        n2->left = child->left;
        child->left = n2;
        n2->left->right = n2;
        n2->right = child;
        n2->parent = n1;
    }
    n1->degree = n1->degree + 1;
    n2->mark = false;
}

void PRIORITYQUEUE::cut(fibonacci_heap* H,nodePQ* x,nodePQ* y){
    //removing x from child list of y
    if(y->degree == 1){
        y->child = NULL;
        x->parent = NULL;
        y->degree = 0;
    }
    else{
        y->child = x->left;
        x->left->right = x->right;
        x->right->left = x->left;
        x->parent = NULL;
        y->degree = y->degree - 1;
    }
    //adding x to the root list of H
    x->left = H->min->left;
    H->min->left = x;
    x->right = H->min;
    x->left->right = x;
    x->mark = false;
}

void PRIORITYQUEUE::cascading_cut(fibonacci_heap* H,nodePQ* y){
    nodePQ* z = y->parent;
    if(z != NULL){
        if(y->mark == false){  // base condition for recursion
            y->mark = true;
        }
        else{                  //recursive calls
            cut(H,y,z);
            cascading_cut(H,z);
        }
    }
}

//to decrease key  of a node
void PRIORITYQUEUE::decreaseKey(nodePQ* x,int k){
    fibonacci_heap* H = PQ;
    if(k > x->key){
        cout << "new key is greater than current key" << endl;
        return;
    }
    x->key = k;
    nodePQ * y = x->parent;
    if(y != NULL && x->key < y->key){  //rearrange the tree after decrease key
        cut(H,x,y);
        cascading_cut(H,y);
    }
    if(x->key < H->min->key){
        H->min = x;
    }
}

void PRIORITYQUEUE::print_fibonacci_heap(){
    fibonacci_heap* H = PQ;
    if(H->min == NULL){
        cout << "root list empty" << endl;
        return;
    }
    queue<nodePQ*> Q;  //Queue to store nodePQ pointers
    nodePQ * n = H->min;
    nodePQ *temp = n;
    //for printing the root list
    cout << "root list : ";
    cout << "<--->" << temp->key << "<--->";
    Q.push(temp);
    temp = temp->right;
    while(temp != n){
        cout << temp->key << "<--->";
        Q.push(temp);
        temp = temp->right;
    }
    cout << endl;

    //for printing the childlist of each nodePQ
    while(!Q.empty()){
        nodePQ* parent = Q.front();
        nodePQ* child = parent->child;
        Q.pop();
        if(child != NULL){
            cout << "child list of " << parent->key << ": ";
            temp = child;
            cout << "<--->" << temp->key << "<--->" ;
            Q.push(temp);
            temp = temp->right;
            while(temp!=child){
                Q.push(temp);
                cout << temp->key << "<--->" ;
                temp = temp->right;
            }
            cout << endl;
        }
    }
}