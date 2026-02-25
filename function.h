#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <fstream>
#include <algorithm>
using namespace std;

void FileInput(int& numberOfNode, int& numberOfEdge, vector<vector<int>>& graph){
    cout << "Enter the file name : ";
    string fileName;
    cin >> fileName;
    ifstream file;
    file.open(fileName, ios::in);
    if(file.fail())
        throw runtime_error("Error: Can not open file.");
    if(!(file >> numberOfNode >> numberOfEdge))
        throw runtime_error("Error: Invalid header format.");
    if(numberOfNode <= 0 || numberOfEdge < 0)
        throw invalid_argument("Error: Number of node and edge should both be postive integer");
    pair<int, int> edge;
    graph.assign(numberOfNode, vector<int>());
    for(int i = 0; i < numberOfEdge; ++i){
        if(!(file >> edge.first >> edge.second))
            throw runtime_error("Error: Incomplete edge data.");
        if(edge.first >= numberOfNode || edge.first < 0 || edge.second >= numberOfNode || edge.second < 0)
            throw invalid_argument("Error: Node index out of bounds in file.");
        graph[edge.first].push_back(edge.second);
        graph[edge.second].push_back(edge.first);
    }
}

void Input(int& numberOfNode, int& numberOfEdge, vector<vector<int>>& graph){
    cout << "Enter number of nodes and edges : ";
    while(!(cin >> numberOfNode >> numberOfEdge) || numberOfNode <= 0 || numberOfEdge < 0){
        cout << "Error: Invalid input. Please enter two postive integers : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    graph.assign(numberOfNode, vector<int> ());
    pair<int, int> edge;
    for(int i = 0; i < numberOfEdge; ++i){
        cin >> edge.first >> edge.second;
        if(edge.first >= numberOfNode || edge.first < 0 || edge.second >= numberOfNode || edge.second < 0){
            cout << "Error: Invalid edge index, please retry : ";
            --i;
            continue;
        }
        graph[edge.first].push_back(edge.second);
        graph[edge.second].push_back(edge.first);
    }
}

void BFS(const vector<vector<int>>& graph, vector<int>& distance, vector<int>& lastPoint, int startPoint){
    distance[startPoint] = 0;
    queue<int> q;
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

void FindRoute(vector<int>& route, const vector<int>& distance, const vector<int>& lastPoint, int endPoint){
    int curPoint = endPoint;
    if(distance[endPoint] == -1) return;
    while(curPoint != -1){
        route.push_back(curPoint);
        curPoint = lastPoint[curPoint];
    }
    reverse(route.begin(), route.end());
}