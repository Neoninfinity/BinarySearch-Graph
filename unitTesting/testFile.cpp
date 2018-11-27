//
// Created by rahul on 11/27/18.
//


#include "../main/graph.h"

int main()
{
    auto graph1 = new graph;
    graph1->createMultipleNodes(7);
    graph1->addConnection(0,5,9);
    graph1->addConnection(1,5,3);
    graph1->addConnection(1,4,4);
    graph1->addConnection(0,4,5);
    graph1->addConnection(0,2,12);
    graph1->addConnection(2,4,4);
    graph1->addConnection(4,3,6);
    graph1->addConnection(3,6,4);

    graph1->breadthFirst(5,2);
    graph1->depthFirst(5,2);
    graph1->isPath(5,2);
}