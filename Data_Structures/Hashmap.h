#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include <cstdlib>
#include <ctime>
#include <list>
#include <iostream>


using namespace std;

// Template for the custom Hashmap
template <typename K, typename V>
class Hashmap
{
    private:
        int table_size;
        list<pair<K , V>>* table;

        int hash_function(K key) const
        {
            return key % table_size;
        }

    public:

        Hashmap(int size) : table_size(size)
        {
            table = new list<pair<K, V>>[table_size];
        }

        ~Hashmap()
        {
            delete[] table;
        }

        void insert(K key, const V& value)
        {
            int index = hash_function(key);
            for (auto& pair : table[index])
            {
                if (pair.first == key)
                {
                    pair.second = value; 
                    return;
                }
            }
            table[index].emplace_back(key, value);
        }

        bool find(K key) const
        {
            int index = hash_function(key);
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
