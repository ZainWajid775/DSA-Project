#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <unordered_map>
#include <vector>
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
    string current_node;
    string destination_node;   
    char status;            // Unused
    float time_of_arrival;  // Unused
  
    // Static storage for generated vehicles (to ensure unique IDs)
    static unordered_map<int , Vehicle*> generated_vehicle_ids;

    // Constructor for vehicle for user generated custom vechicles
    // Incase of duplicate vehicles, the users generated vehicle will be prioritized
    Vehicle(int v_id, int v_priority, string v_current_node, string v_destination_node)
    {
        id = v_id;
        priority = v_priority;
        current_node = v_current_node;
        destination_node = v_destination_node;

        //UNUSED
        status = 'a';
        time_of_arrival = 0;

        // Deletes the duplicate vehicle if it already existed in the database
        if(generated_vehicle_ids.find(v_id) == generated_vehicle_ids.end())
        {
            delete generated_vehicle_ids[v_id];
        }

        generated_vehicle_ids[id] = this;
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

        current_node = generation_node;
        destination_node = arrival_node;

        status = 'a';
        time_of_arrival = 0;

        generated_vehicle_ids[id] = this;

        
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

// Definition of the static member
unordered_map<int, Vehicle*> Vehicle::generated_vehicle_ids;


#endif // VEHICLE_H
