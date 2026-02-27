#pragma once
#include <vector>
#include <set>

#include "enum.h"

class Edge{
public:

    Edge() {}
    Edge(int _end, Facing _relativePos) : end(_end), relativePosition(_relativePos) {}

    bool operator<(const Edge& other) const {
        if(end != other.end) return end < other.end;
        return relativePosition < other.relativePosition;
    }
    
    int end;
    Facing relativePosition;
};