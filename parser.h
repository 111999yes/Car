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
        throw std::out_of_range("Error: Invalid start point of the edge");
    
    int start = 0;
    while(true){
        int pos = back.find(',', start);
        int to = 0;
        if(pos == std::string::npos){
            try{
                to = std::stoi(back.substr(start));
                if(to >= graph.size())
                    throw std::out_of_range("Error: Invalid end point of the edge");
                graph[from].insert(to);
                graph[to].insert(from);
                break;
            }
            catch(const invalid_argument& e){
                break;
            }
        }
        to = std::stoi(back.substr(start, pos - start));
        if(to >= graph.size())
            throw std::out_of_range("Error: Invalid end point of the edge");
        graph[from].insert(to);
        graph[to].insert(from);

        start = pos + 1;
    }
}

void ParseScore(std::vector<int>& score, std::string& input){
    size_t idx = input.find(':');
    if(idx == std::string::npos)
        throw std::invalid_argument("Error: Invalid input format");
    std::string node = input.substr(0, idx);
    std::string point = input.substr(idx + 1);
    if(std::stoi(node) >= score.size() || std::stoi(node) < 0)
        throw std::out_of_range("Error: Invalid index of node");
    score[std::stoi(node)] = std::stoi(point);
}