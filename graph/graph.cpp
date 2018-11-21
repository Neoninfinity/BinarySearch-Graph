//
// Created by rahul on 11/14/18.
//



#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include "binarySearch.h"
#include <limits>



struct dNode{
    int distance;
    dNode* previousNode = nullptr;
};

class graph{
    //Limit function recieved from https://stackoverflow.com/questions/8690567/setting-an-int-to-infinity-in-c
    int max = std::numeric_limits<int>::max();
    std::vector<tree<int>*> graphEdges;
    std::vector<int> graphVertices;
    std::vector<int> visited;
    std::queue<int> queue;
public:

    void createNode(int data);
    void addConnection(int nodeOne,int nodeTwo,int weight);
    int findNodePosition(int nodeValue);
    int minD(std::vector<int> distance,std::vector<bool> selected);
    void addConnectionFromValue(int nodeOne,int nodeTwo);
    bool breadthFirst(int currentNode,int toFind);
    void dijkstra(int source);
    bool depthFirst(int currentNode, int toFind);
    int print(std::vector<int> dist);
    std::string isConnected();


};

/**
 *This function takes @param data and creates a node
 *holding this specific data value.
 * It assigns a tree to the node.
 */
void graph::createNode(int data)
{
    tree<int>* newTree = new tree<int>;
    this->graphEdges.emplace_back(newTree);
    this->graphVertices.emplace_back(data);

}

/**
 * This function goes through the nodeValue vector to find the position of
 * @param nodeValue, then @return the value of the position
 */
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
/**
 * This function will take in two nodes and the weight it will then add
 * @param nodeOne to be adjacent to @param nodeTwo and vise versa by
 * inserting into a binary tree.
 * @param weight will be added to each node to state the weight between
 * the two nodes.
 */

void graph::addConnection(int nodeOne,int nodeTwo,int weight)
{
    tree<int>* wTree= this->graphEdges[nodeOne];
    node<int>* nLoc = wTree->insert(wTree->rootNode,nodeTwo);
    nLoc->weight = weight;
    tree<int>* wTree2= this->graphEdges[nodeTwo];
    node<int>* nLoc2 = wTree2->insert(wTree2->rootNode,nodeOne);
    nLoc2->weight = weight;
}

/**
 * This function will take in two values @param a & @param b
 * after finding the position will do the same as adding a connection
 * this allows the user to find a node via value
 */
void graph::addConnectionFromValue(int a,int b)
{
    int nodeOne = findNodePosition(a);
    int nodeTwo = findNodePosition(b);
    tree<int>* wTree= this->graphEdges[nodeOne];
    wTree->insert(wTree->rootNode,nodeTwo);
    tree<int>* wTree2= this->graphEdges[nodeTwo];
    wTree2->insert(wTree2->rootNode,nodeOne);
}

/**
 * This function runs a depth first search from @param nodeA
 * @return true is node @param nodeB or @returns false
 */

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

/**
 * Checks if the graph is connected, runs a depth first search from first
 * to last node. DFS puts the nodes into a visited array. If the array size
 * is = to the amount of nodes DFS visited all nodes and hence graph is connected.
 * @return yes if all nodes visited or no if it is not.
 */

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
    int min_ret;
    for(int x = 0; x < graphVertices.size();x++)
    {
        if(!selected[x] && distance[x] < max)
        {
            min_ret = x;
        }
    }
    return  min_ret;
}

int graph::print(std::vector<int> dist)
{
    for (int i = 0; i < graphVertices.size(); i++)
        std::cout<< i << " -> " << dist[i] << std::endl;
}



void graph::dijkstra(int source)
{
    int size = graphVertices.size();
    std::vector<int> dist(size,max);
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

    print(dist);


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


    graph1->dijkstra(0);

}
