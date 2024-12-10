#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Struct for Vehicle
struct Vehicle
{
    // Vehicle characteristics
    int id;                 // Unique ID for vehicle
    int priority;           // Vehicle priority for queues
    string type;            // Type of vehicle
    int current_node;
    int movement_counter;   // Random number for number of moves to make in map
  
    // Static storage for generated vehicles (to ensure unique IDs)
    static unordered_map<int , Vehicle*> generated_vehicle_ids;

    // Constructor for vehicle for user generated custom vechicles
    // Incase of duplicate vehicles, the users generated vehicle will be prioritized
    Vehicle(int v_id, int v_priority, int v_current_node)
    {
        id = v_id;
        priority = v_priority;
        current_node = v_current_node;
        type = "User Generated";


        // Deletes the duplicate vehicle if it already existed in the database
        if(generated_vehicle_ids.find(v_id) == generated_vehicle_ids.end())
        {
            generated_vehicle_ids.erase(v_id);
        }

        generated_vehicle_ids[id] = this;
    }

    // Random Vehicle Generation
    Vehicle (int generation_node , int max_moves)
    {   
        int random_type = rand() % 5 + 1;
        switch(random_type)
        {
            case 0: type = "Ambulance" ; priority = 100 ; break;
            case 1: type = "Police" ; priority = 90 ; break;
            case 2: type = "Fire Brigade" ; priority = 80 ; break;
            case 3: type = "Taxi" ; priority = 70 ; break;
            case 4: type = "Car" ; priority = 60 ; break;
            case 5: type = "Bus" ; priority = 50 ; break;
        }

        // ID of each vehicle must be unique so vehicles currently on map are stored in a set and deleted afterwards
        // Checks the set of vehicles until the generated vehicle is unique
        do
        {
            id = rand() % 900 + 100;
        } while (generated_vehicle_ids.find(id) != generated_vehicle_ids.end());

        current_node = generation_node;
        movement_counter = max_moves;

        generated_vehicle_ids[id] = this;

        
    }

    // Random number of moves
    // Max is number of roads
    int random_movement_generation(int max)
    {
        return rand() % max + 1;
    }



    // Destructor
    ~Vehicle()
    {
        generated_vehicle_ids.erase(id);
    }

    bool operator == (const Vehicle& other) const
    {
        return id == other.id;
    }

};

// Definition of the static member
unordered_map<int, Vehicle*> Vehicle::generated_vehicle_ids;


#endif // VEHICLE_H
