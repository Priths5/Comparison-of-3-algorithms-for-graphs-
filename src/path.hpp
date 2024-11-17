#ifndef PATH_HPP
#define PATH_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Place {
    public:
        string name;
        unordered_map<Place*, int> neighbours;
        Place(string name);
        string getName() const;
        void addNeighbour(Place* neighbour, int distance);
        const unordered_map<Place*, int>& getNeighbours() const;
        int heuristicTo(const Place* destination) const;
        
};
struct PathResult {
            vector<Place*> path;
            long long timeTaken;
        };
#endif
