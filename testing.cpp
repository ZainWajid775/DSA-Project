#include <iostream>
using namespace std;

int main()
{
    for(int i = 0; i < 10 ; i++)
    {
            int id = rand() % 999 + 100;
            cout << id;
    }

}
