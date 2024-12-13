#ifndef STACK_H
#define STACK_H

#include <string>
#include <iostream>

using namespace std;

struct S_Node
{
    string data;
    S_Node* next;

    S_Node(string s) : data(s) , next(nullptr) {}
};

class Stack
{
    private:
    S_Node* top;

    public:
    Stack() : top(nullptr) {}

    void push(string s)
    {
        S_Node* new_S_Node = new S_Node(s);
        new_S_Node->next = top;
        top = new_S_Node;
    } 

    string pop()
    {
        if(is_empty())
        {
            return "";
        }
        else
        {
            S_Node* temp = top;
            string pop_data = top->data;
            top = top->next;
            delete temp;
            return pop_data;
        }
    }

    string peek()
    {
        if(is_empty())
        {
            return "";
        }
        else
        {
            return top->data;
        }
    }

    bool is_empty()
    {
        if(top == nullptr)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    void print()
    {
        if(is_empty())
        {
            cout << "Stack Underflow\n";
        }
        else
        {
            S_Node* temp = top;
            int count = 0;
            do
            {
                cout << "Index : " << count << " Data : " << temp->data << endl;
                temp = temp->next;
                count ++;
            }while(temp != nullptr);
        }
    }


};



#endif
