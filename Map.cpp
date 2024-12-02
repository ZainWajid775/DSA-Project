#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include "Road.cpp"
#include "Junction.cpp"
#include "Data_Structures/Vector.h"

using namespace std; 

class Map
{
    public:
        // Junction Matrix (1d as each junction object stores its x and y co-ordiantes)
        vector<Junction> Junction_Matrix;

        // Road Matrix (2d)
        int num_of_junctions;
        vector<vector<Road*> > Road_Matrix;

        // Constructor
        Map(int m_junctions)
        {
            num_of_junctions = m_junctions;
            Road_Matrix.resize(num_of_junctions , vector<Road*>(num_of_junctions , nullptr));
        }

        // Add Junction
        void add_junction(Junction j)
        {
            Junction_Matrix.push_back(j);
        }

        // Add Road
        bool add_road(Road* r , string junction_1 , string junction_2 , bool is_two_way)
        { 
            // Check if junctions exist and extract them
            bool j1_exists = false , j2_exists = false;
            int j1_index = -1 , j2_index = -1;

            for(int i = 0 ; i < Junction_Matrix.size() ; i++)
            {
                if(junction_1 == Junction_Matrix[i].name)
                {
                    j1_exists = true;
                    j1_index = i;
                }
                if(junction_2 == Junction_Matrix[i].name)
                {
                    j2_exists = true;
                    j2_index = i;
                }
            }

            if(j1_exists && j2_exists)
            {
                Road_Matrix[j1_index][j2_index] = r;

                if(is_two_way)
                {
                    Road_Matrix[j2_index][j1_index] = r;
                }

                return true;
            }

            return false;
        }

       void display_map()
{
    // Print column headers (X axis)
    cout << "       ";  // Extra space to accommodate row labels
    for (int j = 0; j < num_of_junctions; j++)
    {
        // Print X coordinate header with fixed width for spacing
        cout << setw(12) << "X" + to_string(j);
    }
    cout << endl;

    // Print junction names (top row for Y0, Y1, etc.)
    cout << "Junctions";
    for (int j = 0; j < num_of_junctions; j++)
    {
        // Print the junction name at the respective coordinates
        bool junction_found = false;
        for (const auto& junction : Junction_Matrix)
        {
            if (junction.x == 0 && junction.y == j)  // Check for Y0 row
            {
                cout << setw(12) << junction.name;
                junction_found = true;
                break;
            }
        }
        if (!junction_found)
        {
            cout << setw(12) << " ";  // Blank space if no junction
        }
    }
    cout << endl;

    // Print the roads (below the junctions for Y0, Y1, etc.)
    cout << " Roads";
    for (int j = 0; j < num_of_junctions; j++)
    {
        bool road_found = false;
        for (int i = 0; i < num_of_junctions; i++)
        {
            if (Road_Matrix[i][j] != nullptr)
            {
                Road* road = Road_Matrix[i][j];
                cout << setw(12) << road->name;  // Print road name below junction
                road_found = true;
                break;
            }
        }
        if (!road_found)
        {
            cout << setw(12) << " ";  // Blank space if no road
        }
    }
    cout << endl;
}


};


int main()
{
    Map map(2);

    Road temp("Broadway" , 100 , 0);
    Road* ptr;
    ptr = &temp;

    Junction j1("Avenue" , 0 , 0 , 0);
    Junction j2("Avenue2" , 0 , 1 , 0);

    map.add_junction(j1);
    map.add_junction(j2);
    map.add_road(ptr , "Avenue" , "Avenue2" , false);   


    Vehicle v("Avenue" , "Avenue2");

    temp.add_to_road(v);
    map.display_map();




}