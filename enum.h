#pragma once

enum class Facing{
    NORTH,
    EAST,
    SOUTH,
    WEST,
    UNDEFINED
};

Facing GetOppositeDirection(const Facing& f){
    if(f == Facing::NORTH) return Facing::SOUTH;
    if(f == Facing::SOUTH) return Facing::NORTH;
    if(f == Facing::EAST) return Facing::WEST;
    if(f == Facing::WEST) return Facing::EAST;
    return Facing::UNDEFINED;
} 