#include "SetIterator.h"
#include "Set.h"
#include <exception>
#include <stdexcept>
#define NOT_VALID 9900990

///O(capacity)
SetIterator::SetIterator(const Set& m) : set(m){
    this->currentPosition = 0;

    while ((this->getCurrent() == EMPTY_POSITION || this->getCurrent() == DELETED_POSITION) && this->currentPosition < set.getCapacity())
    {
        this->currentPosition++;
    }
    if (this->currentPosition >= set.getCapacity())
        this->currentPosition = NOT_VALID;
}

///O(capacity)
void SetIterator::first() {

    currentPosition = 0;
    while ((this->getCurrent() == EMPTY_POSITION || this->getCurrent() == DELETED_POSITION) && this->currentPosition < set.getCapacity())
    {
        this->currentPosition++;
    }
    if (this->currentPosition >= set.getCapacity())
        this->currentPosition = NOT_VALID;
}

///O(capacity)
void SetIterator::next() {
    if (!valid()) {
        throw std::runtime_error("bad");
    }

    currentPosition++;

    while ((this->getCurrent() == EMPTY_POSITION || this->getCurrent() == DELETED_POSITION) && this->currentPosition < set.getCapacity())
    {
        this->currentPosition++;
    }
    if (this->currentPosition >= set.getCapacity())
        this->currentPosition = NOT_VALID;


}


///theta(1)
TElem SetIterator::getCurrent() {

    if (valid()) {
        return set.getElements()[currentPosition];
    } else {

        throw std::runtime_error("bad");
    }
}

///theta(1)
bool SetIterator::valid() const {
    if (this->currentPosition != NOT_VALID)
        return true;
    return false;
}


///O(capacity)
void SetIterator::previous() {
    if (!valid()) {
        throw std::runtime_error("Iterator is not valid");
    }

    currentPosition--;
    while ( currentPosition >= 0 && (this->getCurrent() == EMPTY_POSITION || this->getCurrent() == DELETED_POSITION))
    {
        currentPosition--;
    }
    if (currentPosition < 0)
        currentPosition = NOT_VALID;
}