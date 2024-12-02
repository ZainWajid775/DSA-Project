#include <iostream>
#include <string>
#include <list>
#include "Vehicle.h"
#include "Data_Structures/Linked_List.h"
#include "Data_Structures/Vector.h"


using namespace std;

// Struct for vertices (junction)
struct Junction
{
    // Node information
    string name;            // Name of the junction 
    int x ,y;               // Coordinates in 2D plane
    int capacity;           // Maximum number of vehicles that can be stored
    int current_veh_count;  // Number of vehicles currently at junction

    // Junction Constructor
    Junction(string j_name , int j_x , int j_y , int j_capacity)
    {
        name = j_name;
        x = j_x;
        y = j_y;
        capacity = j_capacity;
        current_veh_count = 0;
    }

    // Signal Functionality
    List signal_queue;   // Stores vehicles currently at signal
    
    // Checks and adds vehicle to the queue if there is space
    bool add_vehicle(Vehicle v)       
    {
        if(current_veh_count < capacity)
        {
            signal_queue.insert(v);
            current_veh_count++;
            return true;
        }
        else
        {
            return false;
        }
    }

    // Checks if the vehicle is in list and removes it 
    bool remove_vehicle(const Vehicle& vehicle)
    {

        if(signal_queue.exists(vehicle))
        {
            signal_queue.remove(vehicle);
            current_veh_count--;
            return true;
        }
        return false;
    }
};
