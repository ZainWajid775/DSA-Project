#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <set>
#include <cstdlib>
#include <pthread.h>
#include <atomic>
#include "Road.cpp"
#include "Junction.cpp"
#include "Data_Structures/Vector.h"

string red = "\033[31m";
string yellow = "\033[33m";
string green = "\033[32m";
string reset = "\033[0m";

using namespace std; 


class Map
{
    public:
        // Junctions stored in a vector (indexed by ID)
        vector<Junction*> Junction_Matrix;

        // Road Matrix (adjacency matrix)
        vector<vector<Road*> > Road_Matrix;

        int num_of_junctions;
        string map_name;

        // Constructor
        Map(string m_name , int m_junctions)
        {
            map_name = m_name;
            num_of_junctions = m_junctions;
            Road_Matrix.resize(num_of_junctions * 2 , vector<Road*>(num_of_junctions * 2, nullptr));
        }

        void road_resize()
        {
            Road_Matrix.resize(num_of_junctions * 2 , vector<Road*>(num_of_junctions * 2, nullptr));
        }

        // Add Junction
        void add_junction(Junction* j)
        {
            Junction_Matrix.push_back(j);
        }

        // Return maximum number of vehicles junctions can hold
        int max_vehicles()
        {
            int max = 0;

            for(auto& junction : Junction_Matrix)
            {
                max += junction->capacity;
            }

            return max;
        }

        // Check if junction exists by name
        bool has_junction(const string j_name)
        {
            for (const auto& junction : Junction_Matrix)
            {
                Junction* temp = junction;
                if (temp->name == j_name) 
                {
                    return true;
                }
            }
            return false;
        }

        // Check if road exists by name
        bool has_road(const string name)
        {
            for (const auto& road_row : Road_Matrix)
            {
                for (const auto& road : road_row)
                {
                    if (road != nullptr)
                    {
                        if(road->name == name)
                        {
                            return true;
                        }
                    }
                }
            }
            return false;
        }

        //Check if road exists by coordinates
        bool has_road(int row , int col)
        {
            if(Road_Matrix[row][col] == nullptr)
            {
                return false;
            }
            return true;
        }

        // Check if there already a junction at the given coordinates
        bool is_index_clear(int r , int c)
        {
            for (const auto& junction : Junction_Matrix)
            {
                Junction* temp = junction;
                if (temp->r == r && temp->c == c) 
                {
                    return true;
                }
            }
            return false;
        }

        // Check if the junction pair exists
        bool check_junction_pair(const string& j1 , const string& j2)
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

        // Check if junction has connected roads
        bool has_road_connection(Junction* junction)
        {
            for(int i = 0 ; i < Junction_Matrix.size() ; i++)
            {
                if(junction->name == Junction_Matrix[i]->name)
                {
                    for(int j = 0 ; j < Junction_Matrix.size() ; j++)
                    {
                        Road *temp = Road_Matrix[i][j];
                        if(temp != nullptr)
                        {
                            return true;
                        }
                    }
                }                    
            }

            return false;
        }

        // Returns junction from road matrix index
        Junction* get_junction(int index)
        {
            return Junction_Matrix[index];
        }

        // Add road between two junctions
        void add_road(Road* r)
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
                }
            }
        }

        // Extract jucntion index
        int get_index(const string &name)
        {
            for(int i = 0 ; i < Junction_Matrix.size() ; i++)
            {
                if(Junction_Matrix[i]->name == name)
                {
                    return i;
                }
            }
            return -1;
        }




        void display_junctions() 
        {
            if(num_of_junctions < 10)
            {
                // Rows and columns to display in 2d space
                const int max_rows = num_of_junctions;
                const int max_cols = num_of_junctions;
                const int cell_width = 12;

                // Print top border
                cout << "+" << string((cell_width + 1) * max_cols, '-') << "+\n";

                // Nested for for 2d 
                // Second for to print the 3 line cell
                for (int row = 0; row < max_rows; row++) 
                {
                    for (int line = 0; line < 3; line++) 
                    {
                        cout << "|";

                        for (int col = 0; col < max_cols; col++) 
                        {
                            string cell_content = "";      // Default blank content
                            string color_code = "\033[0m"; // Default color (reset)

                            bool junction_exists = false;

                            // Find the junction at the current coordinate
                            for (auto& temp : Junction_Matrix) {
                                if (temp->r == row && temp->c == col) 
                                {

                                    junction_exists = true;

                                    if (line == 1) // Middle line for junction name
                                    { 
                                        cell_content = temp->name;

                                        // Check if the junction has any connected roads
                                        bool has_connected_road = false;


                                        // Iterate Road Matrix and if the roads start or end junction name matches, a road exists connected to junction
                                        for (const auto& road_row : Road_Matrix) 
                                        {
                                            for (const auto& road : road_row) 
                                            {
                                                if (road != nullptr && (road->start_junction == temp->name || road->end_junction == temp->name)) 
                                                {
                                                    has_connected_road = true;
                                                    break;
                                                }
                                            }
                                            // Once a road is found , exit loop
                                            if (has_connected_road) 
                                            {
                                                break;
                                            }
                                        }

                                        // Assign color based on traffic count
                                        if (has_connected_road) 
                                        {
                                            if(temp->conjestion < 50)
                                            {
                                                color_code = "\033[32m";
                                            }
                                            else if(temp->conjestion < 80)
                                            {
                                                color_code = "\033[33m";
                                            } 
                                            else
                                            {
                                                color_code = "\033[31m";
                                            } 
                                        }
                                    } 

                                    // Line for vehicle count
                                    else if (line == 2) 
                                    { 
                                        cell_content = "Veh: " + temp->get_veh_count();
                                    }
                                    break;
                                }
                            }

                            // If no junction exists, display "Empty" in the middle line
                            if (!junction_exists && line == 1) 
                            {
                                cell_content = "Empty";
                            }

                            // Format and print cell content
                            int padding = (cell_width - cell_content.size()) / 2;
                            cout << string(padding, ' ') << color_code << cell_content
                                 << "\033[0m" // Reset color after content
                                 << string(cell_width - padding - cell_content.size(), ' ') << "|";
                        }
                        cout << "\n";
                    }
                    // Print row separator
                    cout << "+" << string((cell_width + 1) * max_cols, '-') << "+\n";
                }
            }
            else
            {
                // Rows and columns to display junctions in a simple 2D array
                const int max_rows = num_of_junctions;
                const int max_cols = num_of_junctions;

                // Nested loop for 2D grid visualization
                for (int row = 0; row < max_rows; ++row)
                {
                    for (int col = 0; col < max_cols; ++col)
                    {
                        string junction_name = "";
                        string color_code = "\033[0m"; // Default color reset

                        // Check if a junction exists at the current grid cell
                        for (const auto &junction : Junction_Matrix)
                        {
                            if (junction->r == row && junction->c == col)
                            {
                                junction_name = junction->name;

                                // Assign color based on congestion level
                                if (junction->conjestion < 50)
                                {
                                    color_code = "\033[32m"; // Green
                                }
                                else if (junction->conjestion < 80)
                                {
                                    color_code = "\033[33m"; // Yellow
                                }
                                else
                                {
                                    color_code = "\033[31m"; // Red
                                }
                                break;
                            }
                        }

                        // Print junction name or "Empty" if no junction exists
                        if (!junction_name.empty())
                        {
                            cout << color_code << setw(10) << left << junction_name << "\033[0m"; // Reset color
                        }
                        else
                        {
                            cout << setw(10) << left << "Empty";
                        }
                    }
                    cout << endl; // Newline after each row
                }
            }
        }




        // Display the road map with road details
        void display_road_map()
        {
            cout << "\nRoad Map:\n";
            cout << "Start Junction\tEnd Junction\tRoad Name\tDirection\n";

            // Iterate through all roads
            for (size_t i = 0 ; i < Road_Matrix.size() ; i++)
            {
                for (size_t j = 0 ; j < Road_Matrix[i].size() ; j++)
                {
                    Road* road = Road_Matrix[i][j];
                    if (road != nullptr)
                    {
                        Road* temp = road;
                        string color_code;

                        // Color code according to conjestion
                        if(temp->conjestion < 50)
                        {
                            color_code = "\033[32m";
                        }
                        else if(temp->conjestion < 80)
                        {
                            color_code = "\033[33m";
                        } 
                        else
                        {
                            color_code = "\033[31m";
                        } 

                        if (Road_Matrix[j][i] == nullptr)
                        {
                            // One-way road
                            Junction * temp_1 = Junction_Matrix[i];
                            Junction * temp_2 = Junction_Matrix[j];

                            cout << color_code << setw(18) << left << temp_1->name
                                 << setw(18) << left << temp_2->name
                                 << setw(18) << left << road->name
                                 << setw(8) << left << "→"
                                 << setw(12) << right << "Conjestion : " << road->conjestion
                                 << setw(12) << right << "Status : " << road->status << reset << endl;
                        }
                        else
                        {
                            // Bidirectional road
                            Junction * temp_1 = Junction_Matrix[i];
                            Junction * temp_2 = Junction_Matrix[j];

                            cout << color_code << setw(18) << left << temp_1->name
                                 << setw(18) << left << temp_2->name
                                 << setw(18) << left << road->name
                                 << setw(8) << left << "↔"
                                 << setw(12) << right << "Conjestion : " << road->conjestion
                                 << setw(12) << right << "Status : " << road->status << reset << endl;
                       }
                    }
                }
            }
        }

        // Display in 2d plane
        void display_road_map_1()
        {
            if(num_of_junctions < 7)
            {
                const int cellWidth = 30; // Width of each cell (for proper spacing)
                const int cellHeight = 3; // Height for each cell to print road info in 3 lines

                // Helper function to center text in a fixed-width cell
                auto centerText = [](const string& text, int width) -> string {
                    int padding = width - text.length();
                    if (padding <= 0) return text.substr(0, width); // Truncate if text is too long
                    int leftPadding = padding / 2;
                    int rightPadding = padding - leftPadding;
                    return string(leftPadding, ' ') + text + string(rightPadding, ' ');
                };

                // Print the top border
                cout << "+";
                for (int j = 0; j < num_of_junctions; ++j)
                {
                    cout << setw(cellWidth) << setfill('-') << "" << setfill(' ') << "+";
                }
                cout << endl;

                // For each row of junctions, display road information in the cells
                for (int i = 0; i < num_of_junctions; ++i)
                {
                    for (int r = 0; r < cellHeight; ++r)
                    {
                        for (int j = 0; j < num_of_junctions; ++j)
                        {
                            cout << "|"; // Start border of each cell
                            if (Road_Matrix[i][j] != nullptr)
                            {
                                // Print road details inside the cell
                                if (r == 0)
                                {
                                    if(Road_Matrix[i][j]->conjestion < 50)
                                    {
                                        cout << green << centerText(Road_Matrix[i][j]->name, cellWidth) << reset; // Road name
                                    }
                                    else if(Road_Matrix[i][j]->conjestion < 80)
                                    {
                                        cout << yellow << centerText(Road_Matrix[i][j]->name, cellWidth) << reset; // Road name
                                    }
                                    else
                                    {
                                        cout << red << centerText(Road_Matrix[i][j]->name, cellWidth) << reset; // Road name
                                    }
                                }
                                else if (r == 1)
                                    cout << centerText("Count: " + to_string(Road_Matrix[i][j]->veh_count), cellWidth);
                                else if (r == 2)
                                    cout << centerText("Distance: " + to_string(Road_Matrix[i][j]->distance), cellWidth);
                            }
                            else
                            {
                                // Print "Empty" for cells with no road
                                if (r == 0)
                                    cout << centerText("Empty", cellWidth);
                                else
                                    cout << string(cellWidth, ' '); // Empty space for remaining lines
                            }
                            cout << "|"; // End border of each cell
                        }
                        cout << endl;
                    }

                    // Print the bottom border of the row
                    cout << "+";
                    for (int j = 0; j < num_of_junctions; ++j)
                    {
                        cout << setw(cellWidth) << setfill('-') << "" << setfill(' ') << "+";
                    }
                    cout << endl;

                    // Print the top border for the next row, except for the last one
                    if (i < num_of_junctions - 1) {
                        cout << "+";
                        for (int j = 0; j < num_of_junctions; ++j)
                        {
                            cout << setw(cellWidth) << setfill('-') << "" << setfill(' ') << "+";
                        }
                        cout << endl;
                    }
                }
            }
        }


        void display_map()
        {
            cout << endl;
            display_junctions();
            display_road_map();
        }


};



#endif
