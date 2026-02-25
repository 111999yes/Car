#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>

void ParseEdge(std::string input, std::vector<std::vector<int>>& graph){
    size_t idx = input.find(':');
    if(idx == std::string::npos){
        throw std::invalid_argument("Error: Invalid input format");
    }
    std::string front = input.substr(0, idx);
    std::string back = input.substr(idx + 1);

    int from = std::stoi(front);
    if(from >= graph.size())
        throw std::invalid_argument("Error: Invalid start point of the edge");
    
    int start = 0;
    while(true){
        int pos = back.find(',', start);
        if(pos == std::string::npos){
            graph[from].push_back(std::stoi(back.substr(start)));
            break;
        }
        graph[from].push_back(std::stoi(back.substr(start, pos - start)));
        start = pos + 1;
    }
}