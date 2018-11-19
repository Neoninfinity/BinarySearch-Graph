//
// Created by rahul on 11/14/18.
//



#include <iostream>
#include <vector>
#include <queue>
#include "../binaryTree/binarySearch.cpp"
#include "stack.h"

class graph{
public:
    std::vector<tree<int>*> graphEdges;
    std::vector<int> graphVertices;
    std::vector<int> visited;
    std::vector<int> stack;
    std::queue<int> queue;
    void createNode(int data);
    void addConnection(int nodeOne,int nodeTwo);
    int findNodePosition(int nodeValue);
    void addConnectionFromValue(int nodeOne,int nodeTwo);
    void deleteConnection(int nodeOne,int nodeTwo);
    bool breadthFirst(int currentNode,int toFind);
    bool depthFirst(int currentNode, int toFind);
    bool isPath(int nodeA, int nodeB);
    std::string isConnected();
    bool flag;
};

void graph::createNode(int data)
{
    auto newTree = new tree<int>;
    this->graphEdges.emplace_back(newTree);
    this->graphVertices.emplace_back(data);

}

/* Searching algorithm to convert value to node position takes value and returns position */


int graph::findNodePosition(int nodeValue)
{
    for(int i =0; i < graphVertices.size(); i++)
    {
        if (graphVertices[i] == nodeValue)
        {
            return i;
        }
    }
}

void graph::addConnection(int nodeOne,int nodeTwo)
{
    tree<int>* wTree= this->graphEdges[nodeOne];
    wTree->insert(wTree->rootNode,nodeTwo);
    tree<int>* wTree2= this->graphEdges[nodeTwo];
    wTree2->insert(wTree2->rootNode,nodeOne);
}

void graph::addConnectionFromValue(int a,int b)
{
    int nodeOne = findNodePosition(a);
    int nodeTwo = findNodePosition(b);
    tree<int>* wTree= this->graphEdges[nodeOne];
    wTree->insert(wTree->rootNode,nodeTwo);
    tree<int>* wTree2= this->graphEdges[nodeTwo];
    wTree2->insert(wTree2->rootNode,nodeOne);
}

bool graph::depthFirst(int nodeA, int nodeB)
{
    std::vector<int> adjacent;
    tree<int>* currentTree = graphEdges[nodeA];
    graphEdges[nodeA]->getValues(graphEdges[nodeA]->rootNode,adjacent);

    currentTree->visited = true;
    visited.emplace_back(nodeA);
    std::cout << nodeA;

    if(nodeA == nodeB)
    {
        flag = true;
    }
    else
    {
        flag = false;
    }


    for(int i = 0; i < adjacent.size(); i++)
    {
        if(!graphEdges[adjacent[i]]->visited)
        {
            isPath(adjacent[i],nodeB);
        }
    }
    return flag;
}

std::string graph::isConnected(){
    depthFirst(0,graphEdges.size()-1);
    if(visited.size() != graphVertices.size())
    {
        return "no";
    }
    else
    {
        return "yes";
    }
}

bool graph::breadthFirst(int currentNode,int toFind)
{
    if(currentNode == toFind)
    {
        return true;
    }
    std::vector<int> adjacent;
    tree<int>* currentTree = graphEdges[currentNode];
    graphEdges[currentNode]->getValues(graphEdges[currentNode]->rootNode,adjacent);
    currentTree->visited = true;
    for(int i = 0; i < adjacent.size(); i++)
    {
        if(adjacent[i] != currentNode && !graphEdges[i+1]->visited)
        {
            queue.push(adjacent[i]);
            graphEdges[i]->visited = true;

        }
    }
    int newNode = queue.front();
    queue.pop();
    breadthFirst(newNode,toFind);
}




int main(){
    auto graph1 = new graph;

    graph1->createNode(1);
    graph1->createNode(2);
    graph1->createNode(3);
    graph1->createNode(4);
    graph1->createNode(5);
    graph1->createNode(6);
    graph1->createNode(7);
    graph1->createNode(8);
    graph1->createNode(9);


    graph1->addConnection(0,1);
    graph1->addConnection(0,2);
    graph1->addConnection(2,3);
    graph1->addConnection(2,7);
    graph1->addConnection(7,8);
    graph1->addConnection(3,8);
    graph1->addConnection(3,5);
    graph1->addConnection(5,6);
    graph1->addConnection(7,6);
    graph1->addConnection(7,8);

    graph1->depthFirst(0,8);
}
