#ifndef FILE_HANDLING_h
#define FILE_HANDLING_h

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../Data_Structures/Vector.h"

using namespace std;

vector<string> read_credentials()
{
    ifstream file("File_Handling/Accounts.txt");

    vector<string> credentials;
    string line;
    string username , password;
    bool pair = true;

    if(!file.is_open())
    {
        cerr << "Error opening file !" << endl;
        exit(1);
    }

    while(getline(file , line))
    {
        username = line;

        if(getline(file , line))
        {
            password = line;
            string temp = username + "|" + password;
            
            credentials.push_back(temp);
        }

    }

    return credentials; 
}

#endif

