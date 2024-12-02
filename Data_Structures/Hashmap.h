#ifndef Hashmap_H
#define Hashmap_H

#include <iostream>
#include <list>
#include <utility>
#include <functional>
#include <iostream>
#include "Vector.h"

using namespace std;

template <typename Key, typename Value>
class UnorderedMap
{
private:
    // Hash bucket to store key-value pairs
    vector<list<pair<Key, Value> > > buckets;
    size_t bucket_count;
    size_t size_;

    // Hash function
    size_t get_bucket_index(const Key& key) const
    {
        return hash<Key>()(key) % bucket_count;  // Standard hash and modulus to fit the bucket
    }

public:
    // Constructor
    UnorderedMap(size_t num_buckets = 10) : bucket_count(num_buckets), size_(0)
    {
        buckets.resize(bucket_count);
    }

    // Insert a key-value pair
    void insert(const Key& key, const Value& value)
    {
        size_t index = get_bucket_index(key);
        auto& bucket = buckets[index];

        // Check if the key already exists
        for (auto& pair : bucket)
        {
            if (pair.first == key)
            {
                pair.second = value; // Update the value if key exists
                return;
            }
        }

        // Key does not exist; insert it
        bucket.emplace_back(key, value);
        size_++;
    }

    // Erase a key-value pair by key
    bool erase(const Key& key)
    {
        size_t index = get_bucket_index(key);
        auto& bucket = buckets[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if (it->first == key)
            {
                bucket.erase(it); // Remove the pair
                size_--;
                return true;
            }
        }

        return false; // Key not found
    }

    // Find a value by key
    Value* find(const Key& key)
    {
        size_t index = get_bucket_index(key);
        auto& bucket = buckets[index];

        for (auto& pair : bucket)
        {
            if (pair.first == key)
            {
                return &pair.second; // Return a pointer to the value
            }
        }

        return nullptr; // Key not found
    }

    // Check if a key exists
    bool contains(const Key& key) const
    {
        size_t index = get_bucket_index(key);
        const auto& bucket = buckets[index];

        for (const auto& pair : bucket)
        {
            if (pair.first == key)
            {
                return true;
            }
        }

        return false;
    }

    // Get the number of elements
    size_t size() const
    {
        return size_;
    }

    // Check if the map is empty
    bool empty() const
    {
        return size_ == 0;
    }

    // Print the hash table (for debugging)
    void print() const
    {
        for (size_t i = 0; i < bucket_count; ++i)
        {
            cout << "Bucket " << i << ": ";
            for (const auto& pair : buckets[i])
            {
                cout << "(" << pair.first << ": " << pair.second << ") ";
            }
            cout << endl;
        }
    }
};

#endif Hashmap_H
