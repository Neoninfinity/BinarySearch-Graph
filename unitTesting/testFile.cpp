//
// Created by rahul on 11/27/18.
//


#include "../main/binarySearch.h"

int main()
{
    auto graph1 = new tree<std::string>;
    graph1->insertText("testFile.txt");
    std::vector<std::string> preOrderVec = graph1->pre_order(graph1->rootNode);
    std::vector<std::string> correct = {"banana","air","apple","cover","catch"};
    bool value = (preOrderVec == correct);

    std::string test = preOrderVec[0];
}