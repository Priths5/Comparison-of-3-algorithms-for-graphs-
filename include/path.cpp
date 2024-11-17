#include "../src/path.hpp"
#include<iostream>

Place::Place(std::string name) : name(name) {}

std::string Place::getName() const {
    return name;
}

void Place::addNeighbour(Place* neighbour, int distance) {
    neighbours[neighbour] = distance;
}

const std::unordered_map<Place*, int>& Place::getNeighbours() const {
    return neighbours;
}


