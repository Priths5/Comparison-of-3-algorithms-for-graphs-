#include "../src/path.hpp"
#include "../src/bellmenford.hpp"
#include <climits>
#include <unordered_map>
#include <vector>


unordered_map<Place*, int> bellmanFord(Place* start, Place* destination, unordered_map<Place*, Place*>& parent, const unordered_map<Place*, vector<pair<Place*, int>>>& graph) {
    unordered_map<Place*, int> distances;
    for (const auto& entry : graph) {
        distances[entry.first] = INT_MAX;
    }
    distances[start] = 0;

    int numPlaces = graph.size();

    for (int i = 0; i < numPlaces - 1; ++i) {
        bool updated = false;

        for (const auto& entry : graph) {
            Place* u = entry.first;
            int distanceU = distances[u];

            if (distanceU == INT_MAX) continue;

            for (const auto& neighbor : entry.second) {
                Place* v = neighbor.first;
                int weightUV = neighbor.second;

                if (distanceU + weightUV < distances[v]) {
                    distances[v] = distanceU + weightUV;
                    parent[v] = u;
                    updated = true;
                }
            }
        }

        if (!updated) break;
    }

    for (const auto& entry : graph) {
        Place* u = entry.first;
        int distanceU = distances[u];

        if (distanceU == INT_MAX) continue;

        for (const auto& neighbor : entry.second) {
            Place* v = neighbor.first;
            int weightUV = neighbor.second;

            if (distanceU + weightUV < distances[v]) {
                throw runtime_error("Graph contains a negative-weight cycle");
            }
        }
    }

    return distances;
}

// vector<Place*> reconstructPathBellmanFord(Place* start, Place* destination, unordered_map<Place*, Place*>& parent) {
//     vector<Place*> path;
//     Place* current = destination;

//     while (current != start) {
//         path.insert(path.begin(), current);
//         if (parent.find(current) == parent.end()) {
//             throw runtime_error("No path exists from start to destination");
//         }
//         current = parent.at(current);
//     }

//     path.insert(path.begin(), start);
//     return path;
// }