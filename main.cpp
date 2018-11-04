//
// Created by rahul on 11/3/18.
//

#include <iostream>


struct node
{
    int key_value;
    node *left;
    node *right;

}*root = nullptr;

node* getNode(int data)
{
    node* newNode = new node();
    newNode->key_value = data;
}
node* insert(node* root,int data){
    if(root == nullptr)
    {
        root = getNode(data);

    }
    else if(data <= root->key_value)
    {
        root->left = insert(root->left,data);

    }
    else if(data >= root ->key_value)
    {
        root->right = insert(root->right,data);
    }
    return root;
}

node* search(node* root, int value){
    if(root==nullptr || root->key_value)
    {
        return root;
    }
    else if(root->key_value > value)
    {
        return search(root->left,value);
    }
    else
    {
        return search(root->right,value);
    }
}

int main(){
    insert(root,15);
    insert(root,10);
    insert(root,20);

    node* result = search(root,25);
}

