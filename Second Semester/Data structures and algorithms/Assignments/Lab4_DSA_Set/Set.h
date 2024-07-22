#pragma once
#include <cmath>
//DO NOT INCLUDE SETITERATOR

#define EMPTY_POSITION -999999
#define DELETED_POSITION 888999

typedef int TElem;
class SetIterator;

class Set {
private:
    TElem* elements;
    int capacity;
    int sizeSet;

    // Hash function 1
    int hashFunction1(TElem elem) const {
        return elem % this->capacity;
    }

    // Hash function 2
    int hashFunction2(TElem elem) const {
        return 1 + (elem % (this->capacity-1) );
    }

    // Double hashing function
    int doubleHash(TElem elem) const {

        int aux_element = abs(elem);
        bool found = false;
        int probe_number = 0;
        int position = -1;

        while (!found)
        {
            position = (this->hashFunction1(aux_element) + probe_number * this->hashFunction2(aux_element) ) % this->capacity;

            if (this->elements[position] == EMPTY_POSITION || this->elements[position] == DELETED_POSITION)
            {
                found = true;
            }
            else
            {
                probe_number++;
                if (probe_number >= this->capacity)
                    return -1;
            }
        }

        return position;
    }

    // Resize the hash table
    void resize();


public:
    // Implicit constructor
    Set();

    // Destructor
    ~Set();

    // Adds an element to the set
    // Returns true if the element was added, false otherwise
    bool add(TElem elem);

    // Removes an element from the set
    // Returns true if the element was removed, false otherwise
    bool remove(TElem elem);

    // Checks whether an element belongs to the set or not
    bool search(TElem elem) const;

    // Returns the number of elements
    int size() const;

    // Checks whether the set is empty or not
    bool isEmpty() const;

    // Return an iterator for the set
    SetIterator iterator() const;

    int getCapacity() const{
        return this->capacity;
    }

    const TElem* getElements() const {
        return elements;
    }
};