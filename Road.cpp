#include <string>
#include <iostream>
#include "Vehicle.h"
#include "Data_Structures/Linked_List.h"
using namespace std;

// Struct for egde (roads)
struct Road
{
    // Road characteristics
    string name;            // Name of the road 
    float distance;         // Kilometers
    int capacity;           // Capacity
    string start_junction;  // Start junction
    string end_junction;    // End junction

    // Vehicle information on road
    int veh_count;          // Current vehicle count
    float conjestion;       // Percentage of road being used
    char status;            // 'b' blocked , 'a' active , 'c' conjestion , 'i' inactive

    // to hold current vehicles on road
    List vehicles_on_road;

    // Road Constructor
    Road (string r_name , float r_distance , int r_capacity , string r_start_junction , string r_end_junction)
    {
        name = r_name;
        distance = r_distance;
        capacity = r_capacity;
        start_junction = r_start_junction;
        end_junction = r_end_junction;

        // Default values
        veh_count = 0;
        conjestion = 0;
        status = 'a';
    }

    // Vehicle Movement Functions

    void add_vehicle_front(Vehicle v)
    {
        vehicles_on_road.insert_front(v);

        // Update Conjestion
        veh_count++;
        conjestion = (float)veh_count / capacity * 100;

        if(conjestion > 80)
        {
            status = 'c';
        }
        else if(conjestion > 100)
        {
            status = 'b';
        }
        else if(conjestion < 80)
        {
            status = 'a';
        }

    }

    bool add_to_road(Vehicle v)
    {   
        // Dont add to road if it is disabled, blocked or at max capacity
        if(status == 'i' || status == 'b' || veh_count == capacity)
        {
            return false;
        }
        else
        {
            vehicles_on_road.insert(v);

            // Update Conjestion
            veh_count++;
            conjestion = (float)veh_count / capacity * 100;

            if(conjestion > 80)
            {
                status = 'c';
            }
            else if(conjestion > 100)
            {
                status = 'b';
            }
            else if(conjestion < 80)
            {
                status = 'a';
            }
            return true;
        }
    }

    bool remove_from_road(Vehicle v)
    {
        if(vehicles_on_road.exists(v))
        {
            vehicles_on_road.remove(v);
            veh_count--;
            conjestion = (float)veh_count / capacity * 100;

            if(conjestion > 80)
            {
                status = 'c';
            }
            else if(conjestion > 100)
            {
                status = 'b';
            }
            else if(conjestion < 80)
            {
                status = 'a';
            }
            return true;
        }
        return false;
    }

    // Return vehicle from front
    Vehicle get_vehicle()
    {
        Vehicle current_veh = vehicles_on_road.get_front();
        remove_from_road(current_veh);
        return current_veh;
    }

    // Check if road is empty
    bool empty()
    {
        return(veh_count == 0);
    }

    // Check if vehicle is on this road
    bool exists(Vehicle v)
    {
        return vehicles_on_road.exists_in_list(v);
    }

    // Change road status
    void update_status(char r_status)
    {
        status = r_status;
    }

    bool has_space()
    {
        return (veh_count != capacity);
    }

    float get_conjestion()
    {
        return conjestion;
    }

    void clear()
    {
        vehicles_on_road.clear();
        veh_count = 0;
        conjestion = 0;
    }

    // Debugging function
    void debug()
    {
        cout << name << " " << start_junction << " " << end_junction << endl;
    }


};