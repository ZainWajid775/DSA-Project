#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H


// For windows, use cin.get
#ifdef WIN_32
#include <cstdlib>
// Function to print "enter to continue" and wait for user input
void enter_to_continue()
{
    cout << continue_key << '\n';
    cin.get();
}
#else
#include <unistd.h>
// Function to print "enter to continue" and wait for user input
void enter_to_continue()
{
    cout << continue_key << '\n';
    system("read");
}
#endif

#include <iostream>


using namespace std;

//Colour codes for custom text priting
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"    

// User Interface
string continue_key = "Press the enter key to continue\n";    

//Function to print a coloured line to improve readibility
void line(string s)
{
    //If an empty string is passed, a line is printed 
    if (s.empty())
    {
        cout << CYAN << "================================================================\n";
    }
    //If the string has characters, they are printed in the center of the line 
    else
    {   
            int length = 64;
            int s_len = s.length();
            int remaining_space = length - s_len;
            int half = remaining_space / 2;

            for (int i = 0 ; i < half - 1 ; i++)
            {
                cout << CYAN << "=" ;
            }
            cout << "|";
            cout << s;
            cout << "|";
            for (int i = 0 ; i < half - 1 ; i++)
            {
                cout << CYAN << "=" ;
            }
            cout << endl << RESET;
    }

}

// Function to print "enter to continue" and wait for user input
void enter_to_continue()
{
    cout << continue_key << '\n';
    system("read");
}


#endif