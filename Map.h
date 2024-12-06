#ifndef MAP_H
#define MAP_H

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
        // Junctions stored in a vector (indexed by ID)
        vector<Junction*> Junction_Matrix;

        // Road Matrix (adjacency matrix)
        vector<vector<Road*> > Road_Matrix;

        int num_of_junctions;

        // Constructor
        Map(int m_junctions)
        {
            num_of_junctions = m_junctions;
            Road_Matrix.resize(num_of_junctions * 2 , vector<Road*>(num_of_junctions * 2, nullptr));
        }

        // Add Junction
        void add_junction(Junction* j)
        {
            Junction_Matrix.push_back(j);
        }

        // Check if the junction pair exists
        bool check_junction_pair(const string& j1, const string& j2)
        {
            if (j1 == j2) return false;

            bool j1_e = false, j2_e = false;
            for (const auto& junction : Junction_Matrix)
            {
                Junction* temp = junction;
                if (temp->name == j1) j1_e = true;
                if (temp->name == j2) j2_e = true;
            }
            return j1_e && j2_e;
        }

        // Add road between two junctions
        void add_road(Road* r, bool is_two_way)
        {
            int s_j_r = -1, e_j_c = -1;

            // Check if the junctions exist
            if (check_junction_pair(r->start_junction, r->end_junction))
            {
                // Find indices of junctions in the Junction_Matrix
                for (int i = 0; i < Junction_Matrix.size(); i++)
                {
                    Junction *temp = Junction_Matrix[i];
                    if (r->start_junction ==temp->name)
                    {
                        s_j_r = i;  // Row index for start junction
                    }
                    if (r->end_junction == temp->name)
                    {
                        e_j_c = i; // Column index for end junction
                    }
                }
                if (s_j_r != -1 && e_j_c != -1)
                {
                    // Add road to the road matrix (adjacency matrix)
                    Road_Matrix[s_j_r][e_j_c] = r;
                    if (is_two_way)
                    {
                        Road_Matrix[e_j_c][s_j_r] = r; // Add bidirectional road
                    }
                }
            }
        }


        void display_junctions()
        {
            const int max_rows = num_of_junctions;
            const int max_cols = num_of_junctions;
            const int cell_width = 12;

            // Print top border
            cout << "+" << string((cell_width + 1) * max_cols, '-') << "+\n";

            // Iterate through rows
            for (int row = 0; row < max_rows; row++)
            {
                for (int line = 0; line < 3; line++) // Each junction will have 3 lines
                {
                    cout << "|";
                    for (int col = 0; col < max_cols; col++)
                    {
                        string cell_content = " ";
                        string color_code = "\033[0m"; // Default color (reset)

                        bool has_incoming_road = false;

                        // Find and display junction name at the coordinate
                        for (int i = 0 ; i < Junction_Matrix.size() ; i++) 
                        {
                            Junction *temp;
                            temp = Junction_Matrix[i];

                            if (temp->r == row && temp->c == col)
                            {
                                if (line == 1) // Middle line for junction name
                                {
                                    cell_content = temp->name;

                                    // Check if any roads are leading to this junction (check for incoming roads)
                                    for (size_t i = 0; i < Road_Matrix.size(); i++)
                                    {
                                        if (Road_Matrix[i][col] != NULL) // Road leads to this column (incoming road)
                                        {
                                            has_incoming_road = true;
                                            break;
                                        }
                                    }

                                    // Set color based on traffic light state if there are incoming roads
                                    if (has_incoming_road)
                                    {
                                        if (temp->traffic_light)
                                        {
                                            color_code = "\033[32m"; // Green for traffic light ON
                                        }
                                        else
                                        {
                                            color_code = "\033[31m"; // Red for traffic light OFF
                                        }
                                    }
                                }

                                // Third line for vehicle count
                                if (line == 2)
                                {
                                    string vehicle_count_str = temp->get_veh_count(); // Get vehicle count
                                    cout << string((cell_width - vehicle_count_str.size()) / 2, ' ') << vehicle_count_str
                                         << string(cell_width - (cell_width - vehicle_count_str.size()) / 2 - vehicle_count_str.size(), ' ');
                                }
                                break;
                            }
                        }

                        if (line == 1)
                        {
                            int padding = (cell_width - cell_content.size()) / 2;
                            cout << string(padding, ' ') << color_code << cell_content
                                 << "\033[0m" // Reset color after name
                                 << string(cell_width - padding - cell_content.size(), ' ');
                        }
                        else if (line != 2)
                        {
                            cout << string(cell_width, ' ');
                        }
                        cout << "|";
                    }
                    cout << "\n";
                }
                cout << "+" << string((cell_width + 1) * max_cols, '-') << "+\n";
            }
        }



        // Display the road map with road details
        void display_road_map()
        {
            cout << "\nRoad Map:\n";
            cout << "Start Junction\tEnd Junction\tRoad Name\tDirection\n";

            // Iterate through all roads
            for (size_t i = 0; i < Road_Matrix.size(); i++)
            {
                for (size_t j = 0; j < Road_Matrix[i].size(); j++)
                {
                    Road* road = Road_Matrix[i][j];
                    if (road != nullptr)
                    {
                        Road* temp = road;
                        if (Road_Matrix[j][i] == nullptr)
                        {
                            // One-way road
                            Junction * temp_1 = Junction_Matrix[i];
                            Junction * temp_2 = Junction_Matrix[j];

                            cout << setw(18) << left << temp_1->name
                                 << setw(18) << left << temp_2->name
                                 << setw(18) << left << road->name
                                 << setw(8) << left << "→"
                                 << setw(12) << right << "Conjestion : " << road->conjestion
                                 << setw(12) << right << "Status : " << road->status << endl;
                        }
                        else
                        {
                            // Bidirectional road
                            Junction * temp_1 = Junction_Matrix[i];
                            Junction * temp_2 = Junction_Matrix[j];

                            cout << setw(18) << left << temp_1->name
                                 << setw(18) << left << temp_2->name
                                 << setw(18) << left << road->name
                                 << setw(8) << left << "↔"
                                 << setw(12) << right << "Conjestion : " << road->conjestion
                                 << setw(12) << right << "Status : " << road->status << endl;
                       }
                    }
                }
            }
        }

        void temp()
        {
            for(int i = 0; i < Junction_Matrix.size(); i++)
            {
                Junction *temp = Junction_Matrix[i];
                cout << temp->get_veh_count() << endl;
            }
            
        }
};

#endif
