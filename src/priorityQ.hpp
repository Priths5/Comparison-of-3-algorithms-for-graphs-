#ifndef PRIORITYQ_HPP
#define PRIORITYQ_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <climits>

class PlacePQ {
public:
    std::string name;
    std::unordered_map<PlacePQ*, int> neighbours;

    PlacePQ(const std::string& name);
    std::string getNamePQ() const;
    void addNeighbourPQ(PlacePQ* neighbour, int distance);
    const std::unordered_map<PlacePQ*, int>& getNeighboursPQ() const;
};

class Dijkstra {
public:
    static std::unordered_map<PlacePQ*, int> findShortestPathPQ(PlacePQ* start, PlacePQ* destination, std::unordered_map<PlacePQ*, PlacePQ*>& parent);
    static std::vector<PlacePQ*> reconstructPathPQ(PlacePQ* start, PlacePQ* destination, const std::unordered_map<PlacePQ*, PlacePQ*>& parent);
};

#endif
