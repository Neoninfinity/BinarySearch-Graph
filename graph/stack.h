//
// Created by rahul on 11/18/18.
//

#include <vector>
#include <string>
#include <iostream>
struct Stack
{
    std::vector<int> stackData;
    int top;
    int pop();
    void push(int data);
    bool isEmpty();
};

void Stack::push(int data)
{
    //Check if stack is full however since we will use a vector not necessary
    stackData.push_back(data);

}

int Stack::pop()
{
    //Check if stack is full however since we will use a vector not necessary
    int toReturn = stackData[stackData.back()];
    stackData.pop_back();
}

bool Stack::isEmpty()
{
    if(stackData.size() == 0)
    {
        return true;
    }
}

