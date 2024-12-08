#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "Map.h" 
#include "Simulation.h"

using namespace std;

int main() {
    //// Create a map and populate it
    //Map map("City Map", 5); // Example initialization, adjust as needed
//
    //// Add junctions, roads, and vehicles
    //Junction *j1 = new Junction("J1", 0, 0, 5, 5);
    //Junction *j2 = new Junction("J2", 0, 1, 5, 4);
    //Junction *j3 = new Junction("J3", 0, 2, 5, 3);
    //Junction *j4 = new Junction("J4", 0, 3, 5, 2);
    //Junction *j5 = new Junction("J5", 0, 4, 5, 1);
    //Junction *j6 = new Junction("J6", 1, 0, 5, 6);
    //Junction *j7 = new Junction("J7", 1, 1, 5, 7);
    //Junction *j8 = new Junction("J8", 1, 2, 5, 8);
    //Junction *j9 = new Junction("J9", 1, 3, 5, 9);
    //Junction *j10 = new Junction("J10", 1, 4, 5, 10);
    //Junction *j11 = new Junction("J11", 2, 0, 5, 11);
    //Junction *j12 = new Junction("J12", 2, 1, 5, 12);
    //Junction *j13 = new Junction("J13", 2, 2, 5, 13);
    //Junction *j14 = new Junction("J14", 2, 3, 5, 14);
    //Junction *j15 = new Junction("J15", 2, 4, 5, 15);
    //Junction *j16 = new Junction("J16", 3, 0, 5, 16);
//
    //Road *r1 = new Road("R1", 1.0, 3, "J1", "J2"); // Horizontal road
    //Road *r2 = new Road("R2", 1.0, 3, "J2", "J3"); // Horizontal road
    //Road *r3 = new Road("R3", 1.0, 3, "J3", "J4"); // Vertical road
    //Road *r4 = new Road("R4", 1.0, 3, "J4", "J5"); // Vertical road
//
    //map.add_junction(j1);
    //map.add_junction(j2);
    //map.add_junction(j3);
    //map.add_junction(j4);
    //map.add_junction(j5);
    //map.add_junction(j6);
    //map.add_junction(j7);
    //map.add_junction(j8);
    //map.add_junction(j9);
    //map.add_junction(j10);
    //map.add_junction(j11);
    //map.add_junction(j12);
    //map.add_junction(j13);
    //map.add_junction(j14);
    //map.add_junction(j15);
    //map.add_junction(j16);
//
    //map.add_road(r1 , false);
    //map.add_road(r2 , false);
    //map.add_road(r3 , false);
    //map.add_road(r4 , false);
//
//
    //Vehicle v1("J1", "J2", 5);
    //// Start the traffic light simulation
    //thread traffic_light_thread(simulate_traffic_lights, ref(map));
//
    //cout << "Press Enter to stop the simulation..." << endl;
    //cin.get(); // Wait for user input to stop
//
    //// Stop the simulation
    //keep_running = false;
    //traffic_light_thread.join(); // Wait for the thread to finish
//
    //cout << "Simulation stopped." << endl;
    //    
//
    //return 0;

        // Create a map and populate it with simple junctions and roads
    Map map("Test City", 2); // A small map with 2 junctions

    // Add junctions
    Junction *j1 = new Junction("J1", 0, 0, 5, 1);
    Junction *j2 = new Junction("J2", 0, 1, 5, 2);
    
    // Create one road between them
    Road *r1 = new Road("R1", 1.0, 3, "J1", "J2");

    // Add junctions and road to the map
    map.add_junction(j1);
    map.add_junction(j2);
    map.add_road(r1, false);

    // Add vehicles at J1
    Vehicle v1("J1", "J2", 5);  // Vehicle from J1 to J2, with 5 moves
    Vehicle v2("J1", "J2", 3);  // Vehicle from J1 to J2, with 3 moves



    return 0;
}