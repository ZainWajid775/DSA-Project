#ifndef Vector_H
#define Vector_H

#include <iostream>
#include <stdexcept>
using namespace std;

// Dynamic array that can resize itself

// Template to allow for any data type
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

        // Resize the vector
        void resize(size_t new_size)
        {
            if(new_size > capacity)
            {
                // Resize and allocate new memory
                capacity = new_size * 2;
                T* new_data = new T[capacity];

                // Copy old data to new data
                for(size_t i = 0 ; i < size ; i++)
                {
                    new_data[i] = data[i];
                }

                // Free the old memory
                delete[] data;

                // Point to the new block
                data = new_data;
            }

            // Update the size
            size = new_size;
        }

        // Resize a 2d-vector (Road_Matrix)
        void resize(size_t outer_size , size_t inner_size = 0)
        {   
            // Resize the outer vector
            resize(outer_size);

            // Then resize each of the inner vector
            for(size_t i = 0 ; i < outer_size ; ++i)
            {
                data[i].resize(inner_size);
            }
        }

        // Overload the [] operator to access elements
        T& operator[](size_t index)
        {
            if(index >= size)
            {
                throw out_of_range("Index out of range");
            }
            return data[index];
        }

        // Add an element to the vector
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
            delete[] data;
            size = 0;
        }

        bool empty()
        {
            return size == 0;
        }
};

#endif 