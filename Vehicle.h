#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cstdlib>
#include <ctime>

using namespace std;

// Set to store currently generated vehcile ids to ensure uniqueness
set<int> generated_vehicle_ids;

// Struct for Vehicle
struct Vehicle
{
    // Vehicle characteristics
    int id;                 // Unique ID for vehicle
    int priority;           // Vehicle priority for queues
    string type;            // Type of vehicle
    string current_node;
    string destination_node;   
    char status;            // Unused
    float time_of_arrival;  // Unused

    // Constructor for vehicle 
    Vehicle(int v_id, int v_priority, string v_current_node, string v_destination_node)
    {
        id = v_id;
        priority = v_priority;
        current_node = v_current_node;
        destination_node = v_destination_node;

        //UNUSED
        status = 'a';
        time_of_arrival = 0;
    }

    // Random Vehicle Generation
    Vehicle (string generation_node , string arrival_node)
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

        generated_vehicle_ids.insert(id);

        current_node = generation_node;
        destination_node = arrival_node;

        status = 'a';
        time_of_arrival = 0;

        
    }

    // Random node generation for source and target
    int random_node_generation()
    {
        return rand() % 10 + 1;
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

#endif // VEHICLE_H
