/**
    210CT Coursework 1
    binarySearch.cpp
    Purpose: Create a binary tree and fulfil
    tasks stated on assignment brief

    @author Rahul Prashar
    @version 1.1 21/11/18
*/

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


/**
 * defines a binary tree node of type @tparam T
 */
template<class T>
struct node
{
    T key_data;
    int weight;
    node *parent;
    node *left;
    node *right;

};

/**
 * this function is called when the values of the node
 * need to be set.
 * @tparam T takes a node of type T
 * @param leaf this will be the parent of the new node
 * @param data this is the data to be stored
 * @returns the new node created
 */
template<typename  T>
node<T>* getNode(node<T>* leaf = nullptr, T data = nullptr)
{
    auto newNode = new node<T>();
    newNode->weight;
    newNode->key_data = data;
    newNode->right = nullptr;
    newNode->left = nullptr;
    newNode->parent = leaf;
    return newNode;
}

template <typename T>

/**
 * Class to create a tree of type @tparam T
 * Contains all functions and parameters needed.
 */

class tree{
public:
    bool visited;
    node<T>* rootNode = nullptr;
    bool findWord(int toFind);
    bool findWord(std::string toFind);
    void deleteNode(T toDelete);
    void insertText(std::string fileToInsert);
    std::vector<T> pre_order(node<T>* pNode,std::vector<T> Vec = {});
    node<T>* in_order_next(node<T>* iNode);
    node<T>* insert(node<T>* rootNode,T data,node<T>* parent = nullptr);
    node<T>* search(node<T>* rootNode,T data);
    std::vector<int> getValues(node<T>* pNode,std::vector<int>& retVec);
    std::vector<node<T>*> getNodes(node<T>* pNode,std::vector<node<T>*>& retVec);
};

/**
 * Inserts a new node of value @param data of type @tparam T
 * @param leaf is the currently working node within an iteration
 * @param data is the data to be added into the tree
 * @param parent is the node of the previous iteration
 * @returns the position of the new node.
 */
template<typename T>
node<T>* tree<T>::insert(node<T>* leaf ,T data,node<T>* parent){
    if(this->rootNode == nullptr)
    {
        return(this->rootNode = getNode(parent,data));

    }
    if(findWord(data))
    {
        return leaf;
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

/**
 * Searches through the existing binary tree of type @tparam T
 * to find @param value
 * @param root this is the initial search root node (top of the tree)
 * @return the position of the node OR a nullptr if its not found.
 */

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

/**
 * Opens a text file and removes unnecessary punctuation
 * then returns a string of the new string.
 * @param fileOpen is the file to be opened
 * @returns the new string extracted from the file
 */
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

/**
 * Takes a string then splits it into a vector
 * @param str the string to split.
 * @returns the split vector.
 */
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

/**
 * Template specilization for integer values
 * Then returns a statement whether found or not.
 */
template <>
bool tree<int>::findWord(int toFind)
{
    std::cout << std::endl;
    node<int>* result = this->search(rootNode,toFind);
    if(result == nullptr)
    {
        std::cout << "This value was not found" << std::endl;
        return false;
    }
    else {
        std::cout << result->key_data << " was found" << std::endl;
        return true;
    }
}

/**
 * When called requires user input then searches for that value.
 * Then returns a statement whether found or not.
 */
template <>
bool tree<std::string>::findWord(std::string toFind)
{
    std::transform(toFind.begin(), toFind.end(), toFind.begin(), ::tolower);
    std::cout << std::endl;
    node<std::string>* result = this->search(rootNode,toFind);
    if(result == nullptr)
    {
        std::cout << "This value was not found" << std::endl;
        return false;
    }
    else {
        std::cout << result->key_data << " was found" << std::endl;
        return true;
    }
}

/**
 * Takes a file and tree makes all the words lowercase
 * then inserts into the tree iteratively.
 * @param selectedTree this is the tree to insert into
 * @param fileToInsert this is the file to insert
 */
template <>
void tree<std::string>::insertText(std::string fileToInsert)
{
    std::string documentText = readfile(fileToInsert);
    transform(documentText.begin(), documentText.end(), documentText.begin(), tolower); //Applies operation sequentially to make the text lowercase.
    std::vector<std::string> textVec = stringToVector(documentText);
    for(int i = 0;i < textVec.size();i++)
    {
        this->insert(this->rootNode,textVec[i]);
    }

}



/**
 * Used in the graph to get all values as an vector of integers
 * @param pNode current node that the function is on
 * @param retVec the vector to insert into
 * @returns the new vector
 */
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

/**
 * Used in the graph to get all nodes as an vector of nodes
 * @param pNode current node that the function is on
 * @param retVec the vector to insert into
 * @returns the new vector
 */
template<typename T>
std::vector<node<T>*> tree<T>::getNodes(node<T>* pNode,std::vector<node<T>*>& retVec)
{
    if(pNode->left != nullptr)
    {
        getNodes(pNode->left,retVec);
    }

    retVec.emplace_back(pNode);
    if(pNode->right != nullptr)
    {
        getNodes(pNode->right,retVec);
    }
    return retVec;

}

/**
 * prints the values in a tree in pre-order
 * @param pNode this is the root node where pre-order will start from
 * @returns last node parameter
 */

template <typename T>
std::vector<T> tree<T>::pre_order(node<T>* pNode, std::vector<T> retVec)
{
    if(pNode == nullptr)
    {
        return retVec;
    }
    if(pNode == rootNode)
    {
        retVec.empty();
    }

    retVec.push_back(pNode->key_data);
    retVec = pre_order(pNode->left,retVec);
    retVec = pre_order(pNode->right,retVec);
    return retVec;


}

/**
 * gets the next in_order value for two children deletion
 * @param iNode is the next node in_order
 * @returns the next node in in_order list
 */
template <typename T>
node<T>* tree<T>::in_order_next(node<T>* iNode)
{
    node<T>* current = iNode;
    while (current->left != nullptr)
        current = current->left;

    return current;
}


/**
 * Deletes a node within the binary Tree and frees memory
 * @param toDelete this is the value to delete
 */
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
        else{
            result->parent->right = nullptr;
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
        furthestValue = this->in_order_next(rootNode->right);
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
