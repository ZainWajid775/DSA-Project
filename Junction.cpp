
#include <iostream>
#include <string>
#include <unistd.h>
#include "Vehicle.h"
#include "Data_Structures/Linked_List.h"
#include "Data_Structures/Vector.h"

using namespace std;

// Struct for vertices (junction)
class Junction
{
    public:
    
    // Node information
    string name;                // Name of the junction 
    int r , c;                  // Coordinates in 2D plane
    int capacity;               // Maximum number of vehicles that can be stored
    int current_veh_count;      // Number of vehicles currently at junction
    float conjestion;           // Percentage of junction being used

    // Junction Constructor
    Junction(string j_name , int j_r , int j_c , int j_capacity)
    {
        name = j_name;
        r = j_r;
        c = j_c;
        capacity = j_capacity;
        current_veh_count = 0;
        conjestion = 0;
    }

    string get_veh_count()
    {
        return(to_string(current_veh_count));
    }

    // Signal Functionality
    List signal_queue;   // Stores vehicles currently at signal

    // Get vehicle from the front
    Vehicle get_vehicle()
    {
        Vehicle current_veh = signal_queue.get_front();
        remove_vehicle(current_veh);
        return current_veh;
    }

    // Checks and adds vehicle to the queue if there is space
    void add_vehicle(Vehicle v)       
    {
        signal_queue.insert(v);
        current_veh_count++;

        // Update Conjestion
        conjestion = (float)current_veh_count / capacity * 100;        
    }

    // Adds a vehicle to front
    // Used in simulation 
    void add_vehicle_front(Vehicle v)
    {
        signal_queue.insert_front(v);
        current_veh_count++;

        // Update Conjestion
        conjestion = (float)current_veh_count / capacity * 100;

    }

    // Checks if the vehicle is in list and removes it 
    bool remove_vehicle(const Vehicle& vehicle)
    {

        if(signal_queue.exists(vehicle))
        {
            signal_queue.remove(vehicle);
            current_veh_count--;

            // Update Conjestion
            conjestion = (float)current_veh_count / capacity * 100;
            
            return true;
        }
        return false;
    }

    // Check if the vehicle is in the junction
    bool has_vehicle(const Vehicle& vehicle)
    {
        return signal_queue.exists_in_list(vehicle);
    }

    // Check if junction is empty
    bool is_empty()
    {
        return signal_queue.is_empty();
    }

    // Check if junction has space
    bool has_space()
    {
        return (current_veh_count != capacity);
    }

    // Clear the junction queue
    void clear()
    {
        signal_queue.clear();
        current_veh_count = 0;
        conjestion = 0;
    }


};

