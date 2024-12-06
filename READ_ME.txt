1. Vehicle.h -> Uses hashmap
2. Road.cpp -> Includes vehicle.h for roads , Includes Linked_List.h for vehcile storage 
3. Junction.cpp -> Includes vehicle.h for signals , Includes Linked_List.h for signals
4. Map.cpp -> Includes Road.cpp and Junction.cpp for maps , Includes Vector.h for map functionality

Data structures
1. Vector.h
    Vector , resize x 2 , operator[] , push_back , get_size , get_capacity , clear , empty 

2. Linked_List.h
    List , insert , remove , exists , print , ~List
    

---------------------------------------------------------------------------------------------------------------------------------

2d plane representing the map

Edge -> Road 
Vertice -> Junction

Each vertice has a priority queue for handling traffic light functionality

System can only have 1 road in a single connection eg A to B can only have 1 road

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
    Roads are added by taking r and c from the 1d array that stores junctions
    Road matrix is of size junction count x 2 to account for all the road paths

    Junctions:       Roads:(Null for no road) (Row index is starting junction and column index is ending junction)
    A (0,0)             A B C D
    B (0,1)          A
    C (1,0)          B
    D (1,1)          C
                     D


6. Linked_List.h

7. Vector.h
---------------------------------------------------------------------------------------------------------------------------------
To Implement :

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
    currently adding in simulation signals no manual override available

6. Check that the junction can exist before making it

7. Need to make custom data structures 





Linked_List
Graph using adjaceny matrix
Class with nodes
Hash map

Can implement sorting and array for showing vehicles at signal
Will implement File handling
Queue can be used at signals for priority queue
Recursion can be used in binary trees when showing sorted vehicles via id at signal
Can implement an array with sorting for priority vehicles in map to highlight them