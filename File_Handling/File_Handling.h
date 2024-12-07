#ifndef FILE_HANDLING_h
#define FILE_HANDLING_h

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../Data_Structures/Vector.h"
#include "../Map.h"

using namespace std;

void store_credentials(vector<string> credentials)
{
    ofstream file("File_Handling/Accounts.txt");

    if(!file.is_open())
    {
        cerr << "Error opening file !" << endl;
        exit(1);
    }

    for (size_t i = 0; i < credentials.size(); i++)
    {
        file << credentials[i] << endl;
    }

    file.close();
}

vector<string> read_credentials()
{
    ifstream file("File_Handling/Accounts.txt");

    vector<string> credentials;
    string line;
    string username , password;
    bool pair = true;

    if(!file.is_open())
    {
        cerr << "Error opening file !" << endl;
        exit(1);
    }

    while(getline(file , line))
    {
        username = line;

        if(getline(file , line))
        {
            password = line;
            string temp = username + "|" + password;
            
            credentials.push_back(temp);
        }

    }

    return credentials; 
}



bool store_map(Map* map)
{
    string save_filename = "File_Handling/" + map->map_name + ".txt";

    ofstream file(save_filename);

    if(!file.is_open())
    {
        cout << "Error opening file !" << endl;
        return false;
    }

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
                          to_string(junction->capacity) + "|" + 
                          to_string(junction->signal_timer) + "|" + 
                          to_string(junction->traffic_light);

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

    file << map->map_name + "_" + "roads" << endl << endl;

    file.close();
    return true;

}

Map* read_map(string map_name , Map** arr , int index)
{
    string save_file = "File_Handling/" + map_name + ".txt";

    ifstream file(save_file);

    if(!file.is_open())
    {
        cerr << "Error opening file !" << endl;
        return nullptr;
    }

    string line;

    arr[index] = new Map(map_name , 0);

    // Read first line to get name and then create seperators for roads and junctions
    getline(file , line);
    arr[index]->map_name = line;
    string seperator_j = line + "_junctions";
    string seperator_r = line + "_roads";

    getline(file , line);
    arr[index]->num_of_junctions = stoi(line);

    string read_line;

    while(getline(file , read_line))
    {
        if(read_line == seperator_j)
        {
            break;
        }

        string name;
        int r, c, capacity, timer, traffic_light;

        stringstream ss(read_line);  
        getline(ss, name, '|'); 
        ss >> r;  
        ss.ignore(1, '|');  
        ss >> c;  
        ss.ignore(1, '|');  
        ss >> capacity;  
        ss.ignore(1, '|');  
        ss >> timer;  
        ss.ignore(1, '|'); 
        ss >> traffic_light;

        Junction* junction = new Junction(name , r , c , capacity , timer);
        junction->traffic_light = traffic_light;

        arr[index]->add_junction(junction);
    }

    arr[index]->road_resize();

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

        arr[index]->add_road(road , false);

    }


    return arr[index];

}

#endif

