#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <unordered_map>
#include <pthread.h>
#include <unistd.h>

using namespace std;

// Define a structure to represent a traffic light status at each intersection
struct TrafficSignal {
    bool isGreen;
    int greenTime; // Duration for green signal in seconds
    int redTime;   // Duration for red signal in seconds


    // Default constructor with default values
    TrafficSignal() : isGreen(true), greenTime(30), redTime(30) {}
    // Constructor to initialize TrafficSignal
    TrafficSignal(bool green, int greenT, int redT) 
        : isGreen(green), greenTime(greenT), redTime(redT) {}
};

// Define a class for Traffic Management System
class TrafficManagementSystem {
private:
    int numIntersections;
    vector<vector<int> > adjMatrix; // Adjacency matrix for roads between intersections
    unordered_map<int, TrafficSignal> trafficSignals; // Traffic signal control
    vector<int> vehicleCount; // Vehicle count at each intersection
    pthread_mutex_t mutex; // Mutex to protect shared data (vehicle counts and signals)

public:
    // Constructor to initialize the system with the number of intersections
    TrafficManagementSystem(int n) : numIntersections(n), adjMatrix(n, vector<int>(n, INT_MAX)), vehicleCount(n, 0) {
        pthread_mutex_init(&mutex, nullptr); // Initialize mutex
        for (int i = 0; i < n; ++i) {
            // Use constructor-style initialization
            trafficSignals[i] = TrafficSignal(true, 30, 30); // 30 seconds for green and red time
        }
    }

    // Destructor to destroy the mutex
    ~TrafficManagementSystem() {
        pthread_mutex_destroy(&mutex);
    }

    // Function to add a road between two intersections with a given distance (time)
    void addRoad(int u, int v, int distance) {
        adjMatrix[u][v] = distance;
        adjMatrix[v][u] = distance;
    }

    // Dijkstra's Algorithm to find the shortest path from source intersection to destination
    void dijkstra(int source, int destination) {
        vector<int> dist(numIntersections, INT_MAX);
        vector<int> parent(numIntersections, -1);
        dist[source] = 0;

        // Fixed issue with '>>' syntax for priority_queue
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
        pq.push(pair<int, int>(0, source));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (u == destination) break;

            for (int v = 0; v < numIntersections; ++v) {
                if (adjMatrix[u][v] != INT_MAX) {
                    int alt = dist[u] + adjMatrix[u][v];
                    if (alt < dist[v]) {
                        dist[v] = alt;
                        parent[v] = u;
                        pq.push(pair<int, int>(dist[v], v));
                    }
                }
            }
        }

        // Print the shortest path and its distance
        if (dist[destination] == INT_MAX) {
            cout << "No path found from intersection " << source << " to intersection " << destination << endl;
        } else {
            cout << "Shortest path from " << source << " to " << destination << ": ";
            int curr = destination;
            vector<int> path;
            while (curr != -1) {
                path.push_back(curr);
                curr = parent[curr];
            }
            reverse(path.begin(), path.end());
            for (int i : path) {
                cout << i << " ";
            }
            cout << "\nTotal distance: " << dist[destination] << endl;
        }
    }

    // Simulate vehicle passing through an intersection (with thread synchronization)
    void vehiclePass(int intersection) {
        pthread_mutex_lock(&mutex); // Lock the mutex to safely update shared data
        vehicleCount[intersection]++;
        cout << "Vehicle passed through intersection " << intersection << ". Current count: " << vehicleCount[intersection] << endl;
        pthread_mutex_unlock(&mutex); // Unlock the mutex
    }

    // Simulate traffic light status and update vehicle flow based on signal
    void updateTrafficSignal(int intersection) {
        TrafficSignal& signal = trafficSignals[intersection];
        if (signal.isGreen) {
            cout << "Intersection " << intersection << " has GREEN light.\n";
        } else {
            cout << "Intersection " << intersection << " has RED light.\n";
        }
    }

    // Function to print vehicle counts at intersections
    void printVehicleCounts() {
        cout << "Vehicle count at each intersection:\n";
        for (int i = 0; i < numIntersections; ++i) {
            cout << "Intersection " << i << ": " << vehicleCount[i] << " vehicles\n";
        }
    }

    // Function to simulate a vehicle's movement through a road (thread function)
    static void* vehicleSimulation(void* arg) {
        TrafficManagementSystem* system = (TrafficManagementSystem*)arg;
        int intersection = rand() % system->numIntersections; // Random intersection for vehicle to pass
        system->vehiclePass(intersection);
        sleep(1); // Simulate a 1-second delay between vehicles
        return nullptr;
    }

    // Function to start vehicle threads (simulate multiple vehicles)
    void startVehicleSimulation(int numVehicles) {
        pthread_t threads[numVehicles];

        for (int i = 0; i < numVehicles; ++i) {
            if (pthread_create(&threads[i], nullptr, vehicleSimulation, (void*)this) != 0) {
                cerr << "Error creating thread!" << endl;
                return;
            }
        }

        // Wait for all vehicle threads to finish
        for (int i = 0; i < numVehicles; ++i) {
            pthread_join(threads[i], nullptr);
        }
    }
};

int main() {
    // Create a traffic management system with 5 intersections
    TrafficManagementSystem system(5);

    // Add roads between intersections (adjacency matrix)
    system.addRoad(0, 1, 10); // Road between intersection 0 and 1 with a travel time of 10 units
    system.addRoad(0, 2, 15); // Road between intersection 0 and 2 with a travel time of 15 units
    system.addRoad(1, 3, 10); // Road between intersection 1 and 3
    system.addRoad(2, 3, 10); // Road between intersection 2 and 3
    system.addRoad(3, 4, 5);  // Road between intersection 3 and 4

    // Start vehicle simulation with 10 vehicles
    system.startVehicleSimulation(10);

    // Print vehicle count at each intersection after simulation
    system.printVehicleCounts();

    // Find the shortest path from intersection 0 to intersection 4
    system.dijkstra(0, 4);

    // Update traffic signals for intersection 2 (Example)
    system.updateTrafficSignal(2);

    return 0;
}
