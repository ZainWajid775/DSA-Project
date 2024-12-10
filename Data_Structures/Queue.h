#include <iostream>

using namespace std;

template <class T>

class Queue
{
    private:
        T *queue;
        int front;
        int rear;
        int capacity;
        int size;

    public:
        Queue(int s)
        {
            capacity = s;
            queue = new T[capacity];
            size = 0;
            front = 0;
            rear = -1;
        }
        
        ~Queue()
        {
            delete[] queue;
        }

        bool is_full()
        {
            return (size == capacity);
        }

        bool is_empty()
        {
            return (size == 0);
        }
        void push(T element)
        {
            if(is_full())
            {
                return;
            }
            else
            {
                rear = (rear + 1) % capacity;
                queue[rear] = element;
                size++;
            }
        }
        T pop()
        {
            if(is_empty())
            {
                return -1;
            }
            else
            {
                T item = queue[front];
                front = (front + 1) % capacity;
                size--;
                return item;
            }
        }
        T peek();
        int size();
        bool isEmpty();
        bool isFull();
};