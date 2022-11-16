#include <iostream>
#include <bits/stdc++.h>
#include <queue>
using namespace std;

struct node {
    int key;
    int src;
    int des;
    struct node* parent = NULL;
    struct node* child = NULL;
    struct node* left = NULL;
    struct node* right = NULL;
    int degree = 0;
    bool mark = false;
};

struct fibonacci_heap{
    struct node* min;
    int count;
};

// list of functions used
void insert(fibonacci_heap*,node*);
struct node* delete_min(fibonacci_heap*);
void consolidate(fibonacci_heap*);
void fib_heap_link(fibonacci_heap*,node*,node*);
struct node* find_min(fibonacci_heap*);
struct fibonacci_heap* make_heap();
void decrease_key(fibonacci_heap*,node*,int);
struct fibonacci_heap* union_heaps(fibonacci_heap*,fibonacci_heap*);
void print_rootlist(fibonacci_heap*);
void cascading_cut(fibonacci_heap*,node*);
void cut(fibonacci_heap*,node*,node*);
void print_fibonacci_heap(fibonacci_heap*);

struct fibonacci_heap* make_heap(){
    struct fibonacci_heap* heap = (struct fibonacci_heap*)malloc(sizeof(struct fibonacci_heap));
    heap->min = NULL;
    heap->count=0;
    return heap;
}

void insert(fibonacci_heap* H,node* x){
    //if no node is present
    if(H->min == NULL){
        x->left = x;
        x->right = x;
        H->min = x;
    }
    else{
        struct node* temp;
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

fibonacci_heap* union_heaps(fibonacci_heap* H1,fibonacci_heap* H2){
    if(H1->min == NULL){
        return H2;
    }
    if(H2->min == NULL){
        return H1;
    }
    fibonacci_heap* H = make_heap();
    H->min = H1->min;
    //concatenating root list of H and H2
    node* temp1 = H->min->right;    
    node* temp2 = H2->min->left;
    H->min->right = H2->min;
    H2->min->left = H->min;
    temp1->left = temp2;
    temp2->right = temp1;

    //updating min pointer
    if(H1->min == NULL || (H2->min != NULL && H2->min->key < H1->min->key)){
        H->min = H2->min;
    }

    H->count = H1->count + H2->count;

    return H;

}

node* find_min(fibonacci_heap* H){
    return H->min;
}

struct node* delete_min(fibonacci_heap* H){
    node* min = H->min;
    int child_count = H->min->degree;
    if(min != NULL){
        node* start = H->min->child;
        node* temp = start;
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
            consolidate(H);
        }
        H->count = H->count - 1;
    }
    return min;
}

void consolidate(fibonacci_heap* H){
    int D = log(H->count)/log(1.61803); // upper bound
    struct node* A[D+1];  //auxiliary array
    for(int i=0;i<=D;i++){
        A[i] = NULL;
    }

    node* start = H->min;
    node* temp1 = start;
    int d;
    //counting number of nodes in rootlist
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
        node* temp3=temp1->right;
        while(A[d]!=NULL){
            node* temp2 = A[d];
            if(temp1->key > temp2->key){
                temp2 = temp1;
                temp1 = A[d];
            }
            fib_heap_link(H,temp2,temp1);
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
                node* n = A[i];
                n->left = n;
                n->right = n;
                H->min = n;
            }
            else{
                node* n = A[i];
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

void fib_heap_link(fibonacci_heap* H,node* n2,node* n1){
    //removing n2 from root list
    n2->right->left = n2->left;
    n2->left->right = n2->right;
    //making n2 a child of n1
    if(n1->child == NULL){
        n1->child = n2;
        n2->left = n2;
        n2->right = n2;
        n2->parent = n1;
    }
    else{
        node* child = n1->child;
        n2->left = child->left;
        child->left = n2;
        n2->left->right = n2;
        n2->right = child;
        n2->parent = n1;
    }
    n1->degree = n1->degree + 1;
    n2->mark = false;
}

void cut(fibonacci_heap* H,node* x,node* y){
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

void cascading_cut(fibonacci_heap* H,node* y){
    node* z = y->parent;
    if(z != NULL){
        if(y->mark == false){
            y->mark = true;
        }
        else{
            cut(H,y,z);
            cascading_cut(H,z);
        }
    }
}

void decrease_key(fibonacci_heap* H,node* x,int k){
    if(k > x->key){
        cout << "new key is greater than current key" << endl;
        return;
    }
    x->key = k;
    node * y = x->parent;
    if(y != NULL && x->key < y->key){
        cut(H,x,y);
        cascading_cut(H,y);
    }
    if(x->key < H->min->key){
        H->min = x;
    }
}

void delete_node(fibonacci_heap* H,node* x){
    decrease_key(H,x,INT_MIN);   //decrease key to -infinite
    node* temp = delete_min(H);  // delete the min as the node will be on top
    return;
}

void print_fibonacci_heap(fibonacci_heap* H){
    if(H->min == NULL){
        cout << "root list empty" << endl;
        return;
    }
    queue<node*> Q;  //Queue to store node pointers
    node * n = H->min;
    node *temp = n;
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

    //for printing the childlist of each node
    while(!Q.empty()){
        node* parent = Q.front();
        node* child = parent->child;
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
int main(){
    fibonacci_heap* H = make_heap();

    //hardcoding an example
    node* n1 = (struct node*)malloc(sizeof(struct node));
    node* n2 = (struct node*)malloc(sizeof(struct node));
    node* n3 = (struct node*)malloc(sizeof(struct node));
    node* n4 = (struct node*)malloc(sizeof(struct node));
    node* n5 = (struct node*)malloc(sizeof(struct node));
    node* n6 = (struct node*)malloc(sizeof(struct node));
    node* n7 = (struct node*)malloc(sizeof(struct node));
    node* n8 = (struct node*)malloc(sizeof(struct node));

    n1->key = 23;
    insert(H,n1);
    cout << "inserting " << n1->key << endl;
    cout<<"min:"<<H->min->key<< endl;

    n2->key = 7;
    insert(H,n2);
    cout << "inserting " << n2->key << endl;
    cout<<"min:"<<H->min->key<< endl;
    print_fibonacci_heap(H);

    n3->key = 3;
    n4->key = 18;
    n5->key = 39;
    n6->key = 52;
    n7->key = 38;
    n8->key = 41;

    n3->child = n4;
    n4->child = n5;
    n7->child = n8;

    n4->parent = n3;
    n6->parent = n3;
    n7->parent = n3;
    n5->parent = n4;
    n8->parent = n7;

    n3->left = n3;
    n3->right = n3;
    n4->left = n7;
    n4->right = n6;
    n6->left = n4;
    n6->right = n7;
    n7->right = n4;
    n7->left = n6;
    n5->left = n5;
    n5->right = n5;
    n8->left = n8;
    n8->right = n8;

    n3->degree = 3;
    n4->degree = 1;
    n7->degree = 1;

    fibonacci_heap* H1 = make_heap();
    H1->min = n3;
    H1->count = 6;

    cout << "<****************concatenating two heaps using union****************> "<< endl;
    cout << "<*************Second heap*************>" << endl;
    cout<<"min:"<<H1->min->key<< endl;
    print_fibonacci_heap(H1);
    cout << "No of nodes: " << H1->count << endl;
    H = union_heaps(H,H1);

    cout << "<************New heap*************>" << endl;
    cout<<"min:"<<H->min->key<< endl;
    print_fibonacci_heap(H);
    cout << "No of nodes: " << H->count << endl;

    cout<<"<**************deleting min**************>"<<endl;
    node * temp;
    temp = delete_min(H);
    cout << "deleted min: " << temp->key << endl;
    cout << "<***********Heap after deleting************>" << endl;
    cout << "min: " << H->min->key << endl;
    print_fibonacci_heap(H);
    cout << "No of nodes: " << H->count << endl;

    cout << "<************decreasing key from " << n7->key << " to " << 2 << " ************>" << endl;
    decrease_key(H,n7,2);
    cout << "min: " << H->min->key << endl;
    print_fibonacci_heap(H);
    cout << "No of nodes: " << H->count << endl;

    cout << "<*************Deleting node:" << n1->key << " **************>" << endl;
    delete_node(H,n1);
    cout << "min: " << H->min->key << endl;
    print_fibonacci_heap(H);
    cout << "No of nodes: " << H->count << endl;
    return 0;
}