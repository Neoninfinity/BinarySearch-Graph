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

template<class T>
struct node
{
    T key_value;
    node *parent;
    node *left;
    node *right;

};

template<typename  T>
node<T>* getNode(node<T>* leaf = nullptr, T data = nullptr)
{
    auto newNode = new node<T>();
    newNode->key_value = data;
    newNode->right = nullptr;
    newNode->left = nullptr;
    newNode->parent = leaf;
    return newNode;
}

template <typename T>
class tree{
public:
    node<T>* rootNode;
    node<T>* pre_order(node<T>* pNode);
    node<T>* in_order_next(node<T>* iNode);
    node<T>* insert(node<T>* rootNode,T data,node<T>* parent = nullptr);
    node<T>* search(node<T>* rootNode,T data);
    void deleteNode(T toDelete);
    void  findWord();

};

template<typename T>
node<T>* tree<T>::insert(node<T>* leaf ,T data,node<T>* parent){
    if(this->rootNode == nullptr)
    {
        return(this->rootNode = getNode(parent,data));

    }
    if(data < leaf->key_value)
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
    else
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
}

template<typename T>
node<T>* tree<T>::search(node<T>* root, T value){
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
template<typename T>
std::string readfile(const T fileOpen){
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

template <typename T>
void tree<T>::findWord()
{
    std::string toFind; std::cin >> toFind; std::cout << std::endl;
    node<T>* result = this->search(rootNode,toFind);
    if(result == nullptr)
    {
        std::cout << "This value was not found" << std::endl;
    }
    else {
        std::cout << result->key_value << " was found" << std::endl;
    }
}

template <typename T>
void insertText(tree<T>* selectedTree,std::string fileToInsert)
{
    std::string documentText = readfile(fileToInsert);
    transform(documentText.begin(), documentText.end(), documentText.begin(), tolower); //Applies operation sequentially to make the text lowercase.
    std::vector<std::string> textVec = stringToVector(documentText);
    for(int i = 0;i < textVec.size();i++)
    {
        *selectedTree->insert(selectedTree->rootNode,textVec[i]);
    }

}

template<typename T>
node<T>* tree<T>::pre_order(node<T>* pNode)
{
    if(pNode == nullptr)
    {
        return pNode;
    }
    std::cout << pNode->key_value << " ";
    pre_order(pNode->left);
    pre_order(pNode->right);
}


template <typename T>
node<T>* tree<T>::in_order_next(node<T>* iNode)
{
    node<T>* current = iNode;
    while (current->left != nullptr)
        current = current->left;

    return current;
}

template <typename T>
void tree<T>::deleteNode(T toDelete){
    transform(toDelete.begin(), toDelete.end(), toDelete.begin(), tolower);
    node<T>* result = this->search(rootNode,toDelete);

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
        node<T>* furthestValue;
        if(toDelete > rootNode->key_value)
        {
            furthestValue= this->in_order_next(rootNode->left);
        }
        else
        {
            furthestValue = this->in_order_next(rootNode->right);
        }
        result->key_value = furthestValue->key_value;
        if(furthestValue->parent->key_value > furthestValue->key_value)
        {
            furthestValue->parent->left = nullptr;
        }
        else
        {
            furthestValue->parent->right = nullptr;
        }
        free(furthestValue);
    }
}
