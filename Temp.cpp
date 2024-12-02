#include <iostream>
#include "Data_Structures/Linked_List.h"
#include "Vehicle.h"


int main()
{
    Vehicle temp(100 , 100 , " " , " ");
    Vehicle temp2(99 , 99 , " " , " ");
    Vehicle temp4(101 , 99 , " " , " ");
    List l;
    l.insert(temp);
    l.insert(temp2);

    cout << l.exists(temp4) << endl;

    l.print();
}
