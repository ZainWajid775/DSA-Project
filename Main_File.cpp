#include <iostream>
#include <chrono>
#include <cstdlib>
#include "Map.h" 
#include "Simulation.h"
#include "File_Handling/File_Handling.h"
#include "User_Interface.h"

using namespace std;

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


int main() 
{   
    // Bool var to exit program
    bool exit = false;

    // Stores user accounts
    vector<string> accounts;

    // Map container
    vector <Map*> map_container;

    // Initial start up
    // Read all stored user accounts
    bool file_read = false;

    system("clear");
    line("Login");
    cout << endl;

    try 
    {
        accounts = read_credentials();
        file_read = true;
    }
    catch(const std::exception& e)
    {
        std::cerr << RED "ERROR : " << e.what() << RESET << '\n';
        enter_to_continue();
    }

    // Checks if login was successful
    bool login = false;

    // Get user credentials
    if(file_read)
    {        
        while(!login)
        {

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
                    enter_to_continue();
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
    line("Loading Maps");

    // Read all maps
    try
    {
        map_container = read_maps();
    }
    // If maps cannot be loaded, proceed to main menu
    catch(const std::exception& e)
    {
        std::cerr << RED "ERROR : " << e.what() << RESET << '\n';
        enter_to_continue();
    }
    

    Map map("Test City", 3); 
    Junction *j1 = new Junction("J1", 0, 0, 5, 1);
    Junction *j2 = new Junction("J2", 0, 1, 5, 2);
    Junction *j3 = new Junction("J3", 2, 2, 5, 3);
    
    // Create one road between them
    Road *r1 = new Road("R1", 1.0, 3, "J1", "J2");
    Road *r2 = new Road("R2", 1.0, 3, "J2", "J1");
    Road *r3 = new Road("R3", 1.0, 3, "J2", "J3");
    Road *r4 = new Road("R4", 1.0, 3, "J3", "J2");

    Vehicle *v1 = new Vehicle(1 , 10);

    // Add junctions and road to the map
    map.add_junction(j1);
    map.add_junction(j2);
    map.add_junction(j3);
    map.add_road(r1);
    map.add_road(r2);
    map.add_road(r3);
    map.add_road(r4);

    Map map_2("Test City 2", 3); 

    // Add junctions and road to the map
    map_2.add_junction(j1);
    map_2.add_junction(j2);
    map_2.add_junction(j3);
    map_2.add_road(r1);
    map_2.add_road(r2);
    map_2.add_road(r3);
    map_2.add_road(r4);

    map_container.push_back(&map);
    map_container.push_back(&map_2);

    // Store maps
    store_map_container(map_container);
    map_container = read_maps();



    return 0;
}