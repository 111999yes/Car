#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <cstring>
#include <sstream>

void ParseEdge(const std::string& input, std::vector<std::set<int>>& graph){
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
        int to = 0;
        try{
            if(pos == std::string::npos){
                to = std::stoi(back.substr(start));
                graph[from].insert(to);
                graph[to].insert(from);
                break;
            }
        }
        catch(const std::exception& e){
            break;
        }
        to = std::stoi(back.substr(start, pos - start));
        graph[from].insert(to);
        graph[to].insert(from);

        start = pos + 1;
    }
}