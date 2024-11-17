#include "../src/path.hpp"
#include "../src/bellmenford.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>
#include<climits>
#include<chrono>
using namespace std;
vector<Place*> reconstructPathBellmanFord(Place* start, Place* destination, unordered_map<Place*, Place*>& parent) {
    vector<Place*> path;
    Place* current = destination;

    while (current != start) {
        path.insert(path.begin(), current);
        if (parent.find(current) == parent.end()) {
            throw runtime_error("No path exists from start to destination");
        }
        current = parent.at(current);
    }

    path.insert(path.begin(), start);
    return path;
}
int main() {
    int numPlaces;
    // cout<<"Enter number of places\n";
    cin >> numPlaces;
    unordered_map<string, Place*> places;
    unordered_map<Place*, vector<pair<Place*, int>>> graph;
    // cout << "Enter the name of place in one row.\n";
    for (int i = 0; i < numPlaces; ++i) {
        string placeName;
        cin >> placeName;
        Place* place = new Place(placeName);
        places[placeName] = place;
        graph[place] = {};
    }

    int f;
    // cout << "Enter edges in format: 1 <from> <to> <distance>. Enter -1 to stop.\n";
    while (true) {
        cin >> f;
        if (f == -1) break;

        string from, to;
        int distance;
        cin >> from >> to >> distance;
        if (places.find(from) != places.end() && places.find(to) != places.end()) {
            places[from]->addNeighbour(places[to], distance);
            graph[places[from]].push_back({places[to], distance});
        } else {
            // cerr << "Error: Undefined place(s) in connection (" << from << " -> " << to << ")\n";
            return 1;
        }
    }

    string startName, destinationName;
    // cout << "Enter starting and destination places:\n";
    cin >> startName >> destinationName;

    if (places.find(startName) == places.end() || places.find(destinationName) == places.end()) {
        // cerr << "Error: Start or destination place not defined.\n";
        return 1;
    }

    Place* startingPoint = places[startName];
    Place* endPoint = places[destinationName];
    unordered_map<Place*, Place*> travelHistory;

    try {
        auto start=chrono::high_resolution_clock::now();
        unordered_map<Place*, int> travelDistances = bellmanFord(startingPoint, endPoint, travelHistory, graph);
        auto stop=chrono::high_resolution_clock::now();
        cout << "Bellman-Ford Algorithm\n";
        // cout<<"1 "<<travelDistances.count(endPoint)<<endl;
        if (travelDistances.count(endPoint) > 0 && travelDistances[endPoint] != INT_MAX) {
        cout << "Shortest distance to destination: " << travelDistances[endPoint] << endl;
        auto start1 = chrono::high_resolution_clock::now();
        vector<Place*> travelRoute = reconstructPathBellmanFord(startingPoint, endPoint, travelHistory);
        auto stop1 = chrono::high_resolution_clock::now();
        cout << "Shortest Path:\n";
        for (Place* location : travelRoute) {
            cout << location->getName() << " -> ";
        }
        cout << "Destination" << endl;
        auto dur = chrono::duration_cast<chrono::microseconds>((stop - start) + (stop1 - start1));
        cout << "Time taken: " << dur.count() << " microseconds\n";
    } else {
        cout << "No path found to destination.\n";
    }

    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }

    for (auto& entry : places) {
        delete entry.second;
    }
cout<<"\n-------------------------\n";
    return 0;
}
