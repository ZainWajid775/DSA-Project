#ifndef Vector_H
#define Vector_H

#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T>

class Vector
{
    private:
        T* data;            
        size_t size;
        size_t capacity;

    public:
        Vector(size_t initial_capacity = 10)
        {
            size = 0;
            capacity = initial_capacity;
            data = new T[capacity];
        }

        void resize(size_t new_size)
        {
            if(new_size > capacity)
            {
                capacity = new_size * 2;
                T* new_data = new T[capacity];

                for(size_t i = 0 ; i < size ; i++)
                {
                    new_data[i] = data[i];
                }

                delete[] data;
                data = new_data;
            }

            size = new_size;
        }

        void resize(size_t outer_size , size_t inner_size = 0)
        {
            resize(outer_size);
            for(size_t i = 0 ; i < outer_size ; ++i)
            {
                data[i].resize(inner_size);
            }
        }

        T& operator[](size_t index)
        {
            if(index >= size)
            {
                throw out_of_range("Index out of range");
            }
            return data[index];
        }

        void push_back(const T& value)
        {
            if(size == capacity)
            {
                resize(capacity * 2);
            }

            data[size] = value;
            ++size;
        }

        size_t get_size() const
        {
            return size;    
        }

        size_t get_capacity() const
        {
            return capacity;
        }

        void clear()
        {
            size = 0;
        }

        bool empty()
        {
            return size == 0;
        }
};

#endif 