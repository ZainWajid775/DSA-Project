#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "Map.h" 
#include "Data_Structures/Vector.h"

using namespace std;

atomic<bool> keep_running(true); // Control flag for the thread

void simulate_traffic_lights(Map &map) 
{
    // A container of every thread
    // Each thread will simulate a junction
    vector<thread> threads;

    // Create a thread for each junction
    for (auto& junction : map.Junction_Matrix) 
    {   
        // Create a new thread and add it to threads container
        // Lambda passes each junction to the thread to so it works on its own copy of the junction
        threads.emplace_back([junction, &map]() 
        {
            while (keep_running) 
            {
                // Check if the junction has any connected roads
                bool has_connected_road = false;

                for (const auto& road_row : map.Road_Matrix) 
                {
                    for (const auto& road : road_row) 
                    {
                        // If there is a road and it matches the junctions coordinates either way
                        if (road != nullptr && (road->start_junction == junction->name || road->end_junction == junction->name)) 
                        {
                            has_connected_road = true;
                            break;
                        }
                    }

                    if (has_connected_road) 
                    {
                        break;
                    }
                }

                // Update the traffic light if the junction is connected
                // Thread sleeps until timer and then updates the traffic light
                if (has_connected_road) 
                {
                    this_thread::sleep_for(chrono::seconds(junction->get_signal_timer()));
                    junction->change_traffic_light();
                } 
                // Skip isolated junctions
                else 
                {
                    break;
                }
            }
        }
        );
    }

    // Seperate thread to display map after every cycle
    thread display_thread([&map]() 
    {
        while (keep_running) 
        {
            this_thread::sleep_for(chrono::seconds(1));
            map.display_map(); 
            cout << endl;
        }
    });

    // Detach all threads to run independently
    for (auto& t : threads) 
    {
        t.detach();
    }

    display_thread.detach();
}



#endif
