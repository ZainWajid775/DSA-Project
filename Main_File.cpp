#include <iostream>
#include <pthread.h>
#include <chrono>
#include <iomanip>
#include <atomic>
#include "Map.h"
#include "Simulation.h"


using namespace std;

int main()
{
    Map map(2);

    Road r1("Road 1" , 10 , 10 , "A" , "B");
    Road r2("Road 2" , 10 , 10 , "B" , "C");

    Junction A("A" , 0 , 0 , 10 , 1);
    Junction B("B" , 0 , 1 , 10 , 1);
    Junction C("C" , 1 , 0 , 10 , 3);
    Junction D("D" , 1 , 1 , 10 , 1);

    map.add_junction(&A);
    map.add_junction(&B);
    map.add_junction(&C);
    map.add_junction(&D);

    map.add_road(&r1 , true);
    map.add_road(&r2 , true);

    Vehicle v1(999 , 100 , "A" , "B");
    Vehicle v2(998 , 100 , "A" , "B");
    A.add_vehicle(v1);
    A.add_vehicle(v2);
    B.add_vehicle(v1);
    B.add_vehicle(v2);
    C.add_vehicle(v1);
    C.add_vehicle(v2);
    
    r1.add_to_road(v1);
    r1.add_to_road(v2);

    start_simulation(&map);


}