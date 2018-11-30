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
    T key_data;
    node *parent;
    node *left;
    node *right;

};

template<typename  T>
node<T>* getNode(node<T>* leaf = nullptr, T data = nullptr)
{
    auto newNode = new node<T>();
    newNode->key_data = data;
    newNode->right = nullptr;
    newNode->left = nullptr;
    newNode->parent = leaf;
    return newNode;
}

template <typename T>
class tree{
public:
    node<T>* rootNode;
    bool visited;
    node<T>* pre_order(node<T>* pNode);
    node<T>* in_order_next(node<T>* iNode);
    node<T>* insert(node<T>* rootNode,T data,node<T>* parent = nullptr);
    node<T>* search(node<T>* rootNode,T data);
    std::vector<int> getValues(node<T>* pNode,std::vector<int>& retVec);
    void deleteNode(T toDelete);
    void  findWord();

};

template<typename T>
node<T>* tree<T>::insert(node<T>* leaf ,T data,node<T>* parent){
    if(this->rootNode == nullptr)
    {
        return(this->rootNode = getNode(parent,data));

    }
    if(data < leaf->key_data)
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
    else if(root->key_data > value)
    {
        std::cout << "Data is smaller than node value '" << root -> key_data << "' going left" << std::endl;
        return search(root->left,value);
    }
    else if(root->key_data < value)
    {
        std::cout << "Data is bigger than node value '" << root -> key_data << "' going right" << std::endl;
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
        std::cout << result->key_data << " was found" << std::endl;
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
std::vector<int> tree<T>::getValues(node<T>* pNode,std::vector<int>& retVec)
{
    if(pNode->left != nullptr)
    {
        getValues(pNode->left,retVec);
    }

    retVec.emplace_back(pNode->key_data);
    if(pNode->right != nullptr)
    {
        getValues(pNode->right,retVec);
    }
    return retVec;

}

template <typename T>
node<T>* tree<T>::pre_order(node<T>* pNode)
{
    if(pNode == nullptr)
    {
        return pNode;
    }
    std::cout << pNode->key_data << " ";
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
        if(result->parent->key_data > result->key_data)
        {
            result->parent->left = nullptr;
            free(result);
        }
    }
    else if(result->left != nullptr ^ result->right != nullptr)
    {
        if(result->left != nullptr)
        {
            result->key_data = result->left->key_data;
            result->left = nullptr;
            free(result->left);
        }
        else
        {
            result->key_data = result->right->key_data;
            result->right = nullptr;
            free(result->right);
        }
    }
    else
    {
        node<T>* furthestValue;
        if(toDelete > rootNode->key_data)
        {
            furthestValue= this->in_order_next(rootNode->left);
        }
        else
        {
            furthestValue = this->in_order_next(rootNode->right);
        }
        result->key_data = furthestValue->key_data;
        if(furthestValue->parent->key_data > furthestValue->key_data)
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
