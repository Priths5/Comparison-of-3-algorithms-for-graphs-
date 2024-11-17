#ifndef BELLMENFORD_HPP
#define BELLMENFORD_HPP
#include "path.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <utility>
#include <stdexcept>
#include <iostream>
using namespace std;
// std::vector<Place*> reconstructPathBellmanFord(Place* start, Place* destination, const std::unordered_map<Place*, Place*>& parent);
unordered_map<Place*, int> bellmanFord(Place* start, Place* destination, std::unordered_map<Place*, Place*>& parent, const std::unordered_map<Place*, std::vector<std::pair<Place*, int>>>& edgeMap);
#endif
