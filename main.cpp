//
// Created by rahul on 11/3/18.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <cctype>

struct node
{
    std::string key_value;
    node *parent;
    node *left;
    node *right;

};

node* getNode(node* leaf = nullptr, std::string data = nullptr)
{
    auto newNode = new node();
    newNode->key_value = data;
    newNode->right = nullptr;
    newNode->left = nullptr;
    newNode->parent = leaf;
    return newNode;
}

class tree{
public:

    node* rootNode;
    std::vector<node*> retVec;
    node* insert(node* rootNode,std::string data = "" ,node* parent = nullptr);
    node* search(node* rootNode,std::string data);
    node* pre_order(node* pNode);
    node* in_order_next(node* iNode);
    void deleteNode(std::string toDelete);
    void findWord();

};

node* tree::insert(node* leaf ,const std::string data,node* parent){
    if(this->rootNode == nullptr)
    {
        return(this->rootNode = getNode(parent,data));

    }
    if((leaf->key_value <= data) == 1)
    {
        if(leaf->right == nullptr)
        {
            return(leaf->right = getNode(leaf,data));

        }
        else
        {
            return(tree::insert(leaf->right,data,leaf));
        }

    }
    else
    {
        if(leaf->left == nullptr)
        {
            return(leaf->left = getNode(leaf,data));

        }
        else
        {
            return(tree::insert(leaf->left,data,leaf));
        }

    }
}

node* tree::search(node* root, const std::string value){
    if(root==nullptr)
    {
        std::cout << "Pointer is null data was not found." << value << std::endl;
        return nullptr;
    }
    else if(root->key_value > value)
    {
        std::cout << "Data is smaller than node value '" << root -> key_value << "' going left" << std::endl;
        return search(root->left,value);
    }
    else if(root->key_value < value)
    {
        std::cout << "Data is bigger than node value '" << root -> key_value << "' going right" << std::endl;
        return search(root->right,value);
    }
    else
    {
        return root;
    }
}

std::string readfile(const std::string fileOpen){
    std::ifstream file;
    std::string line;
    std::string newString;
    file.open(fileOpen);

    while (getline (file, line)) {
        newString.append(line);
    }

   file.close();

    for(std::string::iterator i = newString.begin(); i != newString.end(); i++)
    {
        if(!isalpha(newString.at(i - newString.begin())) && isspace(newString.at(i - newString.begin())) == 0)
        {
                newString.erase(i);
                i--;
        }
    }

   return newString;
}

std::vector<std::string> stringToVector(const std::string str)
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

void tree::findWord()
{
    std::string toFind; std::cin >> toFind; std::cout << std::endl;
    node* result = this->search(rootNode,toFind);
    if(result == nullptr)
    {
        std::cout << "This value was not found" << std::endl;
    }
    else {
        std::cout << result->key_value << " was found" << std::endl;
    }
}


void insertText(tree* selectedTree,std::string fileToInsert)
{
    std::string documentText = readfile(fileToInsert);
    transform(documentText.begin(), documentText.end(), documentText.begin(), tolower); //Applies operation sequentially to make the text lowercase.
    std::vector<std::string> textVec = stringToVector(documentText);
    for(int i = 0;i < textVec.size();i++)
    {
        *selectedTree->insert(selectedTree->rootNode,textVec[i]);
    }

}

node* tree::pre_order(node* pNode)
{
    if(pNode == nullptr)
    {
        return pNode;
    }
    std::cout << pNode->key_value << " ";
    pre_order(pNode->left);
    pre_order(pNode->right);
}

node* tree::in_order_next(node* iNode)
{
    node* current = iNode;
    while (current->left != nullptr)
        current = current->left;

    return current;
}

void tree::deleteNode(std::string toDelete){
    transform(toDelete.begin(), toDelete.end(), toDelete.begin(), tolower);
    node* result = this->search(rootNode,toDelete);

    if(result->left == nullptr && result->right == nullptr)
    {
        if(result->parent->key_value > result->key_value)
        {
            result->parent->left = nullptr;
            free(result);
        }
    }
    else if(result->left != nullptr ^ result->right != nullptr)
    {
        if(result->left != nullptr)
        {
            result->key_value = result->left->key_value;
            result->left = nullptr;
            free(result->left);
        }
        else
        {
            result->key_value = result->right->key_value;
            result->right = nullptr;
            free(result->right);
        }
    }
    else
    {
        node* furthestValue;
        if(toDelete > rootNode->key_value)
        {
            furthestValue= this->in_order_next(rootNode->left);
        }
        else
        {
            furthestValue = this->in_order_next(rootNode->right);
        }
        std::string temp = result->key_value;
        result->key_value = furthestValue->key_value;
        if(furthestValue->parent->key_value > furthestValue->key_value)
        {
            furthestValue->parent->left = nullptr;
        }
        else
        {
            furthestValue->parent->right = nullptr;
        }
    }
}


int main(){
    auto tree1= new tree();
    insertText(tree1,"text.txt");
    tree1->deleteNode("cat");

    tree1->insert(tree1->rootNode,"hello");

}

