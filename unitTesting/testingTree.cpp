/**
    210CT Coursework 1
    testing.cpp
    Purpose: test the binary tree & graph functions
    -Test tasks stated on assignment brief

    @author Rahul Prashar
    @version 1.1 21/11/18
*/


#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <iostream>
#include <fstream>
#include "../main/binarySearch.h"



//Binary Tree testing
TEST_CASE( "Words can be manipulated correctly", "[treeString]" ) {

    tree<std::string> *tree1 = new tree<std::string>;
    tree1->insertText("testFile.txt");

    SECTION("Words are inserted correctly") {
        REQUIRE(tree1->rootNode->key_data == "banana");
        REQUIRE(tree1->rootNode->left->key_data == "air");
        REQUIRE(tree1->rootNode->left->right->key_data == "apple");
        REQUIRE(tree1->rootNode->right->key_data == "cover");
        REQUIRE(tree1->rootNode->right->left->key_data == "catch");
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
        REQUIRE(tree1->rootNode->right->key_data == "catch");

        //Test if node with two children can be deleted
        tree1->deleteNode(("Banana"));
        REQUIRE(!tree1->findWord(("banana")));
        std::cout<< tree1->rootNode->key_data;
        REQUIRE(tree1->rootNode->key_data == "catch");
    }

    SECTION("Duplicate words are not inserted")
    {
        tree1->insert(tree1->rootNode,"apple");
        node<std::string>* newNode = tree1->search(tree1->rootNode,"apple");
        bool check = (newNode->right == nullptr) && (newNode->left == nullptr);
        REQUIRE(check);
    }

    SECTION("Check if Pre-Order Outputs correctly")
    {
        auto tree1 = new tree<std::string>;
        tree1->insertText("testFile.txt");
        std::vector<std::string> preOrderVec = tree1->pre_order(tree1->rootNode);
        std::vector<std::string> correct = {"banana","air","apple","cover","catch"};
        REQUIRE(preOrderVec == correct);
    }
}
