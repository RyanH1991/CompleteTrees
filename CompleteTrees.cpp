#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;



struct node{
    int data;
    struct node* left;
    struct node* right;
};

struct node* newNode(int data) 
{  
  struct node* node = (struct node*)malloc(sizeof(struct node)); 
  node->data = data; 
  node->left = NULL; 
  node->right = NULL; 
  return(node); 
} 

struct complete_tree{
    struct node *root = newNode(-2);
    int nodecount;
    int arrayCounter;
    bool bst;
    int arraySave[100];
    complete_tree();
    void insert(int value, int count, node* root){
        //initial count should always be 0
        if(count == nodecount){
            root->data=value;
            return;
        }
        else if (count<nodecount){
            if(root->left==NULL){
                root->left = newNode(-1);
            }
            insert(value, (count*2)+1, root->left);
            if(root->right==NULL){
                root->right = newNode(-1);
            }
            insert(value, (count*2)+2, root->right);
        }
        return;
    }
    void fromArray(int* array, int size, node* root){
        for(int i = 0; i < size; i++){
            insert(array[i], 0, root);
            nodecount++;
        }
    }
    void toArray(int count, int size, int print, node* cream){
        if ((count == arrayCounter) && (arrayCounter == size-1)){
            if(print == 1){
                cout << cream->data << "\n";
            }
            if(print == 0){
                arraySave[arrayCounter] = cream->data;
            }
            //arrayCounter ++;
        }
        else if (count == arrayCounter){
            if(print == 1){
                cout << cream->data << " ";
            }
            if(print == 0){
                arraySave[arrayCounter] = cream->data;
            }
            arrayCounter++;
            toArray(0, size, print, root);
        }
        if (count < arrayCounter){
            if(cream->left!=NULL){
                toArray((count*2+1), size, print, cream->left);
            }
            if(cream->right!=NULL){
                toArray((count*2+2), size, print, cream->right);
            }
        }
        if ((count == arrayCounter) && (arrayCounter == size-1)){
            arrayCounter = 0;
        }
    }
    void isBST(int count, int size,node* cream, int print, int lower, int upper){
        //initial count should always be 0, arrayCounter as well
        /*if (arrayCounter == 0){
            lower = -10000;
            upper = 10000;
        }*/
        if ((count == arrayCounter) && (arrayCounter == size-1)){
            if((count*2+1)<size){
                if(cream->left->data>cream->data || cream->left->data<lower){
                    bst = false;
                }
            }
            if((count*2+2)<size){
                if(cream->right->data<cream->data || cream->right->data>upper){
                    bst = false;
                }
            }
            if(print == 1){
                if(bst==true){
                    cout << "true" << "\n";
                }
                if(bst==false){
                    cout << "false" << "\n";
                }
            }
        }
        else if (count == arrayCounter){
            if((count*2+1)<size){
                if(cream->left->data>cream->data || cream->left->data<lower){
                    bst = false;
                }
            }
            if((count*2+2)<size){
                if(cream->right->data<cream->data || cream->right->data>upper){
                    bst = false;
                }
            }
            arrayCounter++;
            isBST(0, size, root, print, -10000, 10000);
        }
        if (count < arrayCounter){
            if(cream->left!=NULL){
                //upper = root->data;
                isBST((count*2+1), size, cream->left, print, lower, cream->data);
            }
            if(cream->right!=NULL){
                //lower = root->data;
                isBST((count*2+2), size, cream->right, print, cream->data, upper);
            }
        }
        if ((count == arrayCounter) && (arrayCounter == size-1)){
            arrayCounter = 0;
        }
    }
    void preOrder(int count, int size, node* root){
        //initial count is always 0
        if(count != 0){
            cout << " ";
        }
        cout << root->data;
        if(root->left!=NULL && (count*2+1 < size)){
            preOrder((count*2+1), size, root->left);
        }
        if(root->right!=NULL && (count*2+2 < size)){
            preOrder((count*2+2), size, root->right);
        }

        if(count == 0){
            cout << endl;
        }
    }
    void postOrder(int count, int size, node* root){
        //initial count is always 0
        
        if(root->left!=NULL && (count*2+1 < size)){
            postOrder((count*2+1), size, root->left);
        }
        if(root->right!=NULL && (count*2+2 < size)){
            postOrder((count*2+2), size, root->right); 
        }
        cout << root->data;
        if(count != 0){
            cout << " ";
        }
        //cout << "WTF???";
        
        if(count == 0){
            cout << endl;
        }
    }
    void numNodesInLookup(int givenValue, int count, int size, node* cream){
        isBST(0, nodecount, root, 0, -1000, 1000);
        count++;
        if (bst == true){
            //binary search
            if(cream->data == givenValue){
                cout << (count) << endl;
            }
            else if(givenValue<cream->data){
                numNodesInLookup(givenValue, count, size, cream->left);
            }
            else if(givenValue>cream->data){
                numNodesInLookup(givenValue, count, size, cream->right);
            }
        }
        if (bst == false){
            //level-order traversal (use array)
            toArray(0, nodecount, 0, root);
            for(int i = 0; i < size; i++){
                if(givenValue == arraySave[i]){
                    cout << i+1 << endl;
                    i = size;
                }
            }
        }
    }
};

complete_tree :: complete_tree(){
    //root = NULL;
    nodecount = 0;
    arrayCounter = 0;
    bst = true;
    for (int i = 0; i < 100; i++){
        arraySave[i] = 0;
    }
}



int main(){
    complete_tree Poopy;
    int inputArray[12] = {100, 53, 172, 24, 64, 150, 200, 12, 33, 60, 98, 130};
    Poopy.fromArray(inputArray, sizeof(inputArray)/sizeof(inputArray[0]), Poopy.root);
    Poopy.isBST(0, Poopy.nodecount, Poopy.root, 1, -1000, 1000);
    Poopy.postOrder(0, Poopy.nodecount, Poopy.root);
    //Poopy.toArray(0, Poopy.nodecount, 1, Poopy.root);
    Poopy.numNodesInLookup(98, 0, Poopy.nodecount, Poopy.root);
    return 0;
}
