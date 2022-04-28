#ifndef MYLIST_H_INCLUDED
#define MYLIST_H_INCLUDED

#include <iostream>

template <class T>
class myList
{
private:
    //list node
    struct node
    {
        struct node* next; //next pointer
        T data; //data held in list

        //default constructor
        node()
        {
            next = nullptr; //sets next pointer to null by default
        }
    };

    node* head; //pointer to head of list
    node* tail;

public:
    //default constructor
    myList()
    {
        head = nullptr;
        tail = nullptr;
    }
    //copy constructor
    myList(const myList<T> &t)
    {
        if(t.head)
        {
            node* nodePtr = t.head; //node pointer to head of other list for traversal

            head = new node; //starts the new list to be copied to
            node* local = head; //sets pointer to head of current list to traverse

            while(nodePtr->next) //while nodePtr is pointer to a list item
            {
                local->data = nodePtr->data; //copies data over
                local->next = new node; //allocates a new node
                local = local->next; //sets local pointer to new node

                nodePtr = nodePtr->next; //moves pointer to next node to copy from
            }

            local->data = nodePtr->data; //copies data over
            local->next = nullptr; //end of list
            tail = local;

            local = local->next; //sets local pointer to null
            nodePtr = nodePtr->next; //sets other pointer to null
        }
        else
        {
            head = nullptr;
            tail = nullptr;
        }
    }
    //destructor
    ~myList()
    {
        if(!head) //checks to see if list is empty
        {
            return;
        }

        node* nodePtr = head; //sets to start of list to traverse
        node* nextPtr; //sets to next node for deleting purposes

        while(nodePtr)
        {
            nextPtr = nodePtr->next; //sets pointer to next node
            delete nodePtr; //deletes node which is dynamic memory
            nodePtr = nextPtr; //sets pointer to next node
        }

        head = nullptr; //sets to null just in case
        tail = nullptr;
    }

    //overloaded =
    myList<T>& operator=(const myList<T>& t)
    {
        if(head) //checks to see if list is empty
        {
            node* nodePtr = head; //sets to start of list to traverse
            node* nextPtr; //sets to next node for deleting purposes

            while(nodePtr)
            {
                nextPtr = nodePtr->next; //sets pointer to next node
                delete nodePtr; //deletes node which is dynamic memory
                nodePtr = nextPtr; //sets pointer to next node
            }

            head = nullptr; //sets to null just in case
            tail = nullptr;
        }

        if(t.head)
        {
            node* nodePtr = t.head; //node pointer to head of other list for traversal

            while(nodePtr) //while nodePtr is pointer to a list item
            {
                append(nodePtr->data);

                nodePtr = nodePtr->next; //moves pointer to next node to copy from
            }

            nodePtr = nullptr; //sets other pointer to null
        }
        else
        {
            head = nullptr;
            tail = nullptr;
        }

        return *this;
    }


    //append function
    //pre: Enter the data value as a parameter
    //post: Inserts the value to the end of the lsit
    void append(T data)
    {
        if(!head) //if list is empty
        {
            //sets head to a new node
            head = new node;
            head->data = data;
            head->next = nullptr;
            tail = head;
            return;
        }

        //old implementation before adding tail pointer
        /*node* nodePtr = head; //sets pointer to beginning of list

        while(nodePtr->next) //goes through list until it gets to the end
        {
            nodePtr = nodePtr->next;
        }

        nodePtr->next = new node; //creates a new node
        nodePtr->next->data = data; //inserts data
        nodePtr->next->next = nullptr; //end of list so next is null*/

        //adds new node after tail
        tail->next = new node;
        tail->next->data = data;
        tail->next->next = nullptr;
        tail = tail->next;
    }
    //delete function
    //pre: Enter the data value that is in the list as a parameter
    //post: Deletes the value from the list
    void remove(T val)
    {
        if(!head) //if list is empty
        {
            std::cout << "List is empty" << std::endl;
            return;
        }

        node* nodePtr = head;
        node* nextPtr; //next pointer if value is found

        if(head->data == val) //if data is at beginning
        {
            nextPtr = head->next;
            delete head;
            head = nextPtr;
            return;
        }

        while(nodePtr->next) //searches through list until it reaches the end or finds value
        {
            nextPtr = nodePtr->next;

            if(nextPtr->data == val) //if value is found
            {
                nodePtr->next = nextPtr->next;
                delete nextPtr;
                nextPtr = nullptr;
                return;
            }

            nodePtr = nodePtr->next;
        }

        //message if value is not in list
        std::cout << "Could not find value, nothing was deleted" << std::endl;
        return;
    }
    //find function
    //pre: Enter the data value that is in the list as a parameter
    //post: Returns the position of the data found in the list
    node* find(T val) const //should return an iterator but only returns node pointer for testing purposes
    {
        if(!head)
        {
            std::cout << "List is empty, returning null" << std::endl;
            return nullptr;
        }

        node* nodePtr = head;

        while(nodePtr) //searches through list until it reaches the end or finds value
        {
            if(nodePtr->data == val) //if data is found
            {
                return nodePtr;
            }

            nodePtr = nodePtr->next;
        }

        //message if value is not in list
        std::cout << "Could not find value, returning null" << std::endl;
        return nullptr;
    }
    //print function
    //pre: list must not be empty
    //post: prints the entire contents of a list
    void print() const
    {
        if(!head) //if list is empty
        {
            std::cout << "List is empty, nothing could be printed";
            return;
        }

        node* nodePtr = head;

        while(nodePtr)
        {
            std::cout << nodePtr->data << " ";
            nodePtr = nodePtr->next;
        }
    }
    //pre: list must not be empty and value provided must be in list
    //post: adds value before item specified in list or if multiple values before first occurence, or if empty appends value
    void insert(T index, T val)
    {
        if(!head) //if list is empty
        {
            append(val);
            return;
        }

        node* nodePtr = head;
        node* nextPtr; //next pointer if value if found

        if(head->data == index) //if data is at beginning
        {
            std::cout << "List is empty, adding element to list" << std::endl;
            head = new node;
            head->data = val;
            head->next = nodePtr;
            return;
        }

        while(nodePtr->next) //searches through list until it reaches the end or finds value
        {
            nextPtr = nodePtr->next;

            if(nextPtr->data == index) //if value is found
            {
                nodePtr->next = new node;
                nodePtr->next->data = val;
                nodePtr->next->next = nextPtr;
                return;
            }

            nodePtr = nodePtr->next;
        }

        //message if value is not in list
        std::cout << "Could not find value, nothing was changed" << std::endl;
        return;
    }

};

#endif // MYLIST_H_INCLUDED
