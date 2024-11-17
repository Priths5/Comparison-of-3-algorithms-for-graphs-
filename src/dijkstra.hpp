#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "path.hpp"
#include <unordered_map>
#include <vector>

unordered_map<Place*, int> findShortestPath(Place* start, Place* destination, unordered_map<Place*, Place*>& parent);
vector<Place*> reconstructPath(Place* start, Place* destination, const unordered_map<Place*, Place*>& parent);

#endif
