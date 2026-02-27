#pragma once
#include <vector>
#include <set>

#include "enum.h"

class Edge{
public:

    Edge() {}
    Edge(int _end, Facing _relativePos) : terminal(_end), relativePosition(_relativePos) {}

    bool operator<(const Edge& other) const {
        if(terminal != other.terminal) return terminal < other.terminal;
        return relativePosition < other.relativePosition;
    }

    int GetTerminal() const {
        return terminal;
    }

    Facing GetDirection() const {
        return relativePosition;
    }
    
    
private:
    int terminal;
    Facing relativePosition;
};

class Node{
public:

    Node() {}

    void Append(const Edge& e){
        adjacentEdge.push_back(e);
    }

private:
    vector<Edge> adjacentEdge;
};