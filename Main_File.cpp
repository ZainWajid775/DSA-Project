#include <iostream>
#include <thread>
#include <atomic>
#include <unistd.h>
#include <iomanip>
#include "Simulation.h"
#include "Map.h"
#include "File_Handling/File_Handling.h"

using namespace std;

vector<string> credentials = read_credentials();

int main() 
{

    // Initialize map with 4 junctions
    Map map("Temp" , 3);

    // Create roads
    Road r1("Road 1", 10, 10, "A", "B");
    Road r2("Road 2", 10, 10, "B", "C");

    // Create junctions
    Junction A("A", 0, 0, 10, 1);
    Junction B("B", 0, 1, 10, 1);
    Junction C("C", 1, 0, 10, 1);
    Junction D("D", 1, 1, 10, 1);

    // Add junctions and roads to the map
    map.add_junction(&A);
    map.add_junction(&B);
    map.add_junction(&C);
    map.add_junction(&D);
    map.add_road(&r1, true);
    map.add_road(&r2, false);

    //Vehicle v1("A" , "B" , 10);
    //Vehicle v2("A" , "B" , 10);
    //Vehicle v3("A" , "B" , 10);
//
    //A.add_vehicle(v1);
    //A.add_vehicle(v2);
    //A.add_vehicle(v3);
    //system("clear");
//
    //Map** map_container = new Map*[10];
    //store_map(&map);
    //map_container[0] = nullptr;
//
    //read_map("Temp" , map_container , 0); 
//
    //cout << "Read" << endl;
//
    //map_container[0]->display_map();

    std::cout << "__cplusplus: " << __cplusplus << std::endl;

}
