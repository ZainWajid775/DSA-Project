#ifndef Linked_List_H
#define Linked_List_H

#include <iostream>
#include "../Vehicle.h"
using namespace std;

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

        // Constructer
        List() : head(nullptr) {}

        Node* get_head() const 
        { 
            return head; 
        }

        //Insert at front
        void insert_front(Vehicle v)
        {
            Node* node  = new Node(v);

            node->next = head;
            head = node;
        }

        // Insert at end
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

        // Get vehicle in front of list
        Vehicle get_front()
        {
            Vehicle temp = head->vehicle;
            return temp;
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

        // Remove vehicle if it exists
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

        // Checks the vehicle id
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

        // For sorting using bubble sort
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

        // Checks if vehicle exists in list
        bool exists_in_list(Vehicle vehicle)
        {
            Node* temp = head;

            while(temp != nullptr)
            {
                if(temp->vehicle == vehicle)
                {
                    return true;
                }
                temp = temp->next;
            }

            return false;
        }

        // Removes all vehicles
        void clear()
        {
            while(!is_empty())
            {
                Vehicle v = get_front();
                remove(v);
            }
        }

        // Destructor
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