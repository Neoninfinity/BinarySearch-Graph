//
// Created by rahul on 11/14/18.
//

#include <iostream>
#include <vector>
#include "binarySearch.h"

class graph{
public:
    std::vector<tree<int>*> graphEdges;
    std::vector<int> graphVertices;
    void createNode(int data);
    void addConnection(int nodeOne,int nodeTwo);
    int findNodePosition(int nodeValue);
    void addConnectionFromValue(int nodeOne,int nodeTwo);

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


int main(){
    auto graph1 = new graph;

    graph1->createNode(7);
    graph1->createNode(8);
    graph1->createNode(10);
    graph1->createNode(5);

    graph1->addConnection(0,1);
    graph1->addConnection(1,2);
    graph1->addConnection(2,3);
    graph1->addConnection(3,0);
}