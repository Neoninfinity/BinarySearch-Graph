/**
    210CT Coursework 1
    graph.cpp
    Purpose: Create a graph and fulfil
    tasks stated on assignment brief

    @author Rahul Prashar
    @version 1.0 21/11/18
*/


#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <limits>

/**
 * graph structure allows multiple instances
 * Contains all functions & data structures
 * that may be needed by the graph
 */

class graph{
    //Limit function received from https://stackoverflow.com/questions/8690567/setting-an-int-to-infinity-in-c
    int max = std::numeric_limits<int>::max();
    std::vector<tree<int>*> graphEdges;
    std::vector<int> graphVertices;
    std::vector<int> visited;
    std::queue<int> queue;
    bool flag = false;
public:

    //Task 3
    void createNode(int data =0);
    void createMultipleNodes(int amount);
    void addConnection(int nodeOne,int nodeTwo,int weight = 0);
    void addConnectionFromValue(int a,int b,int weight = 0);
    int findNodePosition(int nodeValue);
    int getTotalNodes();

    bool isPathMain(int currentNode,int toFind);
    bool isPath(int currentNode,int toFind);

    //Task 4
    std::string isConnected();

    //Task 5
    bool depthFirstMain(int currentNode, int toFind);
    bool depthFirst(int currentNode, int toFind);

    bool breadthFirstMain(int currentNode,int toFind);
    bool breadthFirst(int currentNode, int toFind);

    //Task 6
    int minD(std::vector<int> distance,std::vector<bool> selected);
    std::vector<int> dijkstra(int source);
    void print(std::vector<int> dist);


};

int graph::getTotalNodes()
{
    return graphVertices.size();
}

/**
 *This function takes @param data and creates a node
 *holding this specific data value.
 * It assigns a tree to the node.
 */

void graph::createNode(int data)
{
    auto newTree = new tree<int>;
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
void graph::addConnectionFromValue(int a,int b,int weight)
{
    int nodeOne = findNodePosition(a);
    int nodeTwo = findNodePosition(b);
    addConnection(nodeOne,nodeTwo,weight);
}
/**
 * Create @param amount nodes
 */
void graph::createMultipleNodes(int amount)
{
    for(int i = 0; i<amount; i++)
    {
       createNode();
    }
}


/**
 * Writes @param value to @param fileName
 *
 */
int write(int value,bool flag, const std::string fileName)
{
    std::ofstream file;
    file.open(fileName,std::ios::app);
    if(flag)
    {
        file << value;
    }
    else
    {
        file << value << "->";
    }
    file.close();

}

/**
 * clears the file @param fileName
 */
int clearFile(const std::string fileName)
{
    std::ofstream file;
    file.open(fileName);
    file.close();
}

/**
 * Finds if there is a path between current & final node
 * then writes path to a file
 * @returns bool if path found
 */
bool graph::isPathMain(int currentNode,int toFind)
{
    std::vector<int> adjacent;
    tree<int>* currentTree = graphEdges[currentNode];
    graphEdges[currentNode]->getValues(graphEdges[currentNode]->rootNode,adjacent);

    currentTree->visited = true;
    visited.emplace_back(currentNode);
    write(currentNode,flag,"pathFound.txt");

    if(std::find(adjacent.begin(), adjacent.end(), toFind) != adjacent.end())
    {
        flag = true;
        write(toFind,flag,"pathFound.txt");
    }

    for(int i = 0;i < adjacent.size();i++)
    {
        if(!graphEdges[adjacent[i]]->visited && !flag )
        {
            isPathMain(adjacent[i],toFind);
        }
    }

}

/**
 * Initialises isPath() with empty arrays runs then
 * @returns bool if path found
 */
bool graph::isPath(int currentNode, int toFind)
{
    clearFile("pathFound.txt");
    for(int i=0; i < graphEdges.size();i++)
    {
        graphEdges[i]->visited = false;
    }
    flag = false;
    visited.clear();
    isPathMain(currentNode,toFind);
    return flag;
}


/**
 * This function runs a depth first search from @param nodeA
 * @return true is node @param nodeB or @returns false
 */

bool graph::depthFirstMain(int currentNode, int toFind)
{
    std::vector<int> adjacent;
    tree<int>* currentTree = graphEdges[currentNode];
    graphEdges[currentNode]->getValues(graphEdges[currentNode]->rootNode,adjacent);

    currentTree->visited = true;
    visited.emplace_back(currentNode);
    if(currentNode == toFind)
    {
        flag = true;
        write(currentNode,flag,"depthFirstOut.txt");
        return true;
    }
    if(flag == true)
    {
        return true;
    }
    write(currentNode,flag,"depthFirstOut.txt");
    for(int i =0; i < adjacent.size(); i++)
    {
        if(!graphEdges[adjacent[i]]->visited)
        {
            depthFirstMain(adjacent[i],toFind);
        }
    }

}

/**
 * Initialises depthFirst() with empty arrays runs then
 * @returns bool if path found
 */
bool graph::depthFirst(int currentNode, int toFind)
{
    clearFile("depthFirstOut.txt");
    for(int i=0; i < graphEdges.size();i++)
    {
        graphEdges[i]->visited = false;
    }
    flag = false;
    visited.clear();
    depthFirstMain(currentNode,toFind);
    return !flag;
}

/**
 * Takes two parameters and a breadth first search to the second node.
 * @param currentNode This is the initial node and the node which is current within an iteration
 * @param toFind This is the node to find
 * @return The return value is a simple bool expression to the node found
 */
bool graph::breadthFirstMain(int currentNode,int toFind)
{

    graphEdges[currentNode]->visited = true;
    queue.push(currentNode);

    while(queue.empty() != true)
    {
        int current = queue.front();
        queue.pop();
        std::vector<int> adjacent;
        graphEdges[current]->getValues(graphEdges[current]->rootNode,adjacent);

        if(current == toFind)
        {
            flag = true;
            write(current,flag,"breadthFirstOut.txt");
            return true;
        }
        if(flag)
        {
            return true;
        }

        write(current,flag,"breadthFirstOut.txt");
        for(int i = 0; i < adjacent.size();i++)
        {
            if(!graphEdges[adjacent[i]]->visited)
            {
                graphEdges[adjacent[i]]->visited = true;
                queue.push(adjacent[i]);
            }

        }

    }
    return false;
}

/**
 * Initialises breadthFirst() with empty arrays runs then
 * @returns bool if path found
 */
bool graph::breadthFirst(int currentNode, int toFind)
{
    clearFile("breadthFirstOut.txt");
    for(int i=0; i < graphEdges.size();i++)
    {
        graphEdges[i]->visited = false;
    }
    flag = false;
    visited.clear();
    breadthFirstMain(currentNode,toFind);
    return !flag;
}

/**
 * Checks if the graph is connected, runs a depth first search from first
 * to last node. DFS puts the nodes into a visited array. If the array size
 * is = to the amount of nodes DFS visited all nodes and hence graph is connected.
 * @return yes if all nodes visited or no if it is not.
 */

std::string graph::isConnected(){
    depthFirst(0,graphEdges.size()+1);
    if(visited.size() != graphVertices.size())
    {
        return "no";
    }
    else
    {
        return "yes";
    }
}

/**
 * @param distance This is a vector of type int which stores
 * the distance from initial node to the node.
 * @param selected this is an equivelent to a 'visited' array
 * and stores all nodes that have been visited
 * @returns the minimum data value in @param distance
 */

int graph::minD(std::vector<int> distance,std::vector<bool> selected)
{
    int min_ret = 0;
    for(int x = 0; x < graphVertices.size();x++)
    {
        if(!selected[x] && distance[x] < max)
        {
            min_ret = x;
        }
    }
    return  min_ret;
}

/**
 * Prints out the distances from @param dist vector
 */
void graph::print(std::vector<int> dist)
{
    for (int i = 0; i < graphVertices.size(); i++)
        std::cout<< i << " -> " << dist[i] << std::endl;
}


/**
 * Takes an initial node @param source, then finds the smallest path to all
 * other nodes
 */

std::vector<int> graph::dijkstra(int source)
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
        graphEdges[minV]->getNodes(currentTree->rootNode,adjacent);

        for(int v =0;v < adjacent.size();v++)
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
    return dist;

}