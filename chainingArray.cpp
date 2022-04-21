//
// Created by Nathan Maynard Hulet on 4/20/22.
//

#include "chainingArray.h"
#include <iostream>

// constructor
chainingArray::chainingArray() {
    // starts with space for 8 elements all initialized to -1
    arrayPointer = new int[8];
    for (int i = 0; i < 8; ++i) {
        arrayPointer[i] = -1;
    }
    capacity = 8;
    numOfElements = 0;
}

// destructor
chainingArray::~chainingArray() {
    delete [] arrayPointer;
}

// operator overloading for [] indexing
// Do not use [] to add elements unless numOfElements will be manually updated
int& chainingArray::operator[](int index) {
    // when the index is out of range, allocate more memory by doubling the capacity
    if (index >= capacity) {
        // create new array with double capacity
        int *newArray = new int[capacity * 2];
        // copy the first array onto the new one
        for (int i = 0; i < numOfElements; ++i) {
            newArray[i] = arrayPointer[i];
        }
        // initialize all the new values to -1
        for (int i = numOfElements; i < capacity * 2; ++i) {
            newArray[i] = -1;
        }
        // update capacity, delete the old array, and set the pointer to the new array
        capacity = capacity * 2;
        delete [] arrayPointer;
        arrayPointer = newArray;
    }
    return *(arrayPointer + index);
}

// append a value to the end of the dynamic array
void chainingArray::append(int val) {
    // function will only append a value if it is not already in the array
    if (search(val) == -1) {
        // if capacity is reached, more memory is allocated by doubling capacity
        if (numOfElements == capacity) {
            capacity = capacity * 2;
            // create new array with double capacity
            int *newArray = new int[capacity];
            // copy the first array onto the new one
            for (int i = 0; i < numOfElements; ++i) {
                newArray[i] = arrayPointer[i];
            }
            // initialize all the new values to -1
            for (int i = numOfElements; i < capacity; ++i) {
                newArray[i] = 0;
            }
            // delete the old array, and set the pointer to the new array
            delete [] arrayPointer;
            arrayPointer = newArray;
        }
        // add the new element to the end of the array
        arrayPointer[numOfElements] = val;
        ++numOfElements;
    }
}

// get the current capacity of the array
int chainingArray::getCapacity() {
    return capacity;
}

// search the array for a value
int chainingArray::search(int searchFor) {
    // iterate through the array and return the value of the search if it is found
    for (int i = 0; i < numOfElements; ++i) {
        if (arrayPointer[i] == searchFor) {
            return  arrayPointer[i]; // successful search
        }
    }
    return -1; // failed search
}

// remove an element from the array by shifting the values
void chainingArray::remove(int value) {
    int removeIndex = -1;
    // search for the element in the array
    for (int i = 0; i < numOfElements; ++i) {
        if (arrayPointer[i] == value) {
            removeIndex = i;
            i = numOfElements;
        }
    }
    // if no matching value is found no elements are deleted.
    if (removeIndex == -1) {
        return;
    }
    // Remove element by shifting the array left by 1 starting at the index of the element to remove.
    for (int i = removeIndex; i < numOfElements; ++i) {
        arrayPointer[i] = arrayPointer[i + 1];
    }
    --numOfElements;
}

// print all the elements in the array seperated by spaces
void chainingArray::print() {
    for (int i = 0; i < numOfElements; ++i) {
        std::cout << arrayPointer[i] << " ";
    }
}

