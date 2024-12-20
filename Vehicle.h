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
    static Hashmap<int, Vehicle> generated_vehicle_ids; // Use the custom Hashmap

    // Random Vehicle Generation
    Vehicle(int generation_node)
    {
        srand(time(nullptr));

        // ID of each vehicle must be unique, check if ID exists in Hashmap
        do
        {
            id = rand() % 900 + 100; // Generate ID in range [100, 999]
        } while (generated_vehicle_ids.find(id)); // Ensure ID is unique

        current_node = generation_node;
        generated_vehicle_ids.insert(id, *this); // Insert the generated vehicle

    }

    // Destructor: Remove the vehicle from Hashmap when destroyed
    ~Vehicle()
    {
        generated_vehicle_ids.remove(id); // Clean up the generated vehicle
    }

    // Overloaded equality operator to compare Vehicles by ID
    bool operator==(const Vehicle& other) const
    {
        return id == other.id;
    }
};

// Definition of the static member for managing vehicles
Hashmap<int, Vehicle> Vehicle::generated_vehicle_ids(50); // 50 is the initial size of the table

#endif // VEHICLE_H
