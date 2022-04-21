//
// Created by Nathan Maynard Hulet on 4/14/22.
//

#include "arrayHash.h"
#include <iostream>

// hashing function
int arrayHash::getHash(int key) {
    return (key % buckets);
}

// constructor
arrayHash::arrayHash(int numberOfBuckets) {
    buckets = numberOfBuckets;
    // initialize the table and set all buckets to nullptr to represent an empty bucket
    table = new chainingArray*[buckets];
    for (int i = 0; i < buckets; ++i) {
        table[i] = nullptr;
    }
}

// destructor
arrayHash::~arrayHash() {
    for (int i = 0; i < buckets; ++i) {
        if (table[i] != nullptr) {
            delete table[i];
        }
    }
    delete [] table;
}

// insert a value into the hash table
void arrayHash::insert(int value) {
    // get the correct bucket to place the value into
    int index = getHash(value);
    // if the bucket is empty, allocate memory for a bucket and insert the element, otherwise just insert the element
    if (table[index] == nullptr) {
        table[index] = new chainingArray;
        table[index]->append(value);
    }
    else {
        table[index]->append(value);
    }
}

// search for a value in the hash table
int arrayHash::search(int searchValue) {
    // get the correct bucket to perform the search in
    int index = getHash(searchValue);
    // When the bucket is empty, the search fails and -1 is returned
    if (table[index] == nullptr) {
        return -1;
    }
    int firstValue = table[index]->operator[](0);
    // When the value to search for is found in the first item in the bucket
    if (firstValue == searchValue) {
        return firstValue;
    }
    // When the value is not in the first position, but the bucket is not empty, a search through the bucket occurs
    else {
        return (table[index]->search(searchValue));
    }

}

// remove an element from the hash table
void arrayHash::remove(int value) {
    // get the correct bucket to remove the element from
    int index = getHash(value);
    // when the bucket is empty, the value to remove does not exist, if not, perform the remove
    if (table[index] == nullptr) {
        return;
    }
    table[index]->remove(value);
}

// print the entire hash table by bucket
void arrayHash::print() {
    // only print out buckets that have been allocated already
    for (int i = 0; i < buckets; ++i) {
        if (table[i] != nullptr) {
            std::cout << "\n\nBucket " << i << ":\n";
            table[i]->print();
        }
    }
}