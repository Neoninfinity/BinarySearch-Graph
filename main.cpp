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

}*root;

class binaryTree
{
public:
    void insert(int key);
    void destroy_tree();
    void *search(int key);

private:

};