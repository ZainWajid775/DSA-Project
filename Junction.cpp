
#include <iostream>
#include <string>
#include <list>
#include <unistd.h>
#include "Vehicle.h"
#include "Data_Structures/Linked_List.h"
#include "Data_Structures/Vector.h"

using namespace std;

// Struct for vertices (junction)
struct Junction
{
    // Node information
    string name;                // Name of the junction 
    int r , c;                  // Coordinates in 2D plane
    int capacity;               // Maximum number of vehicles that can be stored
    int current_veh_count;      // Number of vehicles currently at junction
    int signal_timer;           // Signal timer for traffic light
    bool traffic_light;         // Traffic Light functionality

    // Junction Constructor
    Junction(string j_name , int j_r , int j_c , int j_capacity , int j_timer)
    {
        name = j_name;
        r = j_r;
        c = j_c;
        capacity = j_capacity;
        current_veh_count = 0;
        signal_timer = j_timer;
    }

    string get_veh_count()
    {
        return(to_string(current_veh_count));
    }

    // Signal Functionality
    List signal_queue;   // Stores vehicles currently at signal
    
    // Print vehicle information according to priority or id
    vector<Vehicle> print_signal_queue()
    {
        vector<Vehicle> temp;
        int *arr = new int[signal_queue.size()];

        if(signal_queue.is_empty())
        {
            return temp;
        }

        arr = signal_queue.duplicate_list();

        for(int i = 0 ; i < signal_queue.size() ; i++)
        {
            for(int j = 0 ; j < signal_queue.size() ; j++)
            {
                if(arr[i] > arr[j])
                {
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }

        // Match the id to the vehicle and return it into vector
        for(int i = 0 ; i < signal_queue.size() ; i++)
        {
            temp.push_back(signal_queue.return_vehicle(arr[i]));
        }

        return temp;
        
    }

    // Checks and adds vehicle to the queue if there is space
    bool add_vehicle(Vehicle v)       
    {
        if(current_veh_count < capacity)
        {
            signal_queue.insert(v);
            current_veh_count++;
            return true;
        }
        return false;
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

    int get_signal_timer()
    {   
        return signal_timer;
    }
    
    void change_traffic_light()
    {
        traffic_light = !traffic_light;
    }
    
    void temp()
    {
        change_traffic_light();
    }

};

