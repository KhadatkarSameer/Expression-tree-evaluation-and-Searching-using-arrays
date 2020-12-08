#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/**
 * Class to build a Binary tree and traverse it to find an element
 *
 * @param treeArr - pointer to array that stores the elements of tree
 * @param sortedArr - pointer to array that stores the sorted elements
 * @param size - total number of elements in tree
*/
class Node 
{ 
    public:
    int data; 
    Node *left, *right; 
    Node(int key) 
    {  
        data = key; 
        left = NULL;
        right = NULL;
    } 
};

namespace global
{
    queue<Node*> Queue;   
}

class BinaryTree{
    private:
		vector<int> treeArr;
        int* sortedArr;
		int size,count1;
        Node* root;
    
    public:


        //constructor
        BinaryTree(int size_);
        void insert_btree_as_array(int key);
        vector<int> get_btree_as_array();
        int insert(int key); //insert level order
        bool findByInOrder(int key);
        void Find_1_inorder(Node* r, int key)
        {
            if(r->left!=NULL)
            Find_1_inorder(r->left,key);
            int p=r->data;
            if(p==key) {count1++; return;}
            if(r->right!=NULL)
            Find_1_inorder(r->right,key);
        }
        
        vector<int> Binarytree_as_array();

        bool findByLevelOrder(int key);
        bool Find_2_levelorder(Node* r , int key)
        {
            if(r==root)
            {
                if(root->data==key) return true; //if present will return true
                else global::Queue.push(root);
            }
            while (!global::Queue.empty())
                {
                    Node* temp = global::Queue.front();
                    if(temp->left!=NULL)
                        global::Queue.push(temp->left);
                    if(temp->right!=NULL)
                        global::Queue.push(temp->right);
                    if (global::Queue.front()->data==key)
                    {
                        return true; //if present will return true
                    }
                    global::Queue.pop();
                }
            return false;    
        }

		int* insertSorted(vector<int> keys); //insert all keys in sorted order // Optional: Extra Credit
		bool findByBinarySearch(int key , int s , int l); // Optional: Extra Credit
    
}; 
