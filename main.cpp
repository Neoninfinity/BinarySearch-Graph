//
// Created by rahul on 11/3/18.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>

struct node
{
    int key_value;
    node *left;
    node *right;

};

node* getNode(int data,node* par)
{
    node* newNode = new node();
    newNode->key_value = data;
    newNode->right = nullptr;
    newNode->left = nullptr;
    return newNode;
}

class tree{
public:

    node* rootNode;
    node* insert(node* rootNode,int data);
    node* search(node* rootNode,int data);

};

node* tree::insert(node* leaf,int data){
    if(this->rootNode == nullptr)
    {
        return(this->rootNode = getNode(data,nullptr));

    }
    if(leaf->key_value <= data)
    {
        if(leaf->right == nullptr)
        {
            return(leaf->right = getNode(data,leaf));

        }
        else
        {
            return(tree::insert(leaf->right,data));
        }

    }
    else
    {
        if(leaf->left == nullptr)
        {
            return(leaf->left = getNode(data,leaf));

        }
        else
        {
            return(tree::insert(leaf->left,data));
        }

    }
}

node* tree::search(node* root, int value){
    if(root==nullptr)
    {
        return nullptr;
    }
    else if(root->key_value > value)
    {
        return search(root->left,value);
    }
    else if(root->key_value < value)
    {
        return search(root->right,value);
    }
    else
    {
        return root;
    }
}


std::string readfile(){
    std::ifstream file;
    std::string line;
    std::string newString;
    file.open("text.txt");

    while (getline (file, line)) {
        newString.append(line);
    }

   file.close();

    for(std::string::iterator i = newString.begin(); i != newString.end(); i++)
    {
        if(!isalpha(newString.at(i - newString.begin())) && isspace(newString.at(i - newString.begin())) == false)
        {
                newString.erase(i);
                i--;
        }
    }

   return newString;
}

std::vector<std::string> stringToVector(std::string str)
{
    std::string buffer;
    std::stringstream ss(str);
    std::vector<std::string> words;
    while(ss >> buffer)
    {
        words.push_back(buffer);
    }
    return words;
}

int main(){
    std::string documentText = readfile();
    std::vector<std::string> textVec = stringToVector(documentText);



    tree* tree1= new tree();
    *tree1->insert(tree1->rootNode,15);
    *tree1->insert(tree1->rootNode,10);
    *tree1->insert(tree1->rootNode,20);
    *tree1->insert(tree1->rootNode,25);

    node* result = tree1->search(tree1->rootNode,20);

    if(result == nullptr)
    {
        std::cout << "This value was not found";
    }
    else {
        std::cout << result->key_value << " was found";
    }
*/





}

