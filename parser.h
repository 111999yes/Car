#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <cstring>
#include <sstream>

#include "enum.h"
#include "edge.h"

void ParseEdge(const std::string&, std::vector<Node>&);
void ParseScore(std::vector<int>&, std::string&);
std::pair<int, Facing> ParseSingleEdge(std::string);
Facing ParseStringToFacing(std::string);

void ParseEdge(const std::string& input, std::vector<Node>& graph){
    size_t idx = input.find(':');
    if(idx == std::string::npos)
        throw std::invalid_argument("Error: Invalid input format");
    std::string front = input.substr(0, idx);
    std::string back = input.substr(idx + 1);

    int from = std::stoi(front);
    if(from >= graph.size())
        throw std::out_of_range("Error: Invalid start point of the edge");
    
    int start = 0;
    while(true){
        int pos = back.find(',', start);
        std::pair<int, Facing> edgeData;
        int to = 0;
        if(pos == std::string::npos){
            try{
                edgeData = ParseSingleEdge(back.substr(start));
                to = edgeData.first;
                if(to >= graph.size())
                    throw std::out_of_range("Error: Invalid end point of the edge");
                Edge a(to, edgeData.second);
                graph[from].Append(a);
                Edge ac(from, GetOppositeDirection(edgeData.second));
                graph[to].Append(ac);
                break;
            }
            catch(const std::invalid_argument& e){
                break;
            }
        }
        edgeData = ParseSingleEdge(back.substr(start, pos - start));
        to = edgeData.first;
        if(to >= graph.size())
            throw std::out_of_range("Error: Invalid end point of the edge");
        Edge a(to, edgeData.second);
        graph[from].Append(a);
        Edge ac(from, GetOppositeDirection(edgeData.second));
        graph[to].Append(ac);

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

std::pair<int, Facing> ParseSingleEdge(std::string s){
    std::pair<int, Facing> result;
    size_t idx = s.find('(');
    if(idx == std::string::npos)
            throw std::invalid_argument("Error: Invalid input format");
    result.first = std::stoi(s.substr(0, idx));
    s.pop_back();
    Facing relPos = ParseStringToFacing(s.substr(idx + 1));
    if(relPos == Facing::UNDEFINED)
        throw std::invalid_argument("Error: Undifined direction");
    result.second = relPos;
    return result;
}
