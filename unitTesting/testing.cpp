#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <iostream>
#include <fstream>
#include "../graph/binarySearch.h"
#include "../graph/graph.h"



//Binary Tree testing
TEST_CASE( "Words can be manipulated correctly", "[treeString]" ) {

    tree<std::string> *tree1 = new tree<std::string>;
    insertText(tree1, "testFile.txt");

    SECTION("Words are inserted correctly") {
        REQUIRE(tree1->rootNode->key_value == "banana");
        REQUIRE(tree1->rootNode->left->key_value == "air");
        REQUIRE(tree1->rootNode->left->right->key_value == "apple");
        REQUIRE(tree1->rootNode->right->key_value == "cover");
        REQUIRE(tree1->rootNode->right->left->key_value == "catch");
    }

    SECTION("Words are searched correctly") {
        REQUIRE(!tree1->findWord("app.le"));
        //REQUIRE(tree1->findWord("aPPlE"));
        REQUIRE(tree1->findWord("Air"));
        REQUIRE(!tree1->findWord("hello"));
        REQUIRE(tree1->findWord("catch"));

    }

    SECTION("Words can be deleted correctly") {
        //Test if leaf from right can be deleted
        tree1->deleteNode("apple");
        REQUIRE(!tree1->findWord("apple"));

        //Test if leaf from left can be deleted
        tree1->deleteNode("catch");
        REQUIRE(!tree1->findWord("catch"));

        tree1->insert(tree1->rootNode,"catch");
        //Test if node with one child can be deleted
        tree1->deleteNode("Cover");
        REQUIRE(!tree1->findWord("cover"));
        REQUIRE(tree1->rootNode->right->key_value == "catch");

        //Test if node with two children can be deleted
        tree1->deleteNode(("Banana"));
        REQUIRE(!tree1->findWord(("banana")));
        std::cout<< tree1->rootNode->key_value;
        REQUIRE(tree1->rootNode->key_value == "catch");
    }

    SECTION("Duplicate words are not inserted")
    {
        tree1->insert(tree1->rootNode,"apple");
        node<std::string>* newNode = tree1->search(tree1->rootNode,"apple");
        bool check = (newNode->right == nullptr) && (newNode->left == nullptr);
        REQUIRE(check);
    }
}

//Graph testing

graph* initialise(){
    auto graph1 = new graph;
    int nodes = 7;
    graph1->createMultipleNodes(nodes);
    graph1->addConnection(0,5,9);
    graph1->addConnection(1,5,3);
    graph1->addConnection(1,4,4);
    graph1->addConnection(0,4,5);
    graph1->addConnection(0,2,12);
    graph1->addConnection(2,4,4);
    graph1->addConnection(4,3,6);
    graph1->addConnection(3,6,4);
    return graph1;
}

TEST_CASE( "Graph created correctly", "[graphTests]" ) {

    auto graph1 = initialise();
    int nodes = 7;
    REQUIRE(graph1->getTotalNodes() == nodes);

}

TEST_CASE( "isPath is working correctly", "[isPathTests]" )
{

    auto graph1 = initialise();
    int nodes = 7;

    SECTION("Test for paths between the nodes")
    {
        REQUIRE(graph1->isPath(0,3));
        REQUIRE(graph1->isPath(0,6));
        REQUIRE(graph1->isPath(5,2));
        //Check for no path
        REQUIRE(!(graph1->isPath(4,8)));
    }

}

TEST_CASE("is Connected working correctly")
{
    auto graph1 = initialise();
    int nodes = 7;

    auto unConnected = new graph;
    int nodes2 = 4;
    unConnected->createMultipleNodes(nodes2);
    unConnected->addConnection(0,1,9);
    unConnected->addConnection(0,2,9);

    SECTION("Can check for connected graph and unconnected after addition")
    {
        REQUIRE(graph1->isConnected() == "yes");
        graph1->createNode();
        REQUIRE(graph1->isConnected() == "no");

    }
    SECTION("Can check for connected graph and unconnected after addition")
    {
        REQUIRE(unConnected->isConnected() == "no");
        unConnected->addConnection(0,3,9);
        REQUIRE(unConnected->isConnected() == "yes");

    }

}

std::string getFileString(std::string fileName)
{
    std::ifstream file;
    std::string line;
    std::string newString;
    file.open(fileName);

    while (getline (file, line)) {
        newString.append(line);
    }

    file.close();

    return newString;
}


TEST_CASE("DFS giving right values")
{
    auto dfsGraph = initialise();

    dfsGraph->depthFirst(0,6);
    std::string output = getFileString("depthFirstOut.txt");
    REQUIRE(output == "0->2->4->1->5->3->6");


    dfsGraph->depthFirst(5,2);
    std::string output2 = getFileString("depthFirstOut.txt");
    REQUIRE(output2 == "5->0->2");

}

TEST_CASE("BFS giving right values")
{
    auto bfsGraph = initialise();

    bfsGraph->breadthFirst(0,6);
    std::string output = getFileString("breadthFirstOut.txt");
    REQUIRE(output == "0->2->4->5->1->3->6");


    bfsGraph->breadthFirst(5,2);
    std::string output2 = getFileString("breadthFirstOut.txt");
    REQUIRE(output2 == "5->0->1->2");

}

TEST_CASE("dijkstra algorithm functioning correct")
{
    auto dGraph = initialise();
    std::vector<int> distance = dGraph->dijkstra(0);
    REQUIRE(distance[6] == 15);
    REQUIRE(distance[5] == 9);
    REQUIRE(distance[4] == 5);
    REQUIRE(distance[3] == 11);
    REQUIRE(distance[2] == 9);
    REQUIRE(distance[1] == 9);
    REQUIRE(distance[0] == 0);

}