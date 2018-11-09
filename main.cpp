//
// Created by rahul on 11/3/18.
//

#include <iostream>
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
    node *left;
    node *right;

};

node* getNode(std::string data)
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
    node* insert(node* rootNode,std::string data);
    node* search(node* rootNode,std::string data);
    node* pre_order(node* pNode);
    void findWord();

};

node* tree::insert(node* leaf,std::string data){
    if(this->rootNode == nullptr)
    {
        return(this->rootNode = getNode(data));

    }
    if((leaf->key_value <= data) == 1)
    {
        if(leaf->right == nullptr)
        {
            return(leaf->right = getNode(data));

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
            return(leaf->left = getNode(data));

        }
        else
        {
            return(tree::insert(leaf->left,data));
        }

    }
}

node* tree::search(node* root, std::string value){
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

std::string readfile(std::string fileOpen){
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

node* tree::pre_order(node* pNode)
{/*
   1. Visit the root.
   2. Traverse the left subtree, i.e., call Preorder(left-subtree)
   3. Traverse the right subtree, i.e., call Preorder(right-subtree) */
    if(pNode == nullptr)
    {
        return pNode;
    }
    std::cout << pNode->key_value << " ";
    pre_order(pNode->left);
    pre_order(pNode->right);
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
int main(){
    tree* tree1= new tree();
    insertText(tree1,"text.txt");
    tree1->findWord();
    tree1->pre_order(tree1->rootNode);

}

