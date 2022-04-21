//
// Created by Nathan Maynard Hulet on 4/14/22.
//

#ifndef DS_PRJ_HASH_ARRAYHASH_H
#define DS_PRJ_HASH_ARRAYHASH_H

#include "chainingArray.h"

// array hash table class with separate chaining
class arrayHash {

private:
    // number of buckets
    int buckets;
    // pointer to array of pointers to chaining arrays (pointer to buckets)
    chainingArray** table;
    // helper function to get hash value from a key
    int getHash(int key);

public:
    // constructor with variable number of buckets
    explicit arrayHash(int numberOfBuckets);
    // destructor
    ~arrayHash();
    // Insert takes an integer value and adds it to the appropriate bucket
    // Insert will not add duplicates of values already in the bucket
    // Insert should only be used with values greater than or equal to zero
    void insert(int value);
    // Search takes a value to search for. If the value is found, the same value is returned.
    // If the value is not found, -1 is returned.
    int search(int searchValue);
    // Remove searches for the value and removes it from the bucket if it is found.
    void remove(int key);
    // prints the hash table by showing each bucket and its contents.
    void print();
};


#endif //DS_PRJ_HASH_ARRAYHASH_H
