#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include "objects/ParseLine_vertex.h"

ParseLine_vertex::ParseLine_vertex(){
    
}

void ParseLine_vertex::parse(std::string thisLine){
    std::vector<std::string> tokens;
    std::stringstream check1(thisLine);
    std::string intermediate;
    
    // Locate next space and add token to characters before space
    while(std::getline(check1, intermediate, ' ')){
        tokens.push_back(intermediate);
    }

    // assign tokens to private structure up to 3 elements
    if (tokens.size()>=3){
        this->x = std::stof(tokens[0]);
        this->y = std::stof(tokens[1]);
        this->z = std::stof(tokens[2]);
    }

    // assign 4th element if it exists
    if (tokens.size()==4){
        this->w = std::stof(tokens[3]);
    }
    
}

float ParseLine_vertex::getX(){
    return this->x;
}

float ParseLine_vertex::getY(){
    return this->y;
}

float ParseLine_vertex::getZ(){
    return this->z;
}

float ParseLine_vertex::getW(){
    return this->w;
}