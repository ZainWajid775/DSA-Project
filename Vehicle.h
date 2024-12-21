#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <cstdlib>
#include <ctime>
#include <list>
#include "Data_Structures/Hashmap.h"

// Struct for Vehicle
struct Vehicle
{
    // Vehicle characteristics
    int id;                 // Unique ID for vehicle
    string type;            // Type of vehicle
    int current_node;       // Stores column index of current node

    // Static storage for generated vehicles (to ensure unique IDs)
    // No memory allocated yet
    static Hashmap<int, Vehicle> generated_vehicle_ids; 

    // Random Vehicle Generation
    Vehicle(int generation_node)
    {
        srand(time(nullptr));

        // ID of each vehicle must be unique, check if ID exists in Hashmap
        do
        {
            // Generate a random 3-digit ID until it is unique
            id = rand() % 900 + 100; 
        } while (generated_vehicle_ids.find(id)); 

        current_node = generation_node;
        generated_vehicle_ids.insert(id, *this); 

    }

    // Destructor
    ~Vehicle()
    {
        generated_vehicle_ids.remove(id);
    }

    // Overloaded equality operator to compare Vehicles by ID
    bool operator==(const Vehicle& other) const
    {
        return id == other.id;
    }
};

// Definition of the static member for managing vehicles with memory allocation
Hashmap<int, Vehicle> Vehicle::generated_vehicle_ids(50);

#endif // VEHICLE_H
