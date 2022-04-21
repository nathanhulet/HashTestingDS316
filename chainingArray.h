//
// Created by Nathan Maynard Hulet on 4/20/22.
//

#ifndef DS_PRJ_HASH_CHAININGARRAY_H
#define DS_PRJ_HASH_CHAININGARRAY_H


// dynamicArrayClass
class chainingArray {

private:
    // pointer to the dynamic array
    int *arrayPointer;
    // total space allocated for elements
    int capacity;
    // total elements currently in the dynamic array
    int numOfElements;

public:
    //constructor
    chainingArray();
    // destructor
    ~chainingArray();
    // operator overloading to allow for [] indexing
    int& operator[](int index);
    // adds a value to the array if the value does not currently exist in the array
    void append(int val);
    // returns the current capacity of the  dynamic array
    int getCapacity();
    // searches for a value greater than or equal to zero. If found it returns the value searched for
    // If the search is not found, -1 is returned
    int search(int searchFor);
    // searches for the element to remove and deletes it by shifting the array 1 element left starting at the index of
    // the element to delete
    void remove(int value);
    // prints every element in the array seperated by a space
    void print();
};


#endif //DS_PRJ_HASH_CHAININGARRAY_H
