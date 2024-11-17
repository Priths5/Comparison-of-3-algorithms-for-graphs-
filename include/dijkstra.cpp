#include "../src/dijkstra.hpp"
#include <climits>
#include <set>

unordered_map<Place*, int> findShortestPath(Place* start, Place* destination, unordered_map<Place*, Place*>& parent) {
    unordered_map<Place*, int> distances;
    set<Place*> visited;

    for (auto neighbor : start->neighbours) {
        distances[neighbor.first] = INT_MAX;
    }
    distances[start] = 0;

    while (visited.find(destination) == visited.end()) {
        Place* closestPlace = nullptr;
        int closestDistance = INT_MAX;

        for (auto entry : distances) {
            if (visited.find(entry.first) == visited.end() && entry.second < closestDistance) {
                closestPlace = entry.first;
                closestDistance = entry.second;
            }
        }

        if (closestPlace == nullptr) {
            break;
        }

        visited.insert(closestPlace);

        for (auto neighbor : closestPlace->neighbours) {
            int newDistance = distances[closestPlace] + neighbor.second;
            if (distances.count(neighbor.first) == 0 || distances[neighbor.first] > newDistance) {
                distances[neighbor.first] = newDistance;
                parent[neighbor.first] = closestPlace;
            }
        }
    }

    return distances;
}

vector<Place*> reconstructPath(Place* start, Place* destination, const unordered_map<Place*, Place*>& parent) {
    vector<Place*> path;
    Place* current = destination;

    while (current != start) {
        path.insert(path.begin(), current);
        current = parent.at(current);
    }

    path.insert(path.begin(), start);
    return path;
}
