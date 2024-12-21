#include <iostream>
#include <cstdlib>
#include <algorithm>    
#include <csignal>

#include "Map.h" 
#include "Simulation.h"
#include "File_Handling/File_Handling.h"

#include "Data_Structures/Binary_Search_Tree.h"
#include "Data_Structures/Stack.h"
#include "Data_Structures/Queue.h"
#include "User_Interface.h"


using namespace std;

// Store current programs name
// Used to restart the program in case of a segmentation fault
const char* program_name;


// Map container
vector <Map*> map_container;

// Used to handle any segmentation faults
// Receivers signal number 
void signal_handler(int signum) 
{
    cout << endl << RED << "Caught signal " << signum << " , causing segmentation fault!" << RESET << endl;

    enter_to_continue();

    cout << RED << "Restarting program..." << RESET << endl;
    wait(1);

    // Restart the program by executing the same executable again using execl
    // Program is passed as a parameter to the new process 
    // Char null marks end of argumen
    if (execl(program_name , program_name , (char*)NULL) == -1) 
    {
        std::cerr << "Error restarting program: " << strerror(errno) << std::endl;

        // Incase restarting fails
        exit(signum);
    }
}

//Function to convert string to lowercase
string to_lower(string& s)
{
    string result;
    for (char c : s) 
    {
        result += tolower(c);
    }
    return result;
}

// Get credential
string get_cred(string cred)
{
    string input;

    // Keep looping until input is not empty
    while(input == "")
    {
        cout << YELLOW << cred << " : " << RESET;
        getline(cin , input);

        if(input == "")
        {
            cout << RED  << cred << " cannot be empty !" RESET << endl;
        }
    } 

    return input; 
}

// Checks if map container has a matching name
bool has_name(const string& name)
{
    for(int i = 0 ; i < map_container.size() ; i++)
    {
        if (map_container[i]->map_name == name)
        {
            return true;
        }
    }
    return false;
}

// Parameters : Number of arguments(if any) and name of the programs
int main(int argc , char* argv[]) 
{   
    // Store current programs name
    program_name = argv[0];

    // A signal handler for segmentation faults
    // Trigger the handler for segmentation fault
    signal(SIGSEGV, signal_handler);

    try
    {
        // Bool var to exit program
        bool exit = false;
    
        // Stores user accounts
        vector<string> accounts;
    
        // Initial start up
        system("clear");
        line("Login");
        cout << endl;

        // Read all accounts from accounts text
        try 
        {
            accounts = read_credentials();
        }
        catch(const std::exception& e)
        {
            std::cerr << RED "ERROR : " << e.what() << RESET << '\n';
            enter_to_continue();
        }
    
        // Checks if login was successful
        bool login = false;
    
        // Get user credentials
        if(accounts.size() > 0)
        {        
            while(!login)
            {
            
                system("clear");
                line("Login");
                cout << endl;
    
                // Stored entered credentials
                string username , password;
                username = get_cred("Username");          
                password = get_cred("Password");
    
                // Check if user exists
                for(auto it = accounts.begin() ; it != accounts.end() ; it++)
                {
                    string temp = *it;
                    if(temp == username + "|" + password)
                    {
                        cout << endl;
                        cout << GREEN "Login Successful !" RESET << endl;
                        wait(1);
                        login = true;
                        break;
                    }
                    else if(it == accounts.end() - 1)
                    {
                        cout << endl;
                        cout << RED "Invalid Credentials !" RESET << endl;
                        enter_to_continue();
                    }
                }
            }
        }
        else
        {
            // If file was not read, user has to create a new account
            cout << endl;
            system("clear");
            line("Account Creation");
    
            // Store the new account
            string new_username , new_password;
    
            cout << endl;
            cout << YELLOW "Please create a new account to proceed" RESET << endl;
            new_username = get_cred("Username");
            new_password = get_cred("Password");
    
            // Add account to holder
            accounts.push_back(new_username + "|" + new_password);
    
            // Attempt to save new account
            try
            {
                store_credentials(accounts);
                cout << endl;
                cout << GREEN "Account created successfully !" RESET << endl;
                enter_to_continue();
            }
            catch(const std::exception& e)
            {
                std::cerr << RED "ERROR : " << e.what() << RESET << '\n';
                enter_to_continue();
    
                cout << RED << "The system cannot verify you. Please restart the system and try again." << RESET << '\n';
                exit = true;
            }   
    
        }
    
        // Load all map data
        system("clear");
        line("Loading Maps");
        cout << endl;
    
        // Read all maps
        try
        {
            map_container = read_maps();
        }
        // If maps cannot be loaded, proceed to main menu
        catch(const std::exception& e)
        {
            std::cerr << RED "ERROR : " << e.what() << RESET << '\n';
            cout << YELLOW << "Please try resolving the conflict and restart the system or add a new map." RESET << '\n';
            enter_to_continue();
        }
    
        // Notify user if no maps are available
        if(map_container.empty())
        {
            cout << YELLOW << "No maps found in save files." << endl;
            cout << "Map container is empty." RESET << endl;
            enter_to_continue();
        }

        // Store user input from main menu
        string menu_option;
    
        // Main menu
        while(!exit)
        {   
        
            system("clear");
            line("Main Menu");
            cout << endl;

            // Main menu options
            cout << RED "1. View Maps" << endl;
            cout << YELLOW "2. Create Map" << endl;
            cout << GREEN "3. Delete Map" << endl;
            cout << BLUE "4. Simulation" << endl;
            cout << MAGENTA "5. Add a user" << endl;
            cout << RED "6. Remove a user" << endl;
            cout << YELLOW "7. BST Tree Map sorting" << endl;
            cout << GREEN << "8. Queue vehicle sorting" << endl;
            cout << BLUE "0. Exit" RESET << endl << endl;
            
            cout << YELLOW "Option : " << RESET;
            cin >> menu_option;
            
            // View maps
            if(menu_option == "1")
            {   
                // Used to clear the input buffer to avoid issues with misinput and the program running by itself
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
                // Check if there are any maps to show
                if(map_container.empty())
                {
                    system("clear");
                    line("Map Viewer");
                    cout << endl;
                    cout << YELLOW << "No maps stored in system." << RESET << '\n';
                    enter_to_continue();
    
                    cout << GREEN "Exiting to main menu..." RESET << endl;
                    wait(1);
                }
                else
                {
                    // Exit from this point
                    bool local_exit = false;

                    while(!local_exit)
                    {
                    
                        // Show options 
                        system("clear");
                        line("Map Viewer");
                        cout << endl;
                        string map_option;
                        
                        cout << YELLOW << "Select a map to view by name" << RESET << '\n';
                        cout << endl;
    
                        for(int i = 0 ; i < map_container.size() ; i++)
                        {
                            cout << GREEN << i + 1 << ". " << map_container[i]->map_name << '\n';
                        }
    
                        cout << endl;
                        cout << YELLOW "Enter 0 to Exit" << endl << endl;
                        cout << "Option : " << RESET;
                        getline(cin , map_option);
    
                        if(map_option == "0")
                        {
                            cout << GREEN << "Exiting to main menu..." << RESET << endl;
                            wait(1);
    
                            local_exit = true;
                        }
                        else
                        {
                            // Check if map name is valid
                            for(auto& map : map_container)
                            {
                                if(map->map_name == map_option)
                                {
                                    system("clear");
                                    line("Map Viewer");
                                    cout << endl << endl;
    
                                    cout << MAGENTA << map->map_name << RESET << endl << endl;
                                    map->display_junctions();
                                    cout << endl;
                                    map->display_road_map_1();
                                    cout << endl;
                                    map->display_road_map();
                                    cout << endl;
    
                                    enter_to_continue();
    
                                    cout << GREEN << "Exiting to main menu..." << RESET << endl;
                                    wait(1);
    
                                    local_exit = true;
    
                                    break;
                                }
                            }   
    
                            if(!local_exit)
                            {
                                cout << RED << "Invalid map name" << RESET << endl;
                                enter_to_continue();
                            }
                        }
                    }
                }
            }
    
            // Create a new map
            else if (menu_option == "2")
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // Create a new map
                system("clear");
                line("Map Creator");
                cout << endl;

                // Variables to store map details
                string m_name;
                int m_junctions;
    
                bool name = false , junction = false;
    
                while(!name)
                {
                    cout << YELLOW << "Enter the name of the map : " << RESET;
                    getline(cin , m_name);
                    cout << endl;
    
                    if(m_name == "")
                    {
                        cout << RED << "Map name cannot be blank !" << RESET << endl;
                        enter_to_continue();
                    }
                    else if(has_name(m_name))
                    {
                        cout << RED << "Map name already exists !" << RESET << endl;
                        enter_to_continue();
                    }
                    else
                    {
                        name = true;
                    }
                }
    
                while(!junction)
                {
                    cout << YELLOW << "Enter the number of junctions : " << RESET;
                    cin >> m_junctions;
                    cout << endl;
    
                    if(m_junctions < 2)
                    {
                        cout << RED << "Map cannot have less than 2 junctions !" << RESET << endl;
                        enter_to_continue();
                    }
                    else
                    {
                        junction = true;
                    }
                }
    
                cout << GREEN "Loading Junction Creator..." << RESET << endl;
                wait(1);
    
                // Create a new map
                Map* new_map = new Map(m_name , m_junctions);

                // Get map details
                {
                    line("Map Editor");
                    system("clear");
                    cout << endl;
                    
                    bool back_out_j = false;
                    int j_count = 0;
    
                    // Create junctions
                    while(j_count != m_junctions && !back_out_j)
                    {
                        // Bools to check if entered data is correct
                        bool c1 = false , c2 = false , c3 = false , c4 = false;
                        string j_name , j_row , j_column , j_capacity;
    
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
                        system("clear");
                        line("Map Editor");
                        cout << endl;
    
                        while(!c1)
                        {
                            cout << YELLOW << "Enter the name of the junction : " << RESET;
                            getline(cin , j_name);
                            cout << endl;
    
                            if(j_name == "")
                            {
                                cout << RED << "Junction name cannot be empty !" << RESET << endl;
                                enter_to_continue();
                            }
                            else if(new_map->has_junction(j_name))
                            {
                                cout << RED << "Junction name already exists !" << RESET << endl;
                                enter_to_continue();
                            }
                            else
                            {
                                c1 = true;
                            }
                        }
    
                        while(!c2 || !c3)
                        {
                            cout << YELLOW << "Enter the row index of the junction : " << RESET;
                            cin >> j_row;
                            cout << endl;
    
                            cout << YELLOW << "Enter the column index of the junction : " << RESET;
                            cin >> j_column;
                            cout << endl;
    
                            if(stoi(j_row) > m_junctions - 1 || stoi(j_row) < 0)
                            {
                                cout << RED << "Invalid row index !" << RESET << endl;
                                enter_to_continue();
                            }
                            else
                            {
                                c2 = true;
                            }
                            
                            if(stoi(j_column) > m_junctions - 1 || stoi(j_column) < 0)
                            {
                                cout << RED << "Invalid column index !" << RESET << endl;
                                enter_to_continue();
                            }
                            else if(new_map->is_index_clear(stoi(j_row) , stoi(j_column)))
                            {
                                cout << RED << "Junction already exists at this index !" << RESET << endl;
                                enter_to_continue();
                            }
                            // Only verified if the junction is not already present and the row and column are valid
                            else
                            {
                                c3 = true;
                            }
                        }
    
                        while(!c4)
                        {
                            cout << GREEN << "It is recommended to have a capacity higher than 5 to simulate correct behaviour" << RESET << endl;
                            cout << YELLOW << "Enter the junctions vehicle capacity : " << RESET;
                            cin >> j_capacity;
                            cout << endl;
    
                            if(stoi(j_capacity) < 1)
                            {
                                cout << RED << "Invalid capacity !" << RESET << endl;
                                enter_to_continue();
                            }
                            else
                            {
                                c4 = true;
                            }
                        }
    
                        // Create and add junction
                        Junction *new_junction = new Junction(j_name , stoi(j_row) , stoi(j_column) , stoi(j_capacity));
                        new_map->add_junction(new_junction);
    
                        // Check if user wants to go back
                        cout << GREEN << "Junction added to map" << RESET << endl << endl;
                        j_count++;
    
                        new_map->display_junctions();
                        cout << endl;
                        cout << YELLOW << "Junction map is only a visual aid !!!" << endl;

                        // Map must have a minimum of 2 junctions
                        if(j_count == 1)
                        {
                            cout << endl;
                            cout << YELLOW << "You have added 1 junction, only. Please add another to make the map valid." RESET << endl;
                            enter_to_continue();
                        }
                        else if(j_count == m_junctions)
                        {
                            cout << endl;
                            cout << YELLOW << "Maximum number of junctions added." << endl;
                            enter_to_continue();
                            back_out_j = true;
                            wait(1);
                        }                
                        else if(j_count != m_junctions)
                        {
                            cout << endl;
                            cout << "Available slots : " << m_junctions - j_count << endl << endl;
                            cout << YELLOW << "Do you want to add another junction ? (y / n to exit) : " << RESET;
                            string choice;
                            cin >> choice;
                            if(to_lower(choice) == "n")
                            {
                                back_out_j = true;
                            }
                        }
                        
                    }
    
                    cout << GREEN "Loading Road Creator..." RESET << endl;
                    wait(1);
    
                    // Create roads
                    bool back_out_r = false;
                    int r_count = 0;

                    while(!back_out_r)
                    {
                        string r_name , r_distance , r_capacity , r_start , r_end;
                        bool c1 = false , c2 = false , c3 = false , c4 = false;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
                        system("clear");
                        line("Map Editor");
                        cout << endl;
    
                        while(!c1)
                        {
                            cout << YELLOW << "Enter the name of the road : " << RESET;
                            cin >> r_name;
                            cout << endl;
    
                            if(r_name == "")
                            {
                                cout << RED << "Road name cannot be empty !" << RESET << endl;
                                enter_to_continue();
                            }
                            else if(new_map->has_road(r_name))
                            {
                                cout << RED << "Road already exists !" << RESET << endl;
                                enter_to_continue();
                            }
                            else
                            {
                                c1 = true;
                            }
                        }
    
                        while(!c2)
                        {
                            cout << YELLOW << "Enter the distance of the road : " << RESET;
                            cin >> r_distance;
                            cout << endl;
    
                            if(stof(r_distance) < 1)
                            {
                                cout << RED << "Invalid distance !" << RESET << endl;
                                enter_to_continue();
                            }
                            else
                            {
                                c2 = true;
                            }
                        }
    
                        while(!c3)
                        {
                            cout << GREEN << "It is recommended to have a capacity higher than 5 to simulate correct behaviour" << RESET << endl;
                            cout << YELLOW << "Enter the capacity of the road : " << RESET;
                            cin >> r_capacity;
                            cout << endl;
    
                            if(stoi(r_capacity) < 1)
                            {
                                cout << RED << "Invalid capacity !" << RESET << endl;
                                enter_to_continue();
                            }
                            else
                            {
                                c3 = true;
                            }
                        }
                        
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
                        while(!c4)
                        {
                            system("clear");
                            line("Map Creator");
                            cout << endl;
                            
                            new_map->display_junctions();
    
                            cout << endl;
                            cout << YELLOW << "Row represents starting junction and column represents ending junction" << endl << endl;
    
                            cout << YELLOW << "Enter the roads starting junction : " << RESET << endl;
                            getline(cin , r_start); 
                            cout << endl;
    
                            cout << YELLOW << "Enter the roads ending junction : " << RESET << endl;
                            getline(cin , r_end);
                            cout << endl;
    
                            int check_row = new_map->get_index(r_start);
                            int check_column = new_map->get_index(r_end);
    
    
                            // Check both junction exist
                            if(check_row == -1 || check_column == -1)
                            {
                                cout << RED << "Junction not found !" RESET << endl;
                                enter_to_continue();
                            }
                            // Check it is not a self loop
                            else if(check_row == check_column)
                            {
                                cout << RED << "Self loops not supported !" << RESET << endl;
                                enter_to_continue();
                            }
                            // Check the road doesnt already exist
                            else if(new_map->has_road(check_row , check_column))
                            {   
                                cout << RED << "Road already exists !" << RESET << endl;
                                enter_to_continue();
                            
                            }
                            else
                            {
                                c4 = true;
                            }
    
                            // Create and add road
                            Road *new_road = new Road(r_name , stof(r_distance) , stoi(r_capacity) , r_start , r_end);
                            new_map->add_road(new_road);
    
                        }
                        // Add road to map
                        Road* new_road = new Road(r_name , stof(r_distance) , stoi(r_capacity) , r_start , r_end);
                        new_map->add_road(new_road);
                        r_count++;
    
                        // Check if user wants to go back
                        system("clear");
                        line("Map Creator");
                        cout << endl;
    
                        cout << GREEN << "Road added to map" << RESET << endl;
    
    
                        if(r_count  == (j_count * (j_count - 1)))
                        {
                            cout << YELLOW "Maximum number of roads added to map" RESET << endl;
                            enter_to_continue();
                            back_out_r = true;
                        }
                        else
                        {
                            cout << YELLOW << "Do you want to add another Road ? (y / n to exit) : " << RESET;
                            string choice;
                            cin >> choice;
                            if(to_lower(choice) == "n")
                            {
                                cout << GREEN << "Saving Changes..." << RESET << endl;
                                wait(1);
                                back_out_r = true;
                            }
                        }
    
                    }
    
    
                }
                
                // Add map to container
                map_container.push_back(new_map);
    
                // Save map
                system("clear");
                line("Map Creator");
                cout << endl;

                try 
                {
                    store_map_container(map_container);
                    cout << GREEN << "Map Created and saved successfully !" << RESET << endl;
                    enter_to_continue();
                }
                catch(const std::exception& e)
                {
                    std::cerr << RED "ERROR : " << e.what() << RESET << '\n';
                    cout << YELLOW << "Please try resolving the conflict and restart the system or add a new map." RESET << '\n';
                    enter_to_continue();
                }
    
                cout << GREEN "Exiting to main menu..." << RESET << endl;
                wait(1);
            }
    
            // Delete a map
            else if(menu_option == "3")
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
                system("clear");
                line("Maps Editor");
                cout << endl;
    
                // Print all available maps
                string del_option;
    
                while(del_option != "0")
                {
                    system("clear");
                    line("Maps Editor");
                    cout << endl;
    
                    // Check if there are any maps to show
                    if(map_container.size() != 0)
                    {
                        cout << YELLOW << "Select a map to delete" << RESET << endl;
                        cout << endl;
    
                        for(int i = 0; i < map_container.size(); i++)
                        {
                            cout << BLUE << i + 1 << ". " << map_container[i]->map_name << endl;
                        }
    
                        cout << endl;
                        cout << YELLOW << "Enter the name of the map to delete (CASE SENSITIVE)." << endl;
                        cout << "Enter '0' to go back to the main menu." RESET << endl;
                        cout << GREEN "Type here : " RESET;
                        getline(cin , del_option);
                        cout << endl;
    
                        if(del_option == "")
                        {
                            cout << RED "Invalid map name"  << endl;
                            cout << YELLOW "Please enter a valid map. (CASE SENSITIVE)" RESET << endl;
                            enter_to_continue();
                        }
                        else if(del_option == "0")
                        {
                            cout << GREEN "Exiting to main menu..." RESET << endl;
                            wait(1);
                        }
                        else
                        {
                            for(auto& map : map_container)
                            {   
                                // Get confirmation to delete the map or back out
                                if(map->map_name == del_option)
                                {
                                
                                    system("clear");
                                    line("Maps Editor");
                                    cout << endl;
                                    string confirmation;
                                    cout << YELLOW "Are you sure you want to delete : " << del_option << " ?" << endl;
                                    cout << MAGENTA << "This action is irreversible and the deleted map cannot be recovered." << endl;
                                    cout << YELLOW << "Type "<< GREEN "'confirm'" YELLOW << " to delete the map or anything else to back out : " RESET << endl;
                                    cout << GREEN "Type here : " RESET;
                                    getline(cin , confirmation);
                                    cout << endl;
    
                                    system("clear");
                                    line("Maps Editor");
                                    cout << endl;
    
                                    if(to_lower(confirmation) == "confirm")
                                    {
                                        // Remove map from container
                                        auto it = remove_if(map_container.begin() , map_container.end() , [&](Map* obj)
                                        {
                                            if(del_option == obj->map_name)
                                            {
                                                delete obj;
                                                return true;
                                            }
                                            return false;
                                        }
    
                                        );
    
                                        map_container.erase(it , map_container.end());
                                        try
                                        {
                                            store_map_container(map_container);
                                        }
                                        catch(const std::exception& e)
                                        {
                                            std::cerr << RED "ERROR : " << e.what() << RESET << '\n';
                                            cout << YELLOW << "Please try resolving the conflict, map deletion error !" RESET << '\n';
                                            enter_to_continue();
                                        }
    
                                        cout << YELLOW "Map successfully deleted." RESET << endl;
                                        enter_to_continue();
    
                                    }
                                    else
                                    {
                                        cout << YELLOW << "Map deletion cancelled." << RESET << endl;
                                        enter_to_continue();
                                    }
                                }
    
                            }
    
                            cout << RED "Invalid map name"  << endl;
                            cout << YELLOW "Please enter a valid map. (CASE SENSITIVE)" RESET << endl;
                            enter_to_continue();
                        }
                    }
                    // Case the container is empty
                    else
                    {
                        cout << YELLOW "There are no maps to show."<< endl;
                        cout << "Please add a map from the map creater" RESET << endl;
                        enter_to_continue();
                        del_option  = "0";
                    
                    }
                }
    
    
                
            }
    
            // Simulation
            else if(menu_option == "4")
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    
                if(map_container.size() != 0)
                {   
                    bool map_chosen = false;
                    string user_chosen_map;
                    Map* simulate_map = nullptr;
    
                    while(!map_chosen)
                    {
                        system("clear");
                        line("Simulation Control");
                        cout << endl << endl;
    
                        cout << YELLOW "Please chose a map from the following" << RESET << endl << endl;
    
                        int index = 1;
                        for(auto& map : map_container)
                        {
                            cout << BLUE << index << ". " << map->map_name << endl;
                            index++;
                        }
    
                        cout << endl;
                        cout << YELLOW << "Please enter the name of the map (CASE SENSITIVE) you would like to use or '0' to back out." << RESET << endl;
                        cout << YELLOW << "Type here : " << RESET;
                        cin >> user_chosen_map;
                        cout << endl;
    
                        if(user_chosen_map == "0")
                        {
                            cout << GREEN << "Exiting to main menu..." << RESET << endl;
                            wait(1);
                            break;
                        }
    
                        for(auto& map : map_container)
                        {
                            if(map->map_name == user_chosen_map)
                            {
                                simulate_map = map;
                                map_chosen = true;
                                break;
                            }
                        }
    
                        if(simulate_map == nullptr && user_chosen_map != "0")
                        {
                            cout << RED << "Invalid map name, please try again." << RESET << endl;
                            enter_to_continue();
                            cout << endl;
                        }
                        else
                        {
                            system("clear");
                            line("Simulation Control");
                            cout << endl << endl;                        
    
                            // Variables for vehicles
                            int max_vehicles = simulate_map->max_vehicles();
                            int user_vehicles;
                            bool valid_veh_count = false;
    
                            // Variables for iterations
                            int user_iterations;
                            int valid_iterations = false;
    
                            while(!valid_veh_count)
                            {
                                system("clear");
                                line("Simulation Control");
                                cout << endl << endl;
    
                                cout << MAGENTA "Guide :" << endl << endl;
                                cout << "1. An iteration is an attempt of each vehicle to move." << endl;
                                cout << "2. After the simulation is complete , system removes all the vehicles from the map." << endl;
                                cout << "3. No duplicate vehicle ID can be generated." << endl;
                                cout << "4. Vehicle movement will be random." << endl;
                                cout << "5. Vehicles will move to the least conjested road or junction depending on options." << endl;
                                cout << "6. Vehicles start moving from the junctions." << endl;
                                cout << "7. The system cannot handle cases where all the structures are filled (No movement in this case)." << endl;
                                cout << endl;
    
    
                                cout << YELLOW << "Maximum number of vehicles : " << max_vehicles << endl;
                                cout << "Enter the number of vehicles to generate : " << RESET;
    
                                if(!(cin >> user_vehicles))
                                {
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
                                    cout << endl;
                                    cout << RED "Invalid number of vehicles." RESET << endl;
                                    enter_to_continue();
                                }
                                else if(user_vehicles < 1 || user_vehicles > max_vehicles) 
                                {
                                    cout << endl;
                                    cout << RED "Invalid number of vehicles." RESET << endl;
                                    enter_to_continue();
                                }
                                else
                                {
                                    cout << endl;
                                    cout << GREEN << "Loading simulator..." RESET << endl;
                                    valid_veh_count = true;
                                }
    
                            }
    
                            if(valid_veh_count)
                            {
                            
                                while(!valid_iterations)
                                {
                                    system("clear");
                                    line("Simulation Control");
                                    cout << endl << endl;
    
                                    cout << MAGENTA << "An iteration is completed when all vehicles on the map have had a turn." << endl;
                                    cout << YELLOW << "Enter the number of iterations to run for : ";
    
                                    if(!(cin >> user_iterations))
                                    {
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
                                        cout << endl;
                                        cout << RED "Invalid number of iterations." RESET << endl;
                                        enter_to_continue();
                                    }
                                    else if(user_vehicles < 1 || user_vehicles > max_vehicles) 
                                    {
                                        cout << endl;
                                        cout << RED "Invalid number of iterations." RESET << endl;
                                        enter_to_continue();
                                    }
                                    else
                                    {
                                        cout << endl;
                                        cout << GREEN << "Loading simulator..." RESET << endl;
                                        valid_iterations = true;
                                    }
                                }
    
                            }
    
                            if(valid_veh_count && valid_iterations)
                            {
                                system("clear");
                                line("Simulation");
                                cout << endl << endl;
    
                                // Generate vehicles
                                vector<Vehicle*> vehicle_container;
                                int generated_veh_count = 0;
                                      
                                // Iterate over junctions and create vehicles only if junction has road connections
                                while(generated_veh_count != user_vehicles)
                                {
                                    for(auto& junction : simulate_map->Junction_Matrix)
                                    {
                                        if(simulate_map->has_road_connection(junction))
                                        {   
                                            // Update the vehicles current index according to the junctions index in junction container
                                            Vehicle *temp = new Vehicle(simulate_map->get_index(junction->name)); 
                                            vehicle_container.push_back(temp);
    
                                            junction->add_vehicle(*temp);
    
                                            generated_veh_count++;
                                            
                                            // Break if all vehicles are generated
                                            if(generated_veh_count == user_vehicles)
                                            {
                                                break;
                                            }                                        
                                        }
                                    }
                                }
    
                                system("clear");
                                line("Simulation");
                                cout << endl << endl;
    
                                cout << YELLOW "Generated vehicles : " << generated_veh_count << RESET << endl << endl;
                                simulate_map->display_junctions();
                                cout << endl;
                                enter_to_continue();
    
                                int simulated_iterations = 0;
    
                                while(simulated_iterations < user_iterations)
                                {
                                
                                    system("clear");
                                    line("Junction to Road");   
                                    cout << endl << endl;
    
                                    // Start simulation
    
                                    // Stack to store vehicle movement information as they move
                                    Stack movement_info;
    
                                    // First cycle, move from junction to road
                                    for(auto junction : simulate_map->Junction_Matrix)
                                    {
                                        bool j_complete = false;
    
                                        while(!junction->is_empty() && !j_complete)
                                        {
                                            // Get vehicle in front of junction
                                            Vehicle veh_to_move  = junction->get_vehicle();
    
                                            // Move the vehicle if possible otherwise add it back to the junction in front
                                            if(move_vehicle_junction_to_road(*simulate_map , &veh_to_move))
                                            {   
                                                // Add the movement information to the stack if vehicle moved
                                                string movement = "Vehicle " + to_string(veh_to_move.id) + " moved from "  + junction->name;
                                                movement_info.push(movement);
                                            }
                                            else
                                            {
                                                junction->add_vehicle_front(veh_to_move);
                                                j_complete = true;
                                            }
                                        }
                                    }
    
                                    simulated_iterations++;
    
                                    // Display updated map and movement information
                                    cout << MAGENTA "Iteration : " << simulated_iterations << RESET << endl << endl;
                                    simulate_map->display_junctions();
                                    cout << endl;
                                    simulate_map->display_road_map();
                                    cout << endl;

                                    // If there are less than 7 junctions, only then user can see the block map
                                    simulate_map->display_road_map_1();
                                    cout << endl;
    
                                    int i_move_cycle_1 = 1;

                                    // Print movemnt information
                                    if(movement_info.is_empty())
                                    {
                                        cout << GREEN "No vehicles moved in this cycle" << RESET << endl;
                                    }
                                    else
                                    {
                                        while(!movement_info.is_empty())
                                        {
                                            cout << YELLOW << i_move_cycle_1++ << ". " << movement_info.pop() << endl;  
                                        }
                                    }
    
                                    cout << RESET << endl;
                                    enter_to_continue();
    
    
                                    // Second cycle move from road to junction
                                    system("clear");
                                    line("Road to Junction");
                                    cout << endl << endl;
    
                                    for(auto& row : simulate_map->Road_Matrix)
                                    {
                                        for(auto& road : row)
                                        {
                                            if(road != nullptr)
                                            {
                                                bool r_complete = false;
    
                                                while(!road->empty() && !r_complete)
                                                {
                                                    // Get vehicle in front
                                                    Vehicle veh_to_move = road->get_vehicle();
    
                                                    // Move vehicle if possible othewise add it back
                                                    if(move_vehicle_road_to_junction(*simulate_map , &veh_to_move))
                                                    {  
                                                        // Add movement information to stack if vehicle moved
                                                        string movement = "Vehicle " + to_string(veh_to_move.id) + " moved from "  + road->name;
                                                        movement_info.push(movement);
                                                    }
                                                    else
                                                    {
                                                        road->add_to_road(veh_to_move);
                                                        r_complete = true;
                                                    }
                                                }
                                            }
                                        }
                                    }
    
                                    simulated_iterations++;
    
                                    // Display updated map and movement information
                                    cout << MAGENTA "Iteration : " << simulated_iterations << RESET << endl << endl;
                                    simulate_map->display_junctions();
                                    cout << endl;
                                    simulate_map->display_road_map();
                                    cout << endl;

                                    // If there are less than 7 junctions, only then user can see the block map
                                    simulate_map->display_road_map_1();
                                    cout << endl;

                                    // Print movement information
                                    int i_move_cycle_2 = 1;
                                    if(movement_info.is_empty())
                                    {
                                        cout << GREEN "No vehicles moved in this cycle" << RESET << endl;
                                    }
                                    else
                                    {
                                        while(!movement_info.is_empty())
                                        {
                                            cout << YELLOW << i_move_cycle_2++ << ". " << movement_info.pop() << endl;  
                                        }
                                    }
    
                                    cout << RESET << endl;
                                    enter_to_continue();
                                }
    
    
                                // After simulation ends, delete the vehicle container and clean the map
                                system("clear");
                                line("Simulation Control");
                                cout << endl << endl;
    
                                // Clear junction
                                for(auto junction : simulate_map->Junction_Matrix) 
                                {
                                    if(!junction->is_empty())
                                    {
                                        junction->clear();
                                    }
                                }
    
                                // Clear roads
                                for(size_t i = 0 ; i < simulate_map->Road_Matrix.size() ; i++)
                                {
                                    for(size_t j = 0 ; j < simulate_map->Road_Matrix[i].size() ; j++)
                                    {
                                        Road* road = simulate_map->Road_Matrix[i][j];
    
                                        if(road != nullptr)
                                        {
                                            road->clear();
                                        }
                                    }
                                } 
    
                                cout << YELLOW << "Map Cleared" << endl << endl;
                                cout << GREEN << "Simulation complete" << RESET << endl;
                                enter_to_continue();
                            }   
                        }
                    }
    
                }
                else
                {
                
                    system("clear");
                    line("Simulation Control");
                    cout << endl << endl;
    
                    cout << YELLOW << "You have no maps in the database." << endl;
                    cout << "Please create a new map via the map creater." RESET << endl;
                    enter_to_continue();
    
                    cout << GREEN << "Exiting to main menu..." << endl;
                    wait(1);
                }
    
            }
    
            // Add user to database
            else if(menu_option == "5")
            {
                string new_username , new_password;
    
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                bool valid = false;

                // Loop until a valid username and password is entered
                while(!valid)
                {
                    system("clear");
                    line("User Database");
                    cout << endl << endl;
    
                    new_username = get_cred("New Username");
    
                    bool exists = false;
    
                    for (auto it = accounts.begin() ; it != accounts.end(); it++)
                    {
                        size_t pos = it->find('|');
                        string user = it->substr(0 , pos);
                        if(new_username == user)
                        {
                            exists = true;
                            break;
                        }
                    }

                    // Ensure no duplicate users are created
                    if(exists)
                    {
                        system("clear");
                        line("User Database");
                        cout << endl << endl;
    
                        cout << RED << "User already exists !" << RESET << endl;
                        cout << YELLOW << "Please enter a distinct user name" << RESET << endl;
                        cout << endl;
    
                        enter_to_continue();                    
                    }
                    else
                    {
                    
                        new_password = get_cred("New Password");
                        string new_user;
    
                        new_user = new_username + "|" + new_password;
    
                        try
                        {
                            accounts.push_back(new_user);
                            store_credentials(accounts);
                            cout << endl;
                            cout << GREEN << "New user successfully created." RESET << endl;
                            enter_to_continue();
                        }
                        catch(const std::exception& e)
                        {
                            std::cerr << RED "ERROR : " << e.what() << RESET << '\n';
                            cout << YELLOW << "Users file could not be updated." RESET << '\n';
                            enter_to_continue();
                        }
    
                        cout << GREEN << "Exiting to main menu..." RESET << endl;
                        wait(1);
                        valid = true;
                        
                    }
                }
                
            }
    
            // Delete user from database
            else if(menu_option == "6")
            {
            
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
                system("clear");
                line("User Database");
                cout << endl;
    
                if(accounts.size() > 0)
                {  
                    bool outer_exit = false;
    
                    while(!outer_exit)
                    {
                    
                        system("clear");
                        line("User Database");
                        cout << endl;
    
                        string del_user , del_password;      
    
                        int index = 1;
                        cout << YELLOW "Users in Database" << endl << endl;

                        // Print all usernames in file
                        for(auto& user : accounts)
                        {
                            size_t pos = user.find('|');
                            string result = user.substr(0 , pos);
    
                            cout << GREEN << index++ <<". " << result << endl;
                        }
    
                        cout << endl;
                        cout << YELLOW << "Please enter the username to delete." << endl;
                        cout << "Enter '0' to exit." << RESET << endl << endl;
    
                        del_user = get_cred("Username");

                        for (auto it = accounts.begin() ; it != accounts.end();)
                        { 
                            size_t pos = it->find('|');
                            string result = it->substr(0 , pos);
                            string temp = it->substr(pos + 1);

                            // Iterate over the accounts and delete the user if found
                            if(del_user == result)
                            {
                                bool local_exit = false;

                                // Enter the password to confirm deletion
                                while(!local_exit)
                                {
                                    system("clear");
                                    line("User Database");
                                    cout << endl;
    
                                    cout << YELLOW << "Enter password for user or '0' to exit." << RESET << endl;
                                    cout << YELLOW "Type here : " << RESET;
                                    getline(cin , del_password);
                                    cout << endl;
    
                                    if(del_password == temp)
                                    {
                                        cout << endl;
    
                                        try
                                        {
                                            it = accounts.erase(it);
                                            store_credentials(accounts);
                                            cout << GREEN << "User deleted" RESET << endl;
                                        }
                                        catch(const std::exception& e)
                                        {
                                            std::cerr << RED "ERROR : " << e.what() << RESET << '\n';
                                            cout << YELLOW << "Users file could not be updated." RESET << '\n';
                                            enter_to_continue();
                                        }
                                
                                        enter_to_continue();
                                        local_exit = true;
                                        continue;
    
                                    }
                                    else if(del_password == "0")
                                    {
                                        cout << endl;
                                        cout << GREEN << "Exiting..." RESET << endl;
                                        wait(1);
                                        local_exit = true;
                                    }                                
                                    else
                                    {
                                        cout << endl;
                                        cout << RED << "Invalid password" RESET << endl;
                                        enter_to_continue();
                                    }
                                }
    
                            }
                            // If user not found, continue iterating
                            else
                            {
                                ++it;
                            }
                        }
                        if(del_user == "0")
                        {
                            outer_exit = true;
                        }
                        else
                        {
                            cout << YELLOW << "User not found" RESET << endl;
                            cout << YELLOW << "Please enter a valid username" RESET << endl;
                            enter_to_continue();                        
                        }
    
                    }
                    
                }
                else
                {
                    cout << YELLOW << "No users stored in the database" RESET << endl;
                    cout << YELLOW << "Please create a new user" RESET << endl << endl;
                    enter_to_continue();
                }
    
                cout << GREEN << "Exiting to main menu..." RESET << endl;
                wait(1);
    
            }
    
            // AVL Tree
            else if(menu_option == "7")
            {
                if(map_container.size() != 0)
                {
                    // Create BST
                    B_Node* root = nullptr;

                    // Insert the number of junctions of each map in the container
                    for(auto& map : map_container)
                    {
                        root = insert(root , map->num_of_junctions);
                    }
    
                    system("clear");
                    line("BST");
                    cout << endl << endl;
    
                    cout << CYAN << "Sorting is based on number of junctions of map in the system " << endl << endl;
                    
                    cout << YELLOW << "Pre-order Traversal : ";
                    pre_order(root);
                    cout << endl;
    
                    cout << MAGENTA << "In-order Traversal : ";
                    in_order(root);
                    cout << endl;
    
                    cout << GREEN << "Post-order Traversal : ";
                    post_order(root);
                    cout << endl << endl;
    
    
                    enter_to_continue();
    
                    cout << GREEN << "Exiting to main menu..." RESET << endl;
                    wait(1);
                }
            }
    
            // Queue
            else if(menu_option == "8")
            {
                bool local_exit = false;
    
                while(!local_exit)
                {
                    int priority;
                    int q_size;
                    bool queue_fill = false;
                    bool size_valid = false;

                    // Loop until a valid size is entered
                    while(!size_valid)
                    {
                        system("clear");
                        line("Priority Queue");
                        cout << endl << endl;

                        cout << YELLOW << "Enter the number of vehicles to sort." << RESET << endl;
                        cout << YELLOW << "Enter '0' to exit." << RESET << endl << endl;
                        cout << YELLOW << "Type here : " << RESET;
    
                        if(!(cin >> q_size))
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
                            cout << endl;
                            cout << RED "Invalid size." RESET << endl;
                            enter_to_continue();
                        }
                        else if(q_size == 0)
                        {
                            cout << endl;
                            cout << GREEN << "Exiting to main menu..." RESET << endl;
                            wait(1);
    
                            local_exit = true;
                            break;
                        }
                        else if(q_size > 50 || q_size < 2)
                        {
                            cout << endl;
                            cout << RED "Invalid size." RESET << endl;
                            enter_to_continue();   
                        }                    
                        else
                        {
                            size_valid = true;
                        }
    
    
                    }

                    if(size_valid)
                    {
                        cout << endl;
                        cout << GREEN "Loading priority queue..." RESET << endl;
                        wait(1);
    
                        Circular_Queue priority_queue(q_size);
                        int v_count = 1;

                        // Loop until the queue is filled
                        while(!queue_fill)
                        {
                        
                            system("clear");
                            line("Priority Queue");
                            cout << endl << endl;
    
                            cout << YELLOW "You can add vehicles here and they will be sorted by priority" << endl;
                            cout << "The system has priority ranging from 0 to 100." << RESET << endl << endl;
    
                            cout << YELLOW "Enter the priority of vehicle " << v_count << " : " << RESET;
    
                            if(!(cin >> priority))
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
                                cout << endl;
                                cout << RED "Invalid option." RESET << endl;
                                enter_to_continue();
                            }
                            else if(priority < 0 || priority > 100)
                            {
                                cout << endl;
                                cout << RED "Invalid option." RESET << endl;
                                enter_to_continue();
                            }
                            else
                            {
                                priority_queue.push(priority);
                                v_count++;
    
                                if(v_count == q_size + 1)
                                {
                                    system("clear");
                                    line("Priority Queue");
                                    cout << endl << endl;   
    
                                    cout << GREEN << "Queue filled." RESET << endl;
    
                                    enter_to_continue();
                                    queue_fill = true;
                                }
                            }
    
                        }

                        // Merge sort the queue
                        priority_queue.sort();

                        // Print the queue with colour coding based on priority
                        system("clear");
                        line("Priority Queue");
                        cout << endl << endl;
    
                        cout << MAGENTA << "Priority Queue : ";
    
                        while(!priority_queue.is_empty())
                        {
                            int temp = priority_queue.pop();
                            string color_code;
    
                            if(temp > 75)
                            {
                                color_code = "\033[31m";
                            }
                            else if(temp > 45)
                            {
                                color_code = "\033[33m";
                            }
                            else
                            {
                                color_code = "\033[32m";
                            }
    
                            cout << color_code << temp << " ";
                        }
                        cout << RESET << endl;
    
                        enter_to_continue();
    
                        cout << GREEN << "Exiting to main menu..." << RESET << endl;
                        local_exit = true;
                        wait(1);
                    } 
                }
            }
    
            // Exit program
            else if(menu_option == "0")
            {
                system("clear");
                line("Save and Exit");
                cout << endl;   

                // Save the files before exiting
                try
                {
                    store_map_container(map_container);
                    store_credentials(accounts);
                    cout << GREEN << "Save files updated." << endl;
                }
                catch(const std::exception& e)
                {
                    std::cerr << RED "ERROR : " << e.what() << RESET << '\n';
                    cout << YELLOW << "System data could not be saved." RESET << '\n';
                    enter_to_continue();
                }
    
                cout << YELLOW << "Exiting..." << RESET << endl;
                wait(1);
                exit = true;
                cout << GREEN << "SYSTEM SHUTDOWN" << RESET << endl;
            
            }
    
            // Invalid option
            else
            {
                cout << endl;
                cout << YELLOW << "Invalid option." << RESET << endl;
                enter_to_continue();
            }
    
        }

    }
    catch(const std::exception& e)
    {
        std::cerr << RED "ERROR : " << e.what() << RESET << endl;
        cout << RED << "An unknown error occured."  << endl;
        
        // Restart the program
        cout << RED << "Restarting program..." << RESET << endl;
        wait(1);

        // Program name is the name of the executable and first argument
        if (execl(program_name, program_name, (char*)NULL) == -1) 
        {
            std::cerr << RED "ERROR: Failed to restart program: " << strerror(errno) << RESET << endl;
        }
    }
    catch(...)
    {
        cout << RED << "An unknown error occured."  << endl;
        cout <<  "Please verify the save files and restart the system." << RESET << endl;

        // Restart the program
        cout << RED << "Restarting program..." << RESET << endl;
        wait(1);

        // Program name is the name of the executable and first argument
        if (execl(program_name, program_name, (char*)NULL) == -1) 
        {
            std::cerr << RED "ERROR: Failed to restart program: " << strerror(errno) << RESET << endl;
        }
    }
}