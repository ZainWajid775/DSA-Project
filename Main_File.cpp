#include <iostream>
#include <pthread.h>
#include <chrono>
#include <iomanip>
#include "Map.h"
#include "File_Handling/File_Handling.h"

using namespace std;


int main()
{
    //srand(time(0));
//
    //Map map(2);
//
    //Road r1("Road 1" , 10 , 10 , "A" , "B");
    //Road r2("Road 2" , 10 , 10 , "B" , "C");
//
    //Junction A("A" , 0 , 0 , 10 , 1);
    //Junction B("B" , 0 , 1 , 10 , 1);
    //Junction C("C" , 1 , 0 , 10 , 3);
    //Junction D("D" , 1 , 1 , 10 , 1);
//
    //map.add_junction(&A);
    //map.add_junction(&B);
    //map.add_junction(&C);
    //map.add_junction(&D);
//
    //map.add_road(&r1 , true);
    //map.add_road(&r2 , false);
//
    //system("clear");
    //Vehicle v1("A" , "B" , 10);
    //map.junction_cycle_add(&A , v1);
    //map.display_map();
//
//
    //map.move_vehcle(&A , &r1);
    //map.display_map();
//
    //map.move_vehicle(&r1 , &B);
    //map.display_map();

    
    vector<string> creds;
    creds = read_credentials();
    for(const auto &c : creds)
    {
        cout << c << endl;
    }

    string x , y;
    cin >> x;
    cin >> y;

    string t  = x+"|"+y;
    for(const auto &c : creds)
    {
        if(t == c)
        {
            cout << "Valid cred";
        }
    }


}