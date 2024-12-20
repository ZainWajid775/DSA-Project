#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
using namespace std;

//Value at left of B_Node is smaller
//Value at right of B_Node is bigger

struct B_Node
{
    int data;
    B_Node* left;
    B_Node* right;

    B_Node(int val) : data(val) , left(nullptr) , right(nullptr) {}
};

//Recursively calls itself with a new B_Node until it reaches an empty B_Node where value can be inserted
//Return a B_Node pointer which is inserted at the left or right pointers
B_Node* insert(B_Node* root , int val)
{
    //Insert new B_Node if position found
    if(root == nullptr)
    {
        return new B_Node(val);
    }

    //Recursively call itself with a new B_Node until nullptr is found
    if(val < root->data)
    {
        root->left = insert(root->left , val);
    }
    else
    {
        root->right = insert(root->right , val);
    }

    return root;
}

bool search(B_Node* root , int val)
{
    if(root == nullptr)
    {
        return false;
    }

    //Check value of current B_Node
    if(val == root->data)
    {
        return true;
    }

    //Continue searching left or right depending on value being greater or larger than B_Node data
    if(val < root->data)
    {
        return search(root->left , val);
    }
    else
    {
        return search(root->right , val);
    }
}

//TRAVERSAL

//1. Inorder : Left -> Root -> Right, Sorted Order
//Traverses through left tree first
void in_order(B_Node* root)
{
    if(root == nullptr)
    {
        return;
    }
    in_order(root->left);
    cout << root->data << " ";
    in_order(root->right);
}

//2. Preorder : Root -> Left -> Right
void pre_order(B_Node* root)
{
    if(root == nullptr) 
    {
        return;
    }
    cout << root->data << " ";
    pre_order(root->left);
    pre_order(root->right);
}

//3. Postorder : Left -> Right -> Root
void post_order(B_Node* root)
{
    if(root == nullptr)
    {
        return;
    }
    post_order(root->left);
    post_order(root->right);
    cout << root->data << " ";
}

//4. Level order : Breadth First Search(BFS)
void level_order(B_Node* root)
{
    if(root == nullptr)
    {
        return;
    }

    //Push the current B_Node into a queue
    queue<B_Node*> q;
    q.push(root);

    while(!q.empty())
    {
        //Output the current B_Node and remove it
        B_Node* current =q.front();
        cout << current->data << " ";
        q.pop();

        //If the B_Node has any children, add them into the queue 

        if(current->left != nullptr)
        {
            q.push (current->left);
        }

        if(current->right != nullptr)
        {
            q.push(current->right);
        }
    }
}

B_Node* min (B_Node* root)
{
    while(root && root->left != nullptr)
    {
        root = root->left;
    }
    return root;
}

B_Node* delete_B_Node(B_Node* root , int key)
{
    if(root == nullptr)
    {
        return root;
    }

    //Traverse down the tree until value matches key
    if(key < root->data)
    {
        root->left = delete_B_Node(root->left, key);
    }
    else if(key > root->data)
    {
        root->right = delete_B_Node(root->right , key);
    }

    //Else runs when key matches value, B_Node is one to be deleted
    else
    {
        //Case B_Node has one or no children
        //Replace the B_Node with either its inorder successor or predecessor
        if(root->left == nullptr)
        {
            B_Node* temp = root->right;
            delete root;
            return temp;
        }
        else if(root->right == nullptr)
        {
            B_Node* temp = root->left;
            delete root;
            return temp;
        }

        //Case B_Node has 2 children
        //Find the smallest value on the right subtree
        B_Node* temp = min(root->right);

        //Change the current B_Nodes data to the smallest value in the right subtree
        root->data = temp->data;

        //Delete inorder successor
        root->right = delete_B_Node(root->right , temp->data);
    }

    return root;
}

#endif



