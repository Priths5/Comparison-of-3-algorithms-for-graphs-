#include "../src/priorityQ.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

int main() {
    int numPlaces;
    // cout << "Enter number of places:\n";
    cin >> numPlaces;
    unordered_map<string, PlacePQ*> places;
    for (int i = 0; i < numPlaces; ++i) {
        string placeName;
        // cout << "Enter the name of place " << i + 1 << ":\n";
        cin >> placeName;
        places[placeName] = new PlacePQ(placeName);
    }
    int f = 1;
    // cout << "Enter edges in format: 1 <from> <to> <distance>. Enter -1 to stop.\n";
    while (true) {
        cin >> f;
        if (f == -1) break;
        string from, to;
        int distance;
        cin >> from >> to >> distance;
        if (places.find(from) != places.end() && places.find(to) != places.end()) {
            places[from]->addNeighbourPQ(places[to], distance);
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
    PlacePQ* startingPoint = places[startName];
    PlacePQ* endPoint = places[destinationName];
    unordered_map<PlacePQ*, PlacePQ*> travelHistory;
    auto start = chrono::high_resolution_clock::now();
    unordered_map<PlacePQ*, int> travelDistances = Dijkstra::findShortestPathPQ(startingPoint, endPoint, travelHistory);
    auto stop = chrono::high_resolution_clock::now();
    cout<<"Dijkstra with priority queue\n";
    if (travelDistances.count(endPoint) > 0) {
        cout << "Shortest distance to destination: " << travelDistances[endPoint] << endl;
        auto start1 = chrono::high_resolution_clock::now();
        vector<PlacePQ*> travelRoute = Dijkstra::reconstructPathPQ(startingPoint, endPoint, travelHistory);
        auto stop1 = chrono::high_resolution_clock::now();
        cout << "Shortest Path:\n";
        for (PlacePQ* location : travelRoute) {
            cout << location->getNamePQ() << " -> ";
        }
        cout << "Destination" << endl;
        auto dur = chrono::duration_cast<chrono::microseconds>((stop - start)+(stop1-start1));
        cout<<"Time taken: "<<dur.count()<<" microseconds"<<endl;
    } else {
        cout << "No path found to destination." << endl;
    }
    for (auto& entry : places) {
        delete entry.second;
    }
    cout<<"\n-------------------------\n";
    return 0;
}
