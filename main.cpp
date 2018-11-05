//
// Created by rahul on 11/3/18.
//

#include <iostream>


struct node
{
    int key_value;
    node *left;
    node *right;

};

node* root = nullptr;

node* getNode(int data)
{
    node* newNode = new node();
    newNode->key_value = data;
    return newNode;
}

class tree{
public:
    node* insert(node* root, int data);
    int rootData;
    int* rootLeft;
    int* rootRight;
};

node* tree::insert(node* root,int data){
    if(root == nullptr)
    {
        this.root = getNode(data);

    }
    else if(root->key_value >= data)
    {
        return(insert(root->left,data));
    }
    else
    {
        return(tree::insert(root->right,data));
    }
}

node* search(node* root, int value){
    if(root==nullptr)
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
    tree* tree1= new tree();
    *tree1->insert(root,60);
}

