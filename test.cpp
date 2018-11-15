//
// Created by rahul on 11/5/18.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

int main(){
    std::string line;
    std::ifstream paragraph;
    paragraph.open("text.txt");
    while (getline(paragraph, line))
    {
        std::cout << line;
    }


}