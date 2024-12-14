#ifndef FILE_HANDLING_h
#define FILE_HANDLING_h

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "../Data_Structures/Vector.h"
#include "../Map.h"

using namespace std;

// Store all users in container
// username|password
void store_credentials(vector<string> credentials)
{
    ofstream file("File_Handling/Accounts.txt");

    if(!file.is_open())
    {
        throw runtime_error("Accounts file cannot be accessed!");
    }

    for (size_t i = 0; i < credentials.size(); i++)
    {
        file << credentials[i] << endl;
    }

    file.close();
}

// Read entries in credentials file and return in string vector
vector<string> read_credentials()
{
    ifstream file("File_Handling/Accounts.txt");

    vector<string> credentials;
    string line;

    if(!file.is_open())
    {
        throw runtime_error("Accounts file cannot be accessed!");
    }

    while(getline(file , line))
    {   
        credentials.push_back(line);
    }

    return credentials; 
}

// for all maps in container
bool store_map_container(vector<Map*> container)
{
    ofstream file("File_Handling/Maps.txt");

    if(!file.is_open())
    {
        throw runtime_error("Maps file cannot be accessed!");
    }

    for (auto& map : container)
    {
        file << map->map_name << endl;
        file << map->num_of_junctions << endl;

        // Store Junction with all information in one line
        for (size_t i = 0; i < map->Junction_Matrix.size(); i++)
        {
            Junction* junction = map->Junction_Matrix[i];

            if (junction != nullptr)
            {
                string line = junction->name + "|" + to_string(junction->r) + "|" + 
                              to_string(junction->c) + "|" + 
                              to_string(junction->capacity);

                file << line << endl; 
            }
        }

        file << map->map_name + "_" + "junctions" << endl;

        for(size_t i = 0; i < map->Road_Matrix.size(); i++)
        {
            for(size_t j = 0; j < map->Road_Matrix[i].size(); j++)
            {
                Road* road = map->Road_Matrix[i][j];
                if(road != nullptr)
                {
                    string line = road->name + "|" + to_string(road->distance) + "|" + 
                                  to_string(road->capacity) + "|" + road->start_junction + "|" + 
                                  road->end_junction + "|" + to_string(road->veh_count) + "|" + 
                                  to_string(road->conjestion) + "|" + road->status;

                    file << line << endl;
                }
            }
        }

        file << map->map_name + "_" + "roads" << endl;
    }

    file.close();
    return true;
}



// Reads entire map file and returns the created maps as a vector of pointers
vector<Map*> read_maps() 
{
    vector<Map*> container;

    string save_file = "File_Handling/Maps.txt";

    ifstream file(save_file);

    if(!file.is_open())
    {
        throw runtime_error("Map file cannot be accessed!");
    }

    if(file.peek() == EOF)
    {
        return container;
    }

    try
    {
        string line;

        while(getline(file , line))
        {

            Map* map_being_read = new Map(line , 0);

            // Create seperators for roads and junctions
            string seperator_j = line + "_junctions";
            string seperator_r = line + "_roads";
            getline(file , line);
            map_being_read->num_of_junctions = stoi(line);

            string read_line;

            while(getline(file , read_line))
            {
                if(read_line == seperator_j)
                {
                    break;
                }

                string name;
                int r, c, capacity;

                stringstream ss(read_line);  
                getline(ss, name, '|'); 
                ss >> r;  
                ss.ignore(1, '|');  
                ss >> c;  
                ss.ignore(1, '|');  
                ss >> capacity;  

                Junction* junction = new Junction(name , r , c , capacity);

                map_being_read->add_junction(junction);
            }

            map_being_read->road_resize();

            while(getline(file , read_line))
            {
                if(read_line == seperator_r)
                {
                    break;
                }

                string name , start , end , status; 
                int capacity , vehicles;
                float distance , conjestion;

                stringstream ss(read_line);
                getline(ss, name, '|');  
                ss >> distance;          
                ss.ignore(1, '|');       
                ss >> capacity;         
                ss.ignore(1, '|');       
                getline(ss , start , '|'); 
                getline(ss , end , '|');
                ss >> vehicles;
                ss.ignore(1, '|');     
                ss >> conjestion;        
                ss.ignore(1, '|');       
                getline(ss , status , '|');

                Road* road = new Road(name , distance , capacity , start , end);
                road->veh_count = vehicles;
                road->conjestion = conjestion;
                road->status = status[0];

                map_being_read->add_road(road);

            }

            container.push_back(map_being_read);
        }
    }
    catch(const std::exception& e)
    {
        throw std::runtime_error("Error reading maps file!");
    }
    return container;
}

#endif

