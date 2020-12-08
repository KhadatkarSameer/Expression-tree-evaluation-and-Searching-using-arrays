#include <queue>
#include <stack>
#include <queue>
#include <vector>
#include <chrono>
#include "TreeSearch.h"
#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

/**
 * Constructor to instantiate the array
 * @param size_ - number elements in tree
 */
BinaryTree::BinaryTree(int size_)
{
    size= size_;
    sortedArr = new int[size_];
}

void BinaryTree::insert_btree_as_array( int key)
{treeArr.push_back(key);}

vector<int> BinaryTree::get_btree_as_array()
{
    return treeArr;
}

namespace global
{
    queue<Node*> Qu;
    int i=0;
};


/**
 * Function to insert an element into the tree in level order
 * @param key - element to be inserted
 */
int BinaryTree::insert(int key)
{
    if (global::i==0)
    {
        Node* temp=new Node(key);
        root=temp;
        global::Qu.push(root);
        global::i++;
    }
    
    else if(global::i==1)
    {
        Node* temp =global::Qu.front();
        if(temp->left==NULL)
        {
            Node* l=new Node(key);
            temp->left=l;
            global::Qu.push(l);
        }
        else if(temp->right==NULL)
        {
            Node* r=new Node(key);
            temp->right=r;
            global::Qu.push(r);
        }
        else if(temp->right!=NULL && temp->left!=NULL)
        {
            global::Qu.pop();
            insert(key);
        }
    }
    return 0;
}



/**
 * Function to find the key by performing a inorder order traversal of the tree
 * @param key - key to be searched for in the tree
 */
bool BinaryTree::findByInOrder(int key)
{
    count1=0;
    Find_1_inorder(root,key);
    if(count1>0) return true;
    else return false;
}

/**
 * Function to find the key by performing a level order traversal of the tree
 * @param key - key to be searched for in the tree
 */
bool BinaryTree::findByLevelOrder(int key)
{
    return Find_2_levelorder(root,key);
}
/**
 * Optional: Extra Credit
 * Function to insert all elements as a sorted array
 * @param keys - elements to be inserted in sorted order
 */
int* BinaryTree::insertSorted(vector<int> keys) 
{
	sort(keys.begin(), keys.end());
    for(int i=0; i<keys.size(); i++) 
        sortedArr[i]=keys[i];
    return sortedArr;
}

/**
 * Optional: Extra Credit
 * Function to find the key by performing a binary search over sorted array
 * @param key - key to be searched for in the sorted array
 */
bool BinaryTree::findByBinarySearch(int key , int s , int l)
{
	    if (l >= s) { 
        int mid = s + (l - s) / 2;
        if (sortedArr[mid] == key) 
            return true; 
        if (sortedArr[mid] > key) 
            return findByBinarySearch(key, s , mid - 1); 
        else
            return findByBinarySearch(key, mid + 1, l); 
    }  
    return false;
}

int main(int argc, char *argv[]){
    // read from input number and query files using the file name passed in as inputs
    
    

    vector<int> Arr;
   
    ifstream numfile(argv[1]);
    if (numfile.fail())
    {
        cout<<"Sorry No file given"<<endl;
    }
    else
    {
        // insert each input number into the tree
        string first_line;
        int size1;
        if (!numfile.eof())
        {
            getline(numfile, first_line);         
            size1 = stoi(first_line);
        }
        BinaryTree tree1 = BinaryTree(size1);
        int j=0;
        while(!numfile.eof() && j<size1)
        {
            string s;
            getline(numfile, s);         
            int key = stoi(s);
            tree1.insert_btree_as_array(key);
            j++;
        }
        vector<int> BtreeArr=tree1.get_btree_as_array();
    }
    numfile.close();
    ifstream input_file(argv[2]);
    
    if (input_file.fail())
    {
        cout<<"Sorry No file given"<<endl;
    }
    else
    {
        // insert each input number into the tree
        string first_line;
        int size;
        if (!input_file.eof())
        {
            getline(input_file, first_line);         
            size = stoi(first_line);
        }

        BinaryTree tree = BinaryTree(size);
        int j=0;
        while(!input_file.eof() && j<size)
        {
            string s;
            getline(input_file, s);         
            int key = stoi(s);
            tree.insert(key);
            Arr.push_back(key);
            j++;
        }
        // iterate and search for each query number using inorder traversal
        // measure the total time taken to for all the number using inorder
        input_file.clear();
        input_file.seekg(0);

        
        
        if (!input_file.eof())
            getline(input_file, first_line);

        auto start1 = chrono::steady_clock::now();
        

        int k=0,countinorder=0;
        while(!input_file.eof() && k<size)
        {
            string p;
            getline(input_file, p);         
            int key = stoi(p);
            if(tree.findByInOrder(key))
                countinorder++;
            k++;
        }
        auto end1 = chrono::steady_clock::now();
        

        // iterate and search for each query number using level-order traversal
        // measure the total time taken to for all the number using inorder
        input_file.clear();
        input_file.seekg(0);

        if (!input_file.eof())
            getline(input_file, first_line);

        auto start2 = chrono::steady_clock::now();

        int l=0,countlevelorder=0;
        while(!input_file.eof() && l<size)
        {
            string q;
            getline(input_file, q);         
            int key = stoi(q);
            if(tree.findByLevelOrder(key))
                countlevelorder++;
            l++;
        }
        auto end2 = chrono::steady_clock::now();

        int countfinal=0;
        if(countinorder==countlevelorder)
            countfinal=countlevelorder;


        
        cout << "A2a:"<<countfinal<<","
        << chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count()<<","
        << chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count()
        << endl;
        
        input_file.clear();
        input_file.seekg(0);

        
        int* Sorted_Array=tree.insertSorted(Arr);
       
        if (!input_file.eof())
            getline(input_file, first_line);

        auto start3 = chrono::steady_clock::now();
        int m=0,countBinary=0;
        while(!input_file.eof() && m<size)
        {
            string r;
            getline(input_file, r);         
            int key = stoi(r);
            if(tree.findByBinarySearch(key , 0 , size-1))
                countBinary++;
            m++;
        }
        auto end3 = chrono::steady_clock::now();

        
        cout << "A2c:"
        << chrono::duration_cast<chrono::nanoseconds>(end3 - start3).count()
        << endl;
        input_file.close();

    
    }
	

    // output in the format "A2a:123,456,789" where:
	// 123<=m is the number matching query numbers found
    // 456 is the totoal time taken in milliseconds to complete the search using inorder traversal, and
	// 789 is the total time taken in milliseconds to complete this search using level-order traversal.
}