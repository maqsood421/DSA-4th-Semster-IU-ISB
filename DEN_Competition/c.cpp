#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

const int NUM_CITIES = 4;  // Islamabad, Lahore, Gujranwala, Karachi
const int MAX_ROUTES = 5;   // Number of possible routes between cities

// Define a 3D distance matrix (source, destination, route)
int distances[NUM_CITIES][NUM_CITIES][MAX_ROUTES] = {
    {{0, 0, 0, 0, 0}, {300, 300, 300, 300, 300}, {250, 250, 250, 250, 250}, {500, 500, 500, 500, 500}},  // Islamabad
    {{300, 300, 300, 300, 300}, {20, 38, 51, 11, 8}, {89, 92, 101, 42, 39}, {150, 172, 158, 111, 62}},    // Lahore
    {{250, 250, 250, 250, 250}, {89, 92, 101, 42, 39}, {11, 15, 9, 2, 4}, {69, 71, 77, 89, 85}},          // Gujranwala
    {{500, 500, 500, 500, 500}, {150, 172, 158, 111, 62}, {69, 71, 77, 89, 85}, {22, 28, 59, 51, 72}}     // Karachi
};

// Function to find the minimum distance between two cities from the available routes
int getMinDistance(int from, int to) {
    int minDist = INT_MAX;
    for (int i = 0; i < MAX_ROUTES; i++) {
        minDist = min(minDist, distances[from][to][i]);
    }
    return minDist;
}

// Function to compute the total distance for a given route (permutation of cities)
int calculateRouteDistance(vector<int>& route) {
    int totalDistance = 0;
    for (int i = 0; i < route.size() - 1; i++) {
        totalDistance += getMinDistance(route[i], route[i + 1]);
    }
    totalDistance += getMinDistance(route[route.size() - 1], route[0]);  // Return to starting point
    return totalDistance;
}

// Function to find the optimal route using permutations
void findOptimalRoute(vector<string>& cities, string startCity, vector<string>& visitCities) {
    // Map city names to indices for easier handling
    vector<string> allCities = {"Islamabad", "Lahore", "Gujranwala", "Karachi"};
    vector<int> cityIndices(visitCities.size() + 1);

    // Map startCity to its index
    int startIdx = find(allCities.begin(), allCities.end(), startCity) - allCities.begin();
    cityIndices[0] = startIdx;

    // Map visitCities to their indices
    for (int i = 0; i < visitCities.size(); i++) {
        cityIndices[i + 1] = find(allCities.begin(), allCities.end(), visitCities[i]) - allCities.begin();
    }

    // Generate all permutations of the cities to be visited
    vector<int> perm = {cityIndices[0]};  // Start with the start city
    perm.insert(perm.end(), cityIndices.begin() + 1, cityIndices.end());
    int minDistance = INT_MAX;
    vector<int> bestRoute;

    // Generate permutations and calculate the total distance for each
    do {
        int currentDistance = calculateRouteDistance(perm);
        if (currentDistance < minDistance) {
            minDistance = currentDistance;
            bestRoute = perm;
        }
    } while (next_permutation(perm.begin() + 1, perm.end()));  // Keep the start city fixed

    // Output the best route
    cout << "Optimal Route: ";
    for (int i = 0; i < bestRoute.size(); i++) {
        cout << allCities[bestRoute[i]];
        if (i != bestRoute.size() - 1) cout << " -> ";
    }
    cout << endl;

    // Output the minimum distance
    cout << "Minimum Distance: " << minDistance << " km" << endl;
}

int main() {
    string startCity;
    string citiesToVisit;

    // List of all possible cities
    vector<string> allCities = {"Islamabad", "Lahore", "Gujranwala", "Karachi"};
    
    cout << "Please enter the starting city: ";
    getline(cin, startCity);

    cout << "Enter the list of cities you wish to visit separated by commas (e.g., Lahore, Gujranwala, Karachi): ";
    getline(cin, citiesToVisit);

    // Convert the citiesToVisit string into a vector of city names
    stringstream ss(citiesToVisit);
    string city;
    vector<string> visitCities;
    while (getline(ss, city, ',')) {
        visitCities.push_back(city);
    }

    cout << "\nCalculating the shortest possible route starting and ending at " << startCity << "...\n";
    findOptimalRoute(allCities, startCity, visitCities);  // Pass allCities instead of undefined 'cities'
    
    cout << "\nThank you for using the City Route Planner.\n";
    cout << "Safe travels!" << endl;

    return 0;
}
