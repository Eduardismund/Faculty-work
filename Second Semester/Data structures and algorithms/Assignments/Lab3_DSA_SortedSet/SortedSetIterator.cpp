#include "SortedSetIterator.h"
#include <exception>

using namespace std;

///theta(1)
SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	this->current=m.head;
}

///theta(1)
void SortedSetIterator::first() {
    this->current=this->multime.head;
}

///theta(1)
void SortedSetIterator::next() {
	if(!valid())
        throw std::exception();
    this->current=this->multime.nodes[this->current].next;
}

///theta(1)
TElem SortedSetIterator::getCurrent()
{
	if(!valid())
        throw std::exception();
    return this->multime.nodes[this->current].element;
}

///theta(1)
bool SortedSetIterator::valid() const {
	return this->current!=-1;
}


