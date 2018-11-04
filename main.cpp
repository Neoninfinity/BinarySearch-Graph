//
// Created by rahul on 11/3/18.
//

#include <iostream>


struct node
{
    int key_value
    node *left;
    node *right;
    node *parent;

}root = NULL;

node* getNode(int data)
{
    node* newNode = new node();
    newNode->key_value = data;
}
void insert(Node* root,int data){
    if(root == NULL)
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

}
int main(){
    insert(root,15);
    insert(root,10);
    insert(root,20);

}

