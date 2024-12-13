#include <iostream>

using namespace std;

class Circular_Queue
{
    private:
        int *queue;
        int front;
        int rear;
        int capacity;
        int size;

    public:
        Circular_Queue(int s)
        {
            capacity = s;
            queue = new int[capacity];
            size = 0;
            front = 0;
            rear = -1;
        }
        
        ~Circular_Queue()
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
        void push(int element)
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
        int pop()
        {
            if(is_empty())
            {
                return -1;
            }
            else
            {
                int item = queue[front];
                front = (front + 1) % capacity;
                size--;
                return item;
            }
        }
        int peek()
        {
            if(!is_empty())
            {
                return queue[front];
            }
            return -1;
        }
        int get_size()
        {
            return this->size;
        }
        bool isEmpty()
        {
            return size == 0;
        }
        bool isFull()
        {
            return size == capacity;
        }

        void sort()
        {
            int temp[size];
            for (int i = 0 ; i < size ; i++)
            {
                temp[i] = queue[(front + i) % capacity];
            }

            merge_sort(temp , 0 , size - 1);

            front = 0;
            rear = size - 1;
            for (int i = 0; i < size; i++)
            {
                queue[i] = temp[i];
            }


        }

private:
    void merge_sort(int arr[] , int left , int right)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;

            merge_sort(arr, left, mid);
            merge_sort(arr, mid + 1, right);

            merge(arr, left, mid, right);
        }
    }

    void merge(int arr[] , int left , int mid , int right)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        int *L = new int[n1];
        int *R = new int[n2];

        for (int i = 0; i < n1; i++)
        {
            L[i] = arr[left + i];
        }
        for (int i = 0; i < n2; i++)
        {
            R[i] = arr[mid + 1 + i];
        }

        int i = 0 , j = 0 , k = left;
        while (i < n1 && j < n2)
        {
            if (L[i] <= R[j])
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1)
        {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2)
        {
            arr[k] = R[j];
            j++;
            k++;
        }

        delete[] L;
        delete[] R;
    }
};