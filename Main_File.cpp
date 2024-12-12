#include <iostream>
#include <chrono>
#include <cstdlib>
#include <algorithm>    

#include "Map.h" 
#include "Simulation.h"
#include "File_Handling/File_Handling.h"

#include "Data_Structures/Binary_Search_Tree.h"

#include "User_Interface.h"


using namespace std;

// Map container
vector <Map*> map_container;

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


int main() 
{   
    // Bool var to exit program
    bool exit = false;

    // Stores user accounts
    vector<string> accounts;

    // Initial start up

    system("clear");
    line("Login");
    cout << endl;

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

    string menu_option;

    // Main menu
    while(!exit)
    {   

        system("clear");
        line("Main Menu");
        cout << endl;

        cout << RED "1. View Maps" << endl;
        cout << YELLOW "2. Create Map" << endl;
        cout << GREEN "3. Delete Map" << endl;
        cout << BLUE "4. Simulation" << endl;
        cout << MAGENTA "5. Add a user" << endl;
        cout << RED "6. Remove a user" << endl;
        cout << YELLOW "7. AVL Tree Map sorting" << endl;
        cout << GREEN "0. Exit" RESET << endl << endl;
        
        cout << YELLOW "Option : " << RESET;
        cin >> menu_option;
        
        // View maps
        if(menu_option == "1")
        {
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

                cout << YELLOW "Exiting to main menu." RESET << endl;
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
                    int map_option;
                    
                    cout << YELLOW << "Select a map to view by index" << RESET << '\n';
                    cout << endl;
                    for(int i = 0; i < map_container.size(); i++)
                    {
                        cout << GREEN << i + 1 << ". " << map_container[i]->map_name << '\n';
                    }
                    cout << endl;
                    cout << YELLOW "Enter 0 to Exit" << endl << endl;
                    cout << "Option : " << RESET;
                    cin >> map_option;

                    if(map_option == 0)
                    {
                        local_exit = true;
                        cout << GREEN "Exiting to main menu... " RESET << endl;
                        wait(1);
                    }

                    // Check if map exists and then display it
                    else if(map_option > 0 && map_option <= map_container.size())
                    {
                        // Show map
                        system("clear");
                        line("Map Viewer");
                        cout << endl;
                        map_container[map_option - 1]->display_map();
                        cout << endl; 
                        enter_to_continue();
                    }
                    else
                    {
                        cout << endl;
                        cout << YELLOW << "Invalid option." << RESET << '\n';
                        enter_to_continue();
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
                    bool c1 = false , c2 = false , c3 = false , c4 = false , c5 = false;
                    string j_name , j_row , j_column , j_capacity , j_timer;

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

                        if(stoi(j_row) > m_junctions || stoi(j_row) < 0)
                        {
                            cout << RED << "Invalid index !" << RESET << endl;
                            enter_to_continue();
                        }
                        else
                        {
                            c2 = true;
                        }
                    
                        cout << YELLOW << "Enter the column index of the junction : " << RESET;
                        cin >> j_column;
                        cout << endl;
                        
                        if(stoi(j_column) > m_junctions || stoi(j_column) < 0)
                        {
                            cout << RED << "Invalid index !" << RESET << endl;
                            enter_to_continue();
                        }
                        else if(new_map->is_index_clear(stoi(j_row) , stoi(j_column)))
                        {
                            cout << RED << "Junction already exists at this index !" << RESET << endl;
                            enter_to_continue();
                        }
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

                    while(!c5)
                    {
                        cout << YELLOW << "Enter the junctions signal timer : " << RESET;
                        cin >> j_timer;
                        cout << endl;

                        if(stoi(j_timer) < 1)
                        {
                            cout << RED << "Invalid timer !" << RESET << endl;
                            enter_to_continue();
                        }
                        else
                        {
                            c5 = true;
                        }
                    }
                    // Create and add junction
                    Junction *new_junction = new Junction(j_name , stoi(j_row) , stoi(j_column) , stoi(j_capacity) , stoi(j_timer));
                    new_map->add_junction(new_junction);

                    // Check if user wants to go back
                    cout << GREEN << "Junction added to map" << RESET << endl << endl;
                    j_count++;

                    new_map->display_junctions();
                    cout << endl;
                    cout << YELLOW << "Junction map is only a visual aid !!!" << endl;

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

                    while(!c4)
                    {
                        system("clear");
                        line("Map Creator");
                        cout << endl;
                        
                        new_map->display_junctions();

                        cout << endl;
                        cout << YELLOW << "Row represents starting junction and column represents ending junction" << endl << endl;

                        cout << YELLOW << "Enter the roads starting junction : " << RESET << endl;
                        cin >> r_start;
                        cout << endl;

                        cout << YELLOW << "Enter the roads ending junction : " << RESET << endl;
                        cin >> r_end;
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

            // Create a new map
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
                        cout << YELLOW "Exiting to main menu" RESET << endl;
                        wait(1);
                    }
                    else
                    {
                        for(auto& map : map_container)
                        {
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
                else
                {
                    cout << YELLOW "There are no maps to show."<< endl;
                    cout << "Please add a map from the map creater" RESET << endl;
                    enter_to_continue();
                    del_option  = "0";
                
                }
            }


            
        }

        // Add user to database
        else if(menu_option == "5")
        {
            string new_username , new_password;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            bool valid = false;

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

                        if(del_user == result)
                        {
                            bool local_exit = false;

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

            }
        }

        // Exit program
        else if(menu_option == "0")
        {
            system("clear");
            line("Save and Exit");
            cout << endl;

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
            cout << YELLOW << "Invalid option." << RESET << '\n';
            enter_to_continue();
        }

    }

    return 0;
}