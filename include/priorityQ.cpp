#include "../src/priorityQ.hpp"
using namespace std;
PlacePQ::PlacePQ(const string& name) : name(name) {}

string PlacePQ::getNamePQ() const {
    return name;
}

void PlacePQ::addNeighbourPQ(PlacePQ* neighbour, int distance) {
    neighbours[neighbour] = distance;
}

const unordered_map<PlacePQ*, int>& PlacePQ::getNeighboursPQ() const {
    return neighbours;
}

unordered_map<PlacePQ*, int> Dijkstra::findShortestPathPQ(PlacePQ* start, PlacePQ* destination, unordered_map<PlacePQ*, PlacePQ*>& parent) {
    unordered_map<PlacePQ*, int> distances;
    auto cmp = [](pair<int, PlacePQ*> a, pair<int, PlacePQ*> b) { return a.first > b.first; };
    priority_queue<pair<int, PlacePQ*>, vector<pair<int, PlacePQ*>>, decltype(cmp)> pq(cmp);

    distances[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [currentDistance, currentPlacePQ] = pq.top();
        pq.pop();

        if (currentPlacePQ == destination) break;

        for (const auto& [neighbor, distance] : currentPlacePQ->getNeighboursPQ()) {
            int newDistance = currentDistance + distance;
            if (distances.find(neighbor) == distances.end() || newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance;
                parent[neighbor] = currentPlacePQ;
                pq.push({newDistance, neighbor});
            }
        }
    }
    return distances;
}

vector<PlacePQ*> Dijkstra::reconstructPathPQ(PlacePQ* start, PlacePQ* destination, const unordered_map<PlacePQ*, PlacePQ*>& parent) {
    vector<PlacePQ*> path;
    PlacePQ* current = destination;
    while (current != start) {
        path.insert(path.begin(), current);
        current = parent.at(current);
    }
    path.insert(path.begin(), start);
    return path;
}
