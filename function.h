#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <limits>
#include <fstream>
#include <algorithm>

#include "parser.h"

void FileInput(int& numberOfNode, std::vector<Node>& graph){
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
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    graph.assign(numberOfNode, Node());
    while(std::getline(file, input)){
        if(input == "Q" || input == "q") break;
        ParseEdge(input, graph);
    }
}

void Input(int& numberOfNode, std::vector<Node>& graph){
    std::cout << "Enter number of nodes : ";
    while(!(std::cin >> numberOfNode) || numberOfNode <= 0){
        std::cout << "Error: Invalid input. Please enter one postive integers : ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    graph.assign(numberOfNode, Node());
    std::string input;
    std::cout << "Please Enter edges (enter \"q\" to exit): \n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while(true){
        std::getline(std::cin, input);
        if(input == "Q" || input == "q") break;
        ParseEdge(input, graph);
    }
}

void BFS(const std::vector<Node>& graph, std::vector<int>& distance, std::vector<int>& lastPoint, int startPoint){
    distance[startPoint] = 0;
    std::queue<int> q;
    q.push(startPoint);

    int curPoint;

    while(!q.empty()){
        curPoint = q.front();
        q.pop();

        for(auto adjacentPoint : graph[curPoint].adjacentEdge){
            if(distance[adjacentPoint.GetTerminal()] == -1){
                q.push(adjacentPoint.GetTerminal());
                distance[adjacentPoint.GetTerminal()] = distance[curPoint] + 1;
                lastPoint[adjacentPoint.GetTerminal()] = curPoint;
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