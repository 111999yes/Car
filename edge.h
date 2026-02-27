#pragma once
#include <vector>
#include <set>

#include "enum.h"

class Edge{
public:

    Edge() {}
    Edge(int _end, Facing _relativePos) : end(_end), relativePosition(_relativePos) {}
    
    int end;
    Facing relativePosition;
};