#ifndef Linked_List_H
#define Linked_List_H

#include <iostream>
#include "../Vehicle.h"
using namespace std;

// DELETION DOESNT CHECK IF VEHICLE EXISTS IN LINKED LIST
// USE EXISTS FUCNTION FIRST

struct Node
{
    Vehicle vehicle;
    Node* next;  

    Node(Vehicle v) : vehicle(v) , next(nullptr) {}
};

class List
{
    private:
        Node* head;

    public:

        List() : head(nullptr) {}

        void insert(Vehicle v)
        {
            Node* node = new Node(v);
            Node* temp = head;

            if(temp == nullptr)
            {
                head = node;
                return;
            }

            while(temp->next != nullptr)
            {
                temp = temp->next;
            }

            temp->next = node;
        }

        bool is_empty()
        {
            return head == nullptr;
        }

        Vehicle get_front()
        {
            return head->vehicle;
        }

        int size()
        {
            Node* temp = head;
            int count = 0;

            while(temp != nullptr)
            {
                count++;
                temp = temp->next;
            }

            return count;
        }

        void remove(Vehicle v)
        {
            if(head->vehicle.id == v.id)
            {
                Node* temp = head;
                head = head->next;
                delete temp;
                return;
            }

            Node* temp = head;
            Node* prev = nullptr;

            while(temp && temp->vehicle.id != v.id)
            {
                prev = temp;
                temp = temp->next;
            }

            prev->next = temp->next;
            delete temp;

        }

        // EXIST FUNCTION WORKS WITH VEHICLE IDS ONLY
        bool exists(const Vehicle& v) const
        {
            Node* temp = head;

            while(temp != nullptr)
            {
                if(v.id == temp->vehicle.id)
                {
                    return true;
                }
                temp = temp->next;
            }

            return false;
        }

        void print()
        {
            Node* temp = head;

            while(temp != nullptr)
            {
                cout << temp->vehicle.id << endl;
                temp = temp->next;
            }
        }

        int* duplicate_list()
        {
            int count = size();

            int* arr = new int[count];

            int i = 0;
            Node* temp = head;
            while(temp != nullptr)
            {
                arr[i] = temp->vehicle.id;
                temp = temp->next;
                i++;
            }

            return arr;
        }

        Vehicle return_vehicle(int id)
        {
            if(!is_empty())
            {
                Node* temp = head;

                while(temp != nullptr)
                {
                    if(temp->vehicle.id == id)
                    {
                        return temp->vehicle;
                    }
                    temp = temp->next;
                }
            }

            return Vehicle("ERROR" , "ERROR" , 404);
        }

        ~List()
        {
            while(head != nullptr)
            {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }
};

#endif