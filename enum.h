#pragma once

enum class Facing{
    NORTH,
    EAST,
    SOUTH,
    WEST,
    UNDEFINED
};

void Upper(std::string& s){
    for(auto &i : s){
        if(i >= 'a' && i <= 'z'){
            i = i - 'a' + 'A';
        }
    }
}

Facing GetOppositeDirection(const Facing& f){
    if(f == Facing::NORTH) return Facing::SOUTH;
    if(f == Facing::SOUTH) return Facing::NORTH;
    if(f == Facing::EAST) return Facing::WEST;
    if(f == Facing::WEST) return Facing::EAST;
    return Facing::UNDEFINED;
}

Facing ParseStringToFacing(std::string s){
    Upper(s);
    if(s == "NORTH") return Facing::NORTH;
    if(s == "EAST") return Facing::EAST;
    if(s == "SOUTH") return Facing::SOUTH;
    if(s == "WEST") return Facing::WEST;
    return Facing::UNDEFINED;
}

std::string ParseFacingToString(const Facing& f){
    if(f == Facing::NORTH) return "North";
    if(f == Facing::EAST) return "East";
    if(f == Facing::SOUTH) return "South";
    if(f == Facing::WEST) return "West";
    return "UNDEFINED";
}
