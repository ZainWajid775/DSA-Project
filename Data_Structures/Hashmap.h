#ifndef HASHMAP_H
#define HASHMAP_H

#include <list>

using namespace std;

// Template for the custom Hashmap
template <typename K, typename V>

class Hashmap
{
    private:
        // Size of hashmap
        int table_size;
        // List of pairs
        list<pair<K , V>>* table;

        int hash_function(K key) const
        {
            return key % table_size;
        }

    public:

        // Constructor
        Hashmap(int size) : table_size(size)
        {
            table = new list<pair<K, V>>[table_size];
        }

        // Destructor
        ~Hashmap()
        {
            delete[] table;
        }

        // Insert a key value pair
        // By design there can be no duplicate keys due to the vehicle ids being unique
        void insert(K key , const V& value)
        {
            // Get the index of the key
            int index = hash_function(key);

            // Check if key already exists
            for (auto& pair : table[index])
            {   
                // If the key exists , update the value by adding another value for that key
                if (pair.first == key)
                {
                    pair.second = value; 
                    return;
                }
            }

            // If key does not exist, add a new pair
            table[index].emplace_back(key, value);
        }

        bool find(K key) const
        {   
            // Get the index of the key
            int index = hash_function(key);

            // Check if key exists
            for (const auto& pair : table[index])
            {   
                if (pair.first == key)
                {
                    return true;
                }
            }
            return false;
        }

        void remove(K key)
        {
            int index = hash_function(key);
            for (auto it = table[index].begin(); it != table[index].end(); ++it)
            {
                if (it->first == key)
                {
                    table[index].erase(it);
                    return;
                }
            }
        }
};

#endif
