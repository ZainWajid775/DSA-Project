#ifndef SIMULATION_H
#define SIMULATION_H

#include <pthread.h>
#include <chrono>
#include <atomic>
#include <iostream>
#include "Map.h"

using namespace std;

// Global atomic flag to control when to stop the simulation
std::atomic<bool> stop_simulation(false);

// Thread function to update all junction signals
void* update_junction_signals(void* arg)
{
    Map* map = static_cast<Map*>(arg);

    // Create a vector to track the next update time for each junction
    vector<std::chrono::steady_clock::time_point> next_update_times;

    // Initialize next update times for all junctions
    for (auto& junction : map->Junction_Matrix)
    {
        Junction *temp = junction;
        next_update_times.push_back(std::chrono::steady_clock::now() + std::chrono::seconds(temp->signal_timer));
    }

    while (!stop_simulation)
    {
        auto now = std::chrono::steady_clock::now();

        // Iterate over all junctions
        for (size_t i = 0; i < map->Junction_Matrix.size(); i++)
        {
            Junction* junction = map->Junction_Matrix[i];

            // Check if the junction has incoming roads
            bool has_incoming_roads = false;
            for (size_t r = 0; r < map->Road_Matrix.size(); r++)
            {
                if (map->Road_Matrix[r][i] != nullptr)
                {
                    has_incoming_roads = true;
                    break;
                }
            }

            if (!has_incoming_roads)
            {
                continue; // Skip junctions with no incoming roads
            }

            // Check if it's time to update the signal for this junction
            if (now >= next_update_times[i])
            {
                // Toggle the traffic light status
                Junction *temp = junction;
                temp->change_traffic_light();

                // Schedule the next update for this junction
                next_update_times[i] = now + std::chrono::seconds(temp->signal_timer);
            }
        }

        // Clear the screen (simulate overwriting the output)
        system("clear");  // On Windows, use "cls"
        map->display_junctions();

    }

    cout << "Simulation stopped.\n";
    return nullptr;
}

// Function to start the simulation
void start_simulation(Map* map)
{
    pthread_t simulation_thread;

    // Start the simulation thread
    if (pthread_create(&simulation_thread, nullptr, update_junction_signals, map) != 0)
    {
        cerr << "Error creating simulation thread\n";
        return;
    }

    cout << "Press Enter to stop the simulation...\n";
    cin.get();  // Wait for user input to stop the simulation

    // Stop the simulation
    stop_simulation = true;

    // Wait for the thread to finish
    pthread_join(simulation_thread, nullptr);
}

#endif
