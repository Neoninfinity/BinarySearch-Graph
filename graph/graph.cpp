//
// Created by rahul on 11/14/18.
//



#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include "stack.h"
#include "binarySearch.h"


struct dNode{
    int distance;
    dNode* previousNode = nullptr;
};

class graph{
public:
    std::vector<tree<int>*> graphEdges;
    std::vector<int> graphVertices;
    std::vector<int> visited;
    std::vector<int> stack;
    std::queue<int> queue;
    void createNode(int data);
    void addConnection(int nodeOne,int nodeTwo,int weight);
    int findNodePosition(int nodeValue);
    int minD(std::vector<int> distance,std::vector<bool> selected);
    void addConnectionFromValue(int nodeOne,int nodeTwo);
    void deleteConnection(int nodeOne,int nodeTwo);
    bool breadthFirst(int currentNode,int toFind);
    void dijkstra(int source);
    void dijkstra2(int current,dNode* sets[]);
    bool depthFirst(int currentNode, int toFind);
    bool isPath(int nodeA, int nodeB);
    std::string isConnected();
    int printSolution(std::vector<int> dist);
    bool flag;
};

void graph::createNode(int data)
{
    tree<int>* newTree = new tree<int>;
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

void graph::addConnection(int nodeOne,int nodeTwo,int weight)
{
    tree<int>* wTree= this->graphEdges[nodeOne];
    node<int>* nLoc = wTree->insert(wTree->rootNode,nodeTwo);
    nLoc->weight = weight;
    tree<int>* wTree2= this->graphEdges[nodeTwo];
    node<int>* nLoc2 = wTree2->insert(wTree2->rootNode,nodeOne);
    nLoc2->weight = weight;
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
        return true;
    }

    for(int i = 0; i < adjacent.size(); i++)
    {
        if(!graphEdges[adjacent[i]]->visited)
        {
            depthFirst(adjacent[i],nodeB);
            return false;
        }
    }

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

int graph::minD(std::vector<int> distance,std::vector<bool> selected)
{
    int minimum = 9999;
    for(int x = 0; x < graphVertices.size();x++)
    {
        if(!selected[x] && distance[x] <=minimum)
        {
            minimum = x;
        }
    }
    return  minimum;
}

int graph::printSolution(std::vector<int> dist)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < graphVertices.size(); i++)
        printf("%d tt %d\n", i, dist[i]);
}



void graph::dijkstra(int source)
{
    int size = graphVertices.size();
    std::vector<int> dist(size,9999);
    std::vector<bool> process;
    dist[source] = 0;
    for(int i = 0; i < graphVertices.size(); i++ )
    {
        process.push_back(false);
    }
    while(std::find(process.begin(), process.end(), false) != process.end())
    {
        int minV = minD(dist,process);
        process[minV] = true;
        //process.erase(process.begin()+minV);

        std::vector<node<int>*> adjacent;
        tree<int>* currentTree = graphEdges[minV];
        graphEdges[minV]->getNodes(graphEdges[minV]->rootNode,adjacent);

        for(int v = 0; v < adjacent.size(); v++)
        {
            //from root to adjacent
            int newDistance = dist[minV] + adjacent[v]->weight;
            if(newDistance < dist[adjacent[v]->key_value])
            {
                dist[adjacent[v]->key_value] = newDistance;
            }
        }
    }

    printSolution(dist);


}





int main(){
    auto graph1 = new graph;

    graph1->createNode(33);
    graph1->createNode(14);
    graph1->createNode(15);
    graph1->createNode(6);
    graph1->createNode(4);


    graph1->addConnection(0,3,8);
    graph1->addConnection(0,2,15);
    graph1->addConnection(3,2,8);
    graph1->addConnection(3,1,9);
    graph1->addConnection(1,4,12);


    graph1->depthFirst(0,1);

}
