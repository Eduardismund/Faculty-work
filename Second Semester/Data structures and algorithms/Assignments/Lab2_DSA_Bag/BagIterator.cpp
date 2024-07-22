#include <exception>
#include "BagIterator.h"
#include "Bag.h"

// theta(1)
BagIterator::BagIterator(const Bag& c) : bag(c) {
    currentNode = c.getHead();
    currentFrequency = 1;
}
// theta(1)
void BagIterator::first() {
    currentNode = bag.getHead();
    currentFrequency = 1;
}

// theta(1)
void BagIterator::next() {
    if (!valid())
        throw std::exception();

    if (currentFrequency < currentNode->frequency) {

        currentFrequency++;
        return;
    }

    currentNode = currentNode->next;
    currentFrequency = 1;
}
// theta(1)
bool BagIterator::valid() const {
    return currentNode != nullptr;
}

// theta(1)
TElem BagIterator::getCurrent() const {
    if (!valid()) {
        throw std::exception();
    }
    return currentNode->element;
}
