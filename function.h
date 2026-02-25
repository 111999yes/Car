#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <fstream>
#include <algorithm>

void FileInput(int& numberOfNode, int& numberOfEdge, std::vector<std::set<int>>& graph){
    std::cout << "Enter the file name : ";
    std::string fileName;
    std::cin >> fileName;
    std::ifstream file;
    file.open(fileName, std::ios::in);
    if(file.fail())
        throw std::runtime_error("Error: Can not open file.");
    if(!(file >> numberOfNode >> numberOfEdge))
        throw std::runtime_error("Error: Invalid header format.");
    if(numberOfNode <= 0 || numberOfEdge < 0)
        throw std::invalid_argument("Error: Number of node and edge should both be postive integer");
    std::pair<int, int> edge;
    graph.assign(numberOfNode, std::set<int>());
    for(int i = 0; i < numberOfEdge; ++i){
        if(!(file >> edge.first >> edge.second))
            throw std::runtime_error("Error: Incomplete edge data.");
        if(edge.first >= numberOfNode || edge.first < 0 || edge.second >= numberOfNode || edge.second < 0)
            throw std::invalid_argument("Error: Node index out of bounds in file.");
        graph[edge.first].insert(edge.second);
        graph[edge.second].insert(edge.first);
    }
}

void Input(int& numberOfNode, int& numberOfEdge, std::vector<std::set<int>>& graph){
    std::cout << "Enter number of nodes and edges : ";
    while(!(std::cin >> numberOfNode >> numberOfEdge) || numberOfNode <= 0 || numberOfEdge < 0){
        std::cout << "Error: Invalid input. Please enter two postive integers : ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    graph.assign(numberOfNode, std::set<int> ());
    std::pair<int, int> edge;
    for(int i = 0; i < numberOfEdge; ++i){
        std::cin >> edge.first >> edge.second;
        if(edge.first >= numberOfNode || edge.first < 0 || edge.second >= numberOfNode || edge.second < 0){
            std::cout << "Error: Invalid edge index, please retry : ";
            --i;
            continue;
        }
        graph[edge.first].insert(edge.second);
        graph[edge.second].insert(edge.first);
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