#include "Set.h"
#include "SetIterator.h"

///B.C: theta(1), W.c: theta(sqrt(x)), TOTAL: O(sqrt(x))
bool prime(int x)
{
    int d = 2;
    while (d <= sqrt(x))
    {
        if (x % d == 0)
        {
            return false;
        }
        d++;
    }
    return true;
}


int next_prime(int number)
{

    int next_prime_number = number * 2;

    if (prime(next_prime_number))
        return next_prime_number;

    while (!prime(next_prime_number))
    {
        next_prime_number++;
    }

    return next_prime_number;
}

///theta(capacity)
Set::Set() {
    capacity = 17;
    sizeSet = 0;
    elements = new TElem[capacity];
    for (int i = 0; i < capacity; ++i) {
        elements[i] = EMPTY_POSITION;
    }
}
///B.c: theta(1), W.c: theta(capacity), Total: O(capacity)
bool Set::add(TElem elem) {
    if(search(elem))
        return false;
    int position = this->doubleHash(elem);
    if (position == -1)
    {
        this->resize();
        position = this->doubleHash(elem);
    }

    this->elements[position] = elem;
    this->sizeSet++;
    return true;

}
///B.c: theta(1), W.c: theta(capacity), Total: O(capacity)
bool Set::remove(TElem elem) {
    int probe_number = 0;
    int position;
    int aux_elem = abs(elem);

    while (probe_number < this->capacity)
    {
        position = (this->hashFunction1(aux_elem) + probe_number * this->hashFunction2(aux_elem)) % this->capacity;
        if (this->elements[position] == EMPTY_POSITION)
        {
            return false;
        }
        else if (this->elements[position] != elem)
        {
            probe_number++;
        }
        else if (this->elements[position] == elem)
        {
            this->elements[position] = DELETED_POSITION;
            this->sizeSet--;
            return true;
        }
    }
    return false;
}

///B.C: theta(1), W.C:theta(capacity), Total:O(capacity)
bool Set::search(TElem elem) const {
    int probe_number = 0;
    int position;

    int aux_elem = abs(elem);

    while (probe_number < this->capacity)
    {
        position = (this->hashFunction1(aux_elem) + probe_number * this->hashFunction2(aux_elem)) % this->capacity;
        if (this->elements[position] == EMPTY_POSITION)
        {
            return false;
        }
        else if (this->elements[position] != elem)
        {
            probe_number++;
        }
        else if (this->elements[position] == elem)
        {
            return true;
        }
    }
    return false;
}

///theta(1)
int Set::size() const {
    return sizeSet;
}


///theta(1)
bool Set::isEmpty() const {
    return sizeSet == 0;
}


///theta(capacity)
void Set::resize() {
    TElem* auxiliary_elements = new TElem[this->sizeSet];
    int j = 0;
    for (int i = 0; i < this->capacity; i++)
    {
        if (this->elements[i] != EMPTY_POSITION && this->elements[i] != DELETED_POSITION)
        {
            auxiliary_elements[j] = this->elements[i];
            j++;
        }
    }

    this->capacity = next_prime(this->capacity);
    this->elements = new TElem[this->capacity];
    int position;

    for (int i = 0; i < this->capacity; i++)
    {
        this->elements[i] = EMPTY_POSITION;
    }

    for (int i = 0; i < j; i++)
    {
        position = this->doubleHash(auxiliary_elements[i]);
        this->elements[position] = auxiliary_elements[i];
    }
}

Set::~Set() {
    delete[] elements; // Free memory for the elements array
}
///theta(1)
SetIterator Set::iterator() const {
    return SetIterator(*this); // Return an iterator for the set
}
