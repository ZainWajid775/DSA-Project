1. Vehicle.h -> Uses hashmap
2. Road.cpp -> Includes vehicle.h for roads , Includes Linked_List.h for vehcile storage 
3. Junction.cpp -> Includes vehicle.h for signals , Includes Linked_List.h for signals
4. Map.cpp -> Includes Road.cpp and Junction.cpp for maps , Includes Vector.h for map functionality

Data structures
1. Vector.h
    Vector , resize x 2 , operator[] , push_back , get_size , get_capacity , clear , empty 

2. Linked_List.h
    List , insert , remove , exists , print , ~List

3. Hashmap.h
    

---------------------------------------------------------------------------------------------------------------------------------

2d plane representing the map

Edge -> Road 
Vertice -> Junction

Each vertice has a priority queue for handling traffic light functionality

---------------------------------------------------------------------------------------------------------------------------------
Currently Using :

1. Road Structure 
    Stores road information and status

2. Junction Structure
    Stores junction information and implements signal functionlity using list

3. Vehicle Hashmap
    Stores all generated vehicles and ensure no duplicate ids are generated

4. Vehicle Structure
    Responsible for random vehicle generation and storing its information

5. Map
    Uses a sparse adjaceny matrix to create a map and ensure effecient memory usage , 1d vector for juntions and 2d for the roads

6. Linked_List.h

7. Hashmap.h

8. Vector.h
---------------------------------------------------------------------------------------------------------------------------------
To Implement :

1. Map 
    Will represent the map using spare adjaceny matrix
    Currently trying to print map

2. File handling

3. 2 modes of operation
    i. ) Simulation
    ii.) User Controlled Simulation

4. Vehicle Movement
    Update the vehicle
    Update the road
    Update the signal
    Update the junction
    Update the map

    For vehicle, in simulation mode, vehicle should move on its own after checking path is available
    For user controlled simulation, user should be able to input the vehicle id and move it manually while other vehicles move on their own

5. Signal 

6. Check that the junction can exist before making it

7. Need to make custom data structures 





Linked_List
Graph using adjaceny matrix
Class with nodes
Hash map (have to make custom)


Can implement sorting and array for showing vehicles at signal
Will implement File handling
Queue can be used at signals for priority queue
Recursion can be used in binary trees when showing sorted vehicles via id at signal
Can implement an array with sorting for priority vehicles in map to highlight them