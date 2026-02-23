#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

int main(){

//=======================INPUT=======================
    int numberOfNode;
    int numberOfEdge;
    cin >> numberOfNode >> numberOfEdge;
    vector<vector<int>> node;
    for(int i = 0; i < numberOfNode; ++i) node.push_back({});
    for(int i = 0; i < numberOfEdge; ++i){
        pair<int, int> edge;
        cin >> edge.first >> edge.second;
        node[edge.first].push_back(edge.second);
        node[edge.second].push_back(edge.first);
    }
//===================================================


//=======================INIT=======================
    int startPoint;
    cin >> startPoint;
    vector<int> distance(numberOfNode, INT_MAX);
    vector<int> lastPoint(numberOfNode, -1);
    queue<int> q;

    distance[startPoint] = 0;
    q.push(startPoint);
//==================================================

//=======================BFS=======================
    while(!q.empty()){
        int curPoint = q.front();
        q.pop();
        for(int i = 0; i < node[curPoint].size(); ++i){
            if(distance[node[curPoint][i]] == INT_MAX){
                q.push(node[curPoint][i]);
                distance[node[curPoint][i]] = distance[curPoint] + 1;
                lastPoint[node[curPoint][i]] = curPoint;
            }
        }
    }

//=================================================

    cout << "節點\t距離\t前驅節點" << endl;
    for(int i = 0; i < numberOfNode; ++i){
        cout << i << "\t";
        if(distance[i] == INT_MAX) cout << "不可達";
        else cout << distance[i];
        cout << "\t" << lastPoint[i] << endl;
    }

    return 0;
}