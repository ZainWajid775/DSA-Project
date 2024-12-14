#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Struct for Vehicle
struct Vehicle
{
    // Vehicle characteristics
    int id;                 // Unique ID for vehicle
    string type;            // Type of vehicle
    int current_node;       // Stores column index of current node
  
    // Static storage for generated vehicles (to ensure unique IDs)
    static unordered_map<int , Vehicle*> generated_vehicle_ids;

    // Random Vehicle Generation
    Vehicle (int generation_node)
    {   
        // ID of each vehicle must be unique so vehicles currently on map are stored in a set and deleted afterwards
        // Checks the set of vehicles until the generated vehicle is unique
        do
        {
            id = rand() % 900 + 100;
        } while (generated_vehicle_ids.find(id) != generated_vehicle_ids.end());

        current_node = generation_node;

        generated_vehicle_ids[id] = this;

    }

    // Destructor
    ~Vehicle()
    {
        generated_vehicle_ids.erase(id);
    }

    // Overloaded operator to compare ids
    bool operator == (const Vehicle& other) const
    {
        return id == other.id;
    }

};

// Definition of the static member
unordered_map<int, Vehicle*> Vehicle::generated_vehicle_ids;


#endif // VEHICLE_H
