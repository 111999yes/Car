#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <fstream>
#include <algorithm>

#include "parser.h"

void FileInput(int& numberOfNode, std::vector<std::set<int>>& graph){
    std::cout << "Enter the file name : ";
    std::string fileName;
    std::cin >> fileName;
    std::ifstream file;
    file.open(fileName, std::ios::in);
    if(file.fail())
        throw std::runtime_error("Error: Can not open file.");
    if(!(file >> numberOfNode))
        throw std::runtime_error("Error: Invalid header format.");
    if(numberOfNode <= 0)
        throw std::invalid_argument("Error: Number of node and edge should both be postive integer");
    std::string input;
    graph.assign(numberOfNode, std::set<int>());
    for(int i = 0; i < numberOfNode; ++i){
        if(!(file >> input))
            throw std::runtime_error("Error: Incomplete edge data.");
        ParseEdge(input, graph);
    }
}

void Input(int& numberOfNode, std::vector<std::set<int>>& graph){
    std::cout << "Enter number of nodes : ";
    while(!(std::cin >> numberOfNode) || numberOfNode <= 0){
        std::cout << "Error: Invalid input. Please enter one postive integers : ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    graph.assign(numberOfNode, std::set<int> ());
    std::string input;
    for(int i = 0; i < numberOfNode; ++i){
        if(!(std::cin >> input))
            throw std::runtime_error("Error: Invalid input");
        ParseEdge(input, graph);
    }
}

void BFS(const std::vector<std::set<int>>& graph, std::vector<int>& distance, std::vector<int>& lastPoint, int startPoint){
    distance[startPoint] = 0;
    std::queue<int> q;
    q.push(startPoint);

    int curPoint;

    while(!q.empty()){
        curPoint = q.front();
        q.pop();

        for(int adjacentPoint : graph[curPoint]){
            if(distance[adjacentPoint] == -1){
                q.push(adjacentPoint);
                distance[adjacentPoint] = distance[curPoint] + 1;
                lastPoint[adjacentPoint] = curPoint;
            }
        }
    }
}

void FindRoute(std::vector<int>& route, const std::vector<int>& distance, const std::vector<int>& lastPoint, int endPoint){
    int curPoint = endPoint;
    if(distance[endPoint] == -1) return;
    while(curPoint != -1){
        route.push_back(curPoint);
        curPoint = lastPoint[curPoint];
    }
    reverse(route.begin(), route.end());
}