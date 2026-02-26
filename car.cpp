#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <fstream>
#include <limits>
using namespace std;

#include "function.h"

int main(){

//=======================INPUT=======================
    bool isFile = false;
    string input;
    cout << "File IO or not [y/n] : ";
    cin >> input;
    if(input == "y" || input == "Y") isFile = true;

    int numberOfNode = 0;
    vector<set<int>> graph;
    
    if(!isFile){
        while(true){
            try{
                Input(numberOfNode, graph);
                break;
            }
            catch(const runtime_error& e){
                cout << e.what() << ", please retry\n";
            }
        }
    }
    else{
        while(true){
            try{
                FileInput(numberOfNode, graph);
                break;
            }
            catch(const exception& e){
                cout << e.what() << ", please retry\n";
            }
        }
    }
//===================================================


//=======================INIT=======================
    int startPoint, endPoint;
    cout << "Enter start and end point: ";
    while(true){
        try{
            if(!(cin >> startPoint >> endPoint)){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Error : Invalid input");
            }
            if(startPoint >= numberOfNode || startPoint < 0 || endPoint >= numberOfNode || endPoint < 0)
                throw invalid_argument("Error : Invalid index of start point or end point");
            break;
        }
        catch(const exception& e){
            cout << e.what() << ", please retry : ";
        }
    }
    vector<int> distance(numberOfNode, -1);
    vector<int> lastPoint(numberOfNode, -1);
    
//==================================================

//=======================SCORE=======================
    vector<int> score(numberOfNode, 0);
    string inputScore;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Enter the score of each node (default score = 0 and enter \"q\" to exit): \n";
    while(true){
        getline(cin, inputScore);
        if(inputScore == "q" || inputScore == "Q") break;
        else{
            try{
                ParseScore(score, inputScore);
            }
            catch(const exception& e){
                cout << e.what() << ", please retry : ";
            }
        }
    }
//===================================================

//=======================BFS=======================
    BFS(graph, distance, lastPoint, startPoint);
//=================================================

//=======================ROUTE=======================
    vector<int> route;
    FindRoute(route, distance, lastPoint, endPoint);
//=======================ROUTE=======================

//=================================================

    cout << "節點\t距離\t前驅節點" << endl;
    for(int i = 0; i < numberOfNode; ++i){
        cout << i << "\t";
        if(distance[i] == -1) cout << "不可達";
        else cout << distance[i];
        cout << "\t" << lastPoint[i] << endl;
    }

    cout << "\nroute : \n";
    if(distance[endPoint] == -1) cout << "\tno possible route\n";
    else{
        for(size_t i = 0; i < route.size(); ++i){
            cout << route[i] << ((i == (route.size() - 1)) ? "\n" : " -> ");
        }
    }

    cout << "\nscore : \n";
    for(int i = 0; i < score.size(); ++i){
        cout << i << " : " << score[i] << endl;
    }

    return 0;
}