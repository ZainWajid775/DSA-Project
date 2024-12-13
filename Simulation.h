#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <cstdlib>
#include "Map.h" 
#include "Data_Structures/Vector.h"

using namespace std;



bool move_vehicle_road_to_junction(Map& map , Vehicle* vehicle)
{
    // Get vehicles current position
    int column = vehicle->current_node;
    int row;

    // Extract Row index
    for(int i = 0 ; i < map.Road_Matrix.size() ; i++)
    {
        Vehicle temp = *vehicle;

        if((map.Road_Matrix[i][column] != nullptr) && (map.Road_Matrix[i][column]->exists(temp)))
        {
            row = i;
            break;
        }
    }
    


    // Check if the vehicle can move to junction
    // Column index of the current road corresponds to the junction
    // 1. Get junction data
    Junction *temp = map.get_junction(column);

    // 2. Check if junction has space
    if(temp->has_space())
    {
        // 3. Update vehicle
        vehicle->current_node = column;
        // 4. Move vehicle to junction
        temp->add_vehicle(*vehicle);
        return true;
    }

    return false;
}

bool move_vehicle_junction_to_road(Map& map , Vehicle* vehicle)
{
    // Get vehicles current position
    // Row index of Junction in road matrix shows next possible moves
    int row = vehicle->current_node;

    // Iterate over all column of road matrix to get connected roads
    // Roads are pushed into an array
    // If a road is full , it is not pushed into the queue

    // 1. Push in possible connections

    vector<Road*> road_arr;
    for(int i = 0 ; i < map.num_of_junctions ; i++)
    {   
        Road *temp = map.Road_Matrix[row][i];
        if(temp != nullptr)
        {
            if(temp->has_space())
            {
                road_arr.push_back(temp);
            }
        }
    }

    // Incase of no possible moves
    if(road_arr.size() != 0)
    {
        // 2. Sort road_arr according to road priority
        // Priority based on road availability
        int size = road_arr.size();
        for(int i = 0 ; i < size - 1 ; i++)
        {
            for(int j = 0 ; j < size - i - 1 ; j++)
            {
                // Ascending order
                float con_1 , con_2;
                con_1 = road_arr[j]->get_conjestion();
                con_2 = road_arr[j+1]->get_conjestion();

                if(con_1 > con_2)
                {
                    Road *temp = road_arr[j];
                    road_arr[j] = road_arr[j+1];
                    road_arr[j+1] = temp;
                }
            }
        }

        // 3. Move to road
        // Extract column index of road to update current position
        string selected_name = road_arr[0]->name;
        for (int i = 0 ; i < map.Road_Matrix[row].size() ; i++)
        {
            Road *temp = map.Road_Matrix[row][i];

            if(temp != nullptr)
            {
                string name = temp->name;
                if(name == selected_name)
                {   
                    vehicle->current_node = i;
                    break;
                }
            }
        }

        road_arr[0]->add_to_road(*vehicle);
        return true;
    }

        


    return false;
}



#endif
