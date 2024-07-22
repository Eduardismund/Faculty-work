#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->current = 0;
}

//theta(1)
TComp SortedBagIterator::getCurrent() {
    if (this->current >= this->bag.length)
        throw exception();
    return this->bag.e[this->current];
}

//theta(1)
bool SortedBagIterator::valid() {
	if (this->current < this->bag.length)
        return true;
	return false;
}

//theta(1)
void SortedBagIterator::next() {
    if (this->current >= this->bag.length)
        throw exception();
	this->current+=1;
}

//theta(1)
void SortedBagIterator::first() {
	this->current= 0;
}

