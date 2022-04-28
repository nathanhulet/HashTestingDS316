#ifndef MYHASH_H_INCLUDED
#define MYHASH_H_INCLUDED

#include "myList.h" //list used for separate chaining
#include <iostream> // for std::cout

class myHash
{
    //capacity of hash table
    int capacity;

    //number of elements
    double elements;

    //array of list objects where values are stored
    myList<int>** hashTable;

public:
    //CONSTRUCTORS

    //default constructor
    //initializes a default table
    myHash()
    {
        capacity = 10;
        hashTable = new myList<int>*[capacity];
        for (int i = 0; i < capacity; ++i) {
            hashTable[i] = nullptr;
        }
        elements = 0;
    }

    //constructor to initialize capacity to n
    myHash(int n)
    {
        capacity = n;
        hashTable = new myList<int>*[capacity];
        for (int i = 0; i < capacity; ++i) {
            hashTable[i] = nullptr;
        }
        elements = 0;
    }

    //destructor
    //frees dynamic memory
    ~myHash()
    {
        for (int i = 0; i < capacity; ++i) {
            if (hashTable[i] != nullptr) {
                hashTable[i]->~myList();
                delete hashTable[i];
            }
        }
        capacity = 0;
        elements = 0;
        delete [] hashTable;
    }

    //OPERATIONS

    //precondition: must be passed in an integer
    //postcondition: returns a value that fits the index of the hash table
    int hashFunction(int val)
    {
        //returns a value between 1 and 1 - capacity to fit in array
        return (val % capacity);
    }

    //precondition: must be passed in an integer
    //postcondition: hashes and inserts value into hash table
    void insert(int val)
    {
        //generates index from hash function
        int index = hashFunction(val);

        if (hashTable[index] == nullptr) {
            hashTable[index] = new myList<int>;
            hashTable[index]->append(val);
        }
        else {
            hashTable[index]->append(val);
        }

        //adds one to elements
        elements++;

    }

    //precondition: must be passed in an integer that is (hopefully) in the table
    //postcondition: searches for and if found, removes the value from the table
    void del(int val)
    {
        //generates index from hash function
        int index = hashFunction(val);

        if (hashTable[index] == nullptr) {
            return;
        }

        //searches for and if found deletes value
        hashTable[index]->remove(val);

        //removes one from elements
        elements--;

    }

    //precondition: none
    //postcondition: returns capacity
    int getCapacity()
    {
        return capacity;
    }

    //precondition: none
    //postcondition: returns number of elements
    int getElements()
    {
        return elements;
    }

    //precondition: table must not be empty
    //postcondition: prints hash table
    void print()
    {
        //if table is empty
        if(elements == 0)
        {
            std::cout << "Table is empty" << std::endl;
            return;
        }

        //loops through table
        for(int i = 0; i < capacity; i++)
        {
            //individually prints out each list at each index
            hashTable[i]->print();
            std::cout << std::endl;
        }
    }

    //precondition: must pass a valid value
    //postcondition: returns if value is in hash table or not
    bool isIn(int val)
    {
        //generates index from hash function
        int index = hashFunction(val);

        if (hashTable[index] == nullptr) {
            return false;
        }

        //if value is found
        if(hashTable[index]->find(val) != nullptr)
        {
            return true;
        }
        //otherwise it is not in table
        else
        {
            return false;
        }
    }
};

#endif // MYHASH_H_INCLUDED
