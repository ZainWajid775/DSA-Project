#include <iostream>
#include <vector>
#include "Road.cpp"
#include "Junction.cpp"

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
        bool add_road(Road* r , string junction_1 ,string junction_2 , bool is_two_way)
        { 
            // Check if junctions exist and extract them
            bool j1_exists = false , j2_exists = false;
            int j1_index = -1 , j2_index = -1;

            for(int i = 0 ; i < Junction_Matrix.size() ; i++)
            {
                if(junction_1 == junction_1)
                {
                    j1_exists = true;
                    j1_index = i;
                }
                if(junction_2 == junction_2)
                {
                    j2_exists = true;
                    j2_index = i;
                }
            }

            if(j1_exists && j2_exists)
            {
                Road_Matrix[j1_index][j2_index] = r;

                if(is_two_way && j1_index)
                {
                    Road_Matrix[j2_index][j1_index] = r;
                }

                return true;
            }

            return false;
        }

        void display_roads()
        {
            for(int i = 0; i < Road_Matrix.size(); i++)
            {
                for(int j = 0; j < Road_Matrix[i].size(); j++)
                {
                    if(Road_Matrix[i][j] != nullptr)
                    {
                        Road* road = Road_Matrix[i][j];
                        cout << Road_Matrix[i][j]->name << " ";
                        cout << Road_Matrix[i][j]->veh_count << " ";
                        cout << Road_Matrix[i][j]->conjestion << " ";
                        cout << Road_Matrix[i][j]->status << " ";
                        
                        for(const auto& v : road->vehicles_on_road)
                        {
                            cout << v.id << " ";
                            cout << v.type << " ";
                            cout << v.priority << " ";
                        }
                        cout << endl;
                    }

                }
                cout << endl;
            }
        }

};


int main()
{
    Map map(2);

    Road temp("Broadway" , 100 , 1);
    Road* ptr;
    ptr = &temp;

    Junction j1("Avenue" , 0 , 0 , 10);
    Junction j2("Avenue2" , 0 , 1 , 10);

    map.add_junction(j1);
    map.add_junction(j2);
    map.add_road(ptr , "Avenue" , "Avenue2" , false);   


    Vehicle v("Avenue" , "Avenue2");

    temp.add_to_road(v);
    map.display_roads();




}