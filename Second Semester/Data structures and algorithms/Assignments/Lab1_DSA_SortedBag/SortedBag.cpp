#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <exception>

//theta(1)
SortedBag::SortedBag(Relation r) {
    this->capacity = 1;
	this->e= new TElem[this->capacity];
    this->length = 0;
    this->r = r;
}

//BC: theta(1)
//WC: theta(n)
//total: O(n)

void SortedBag::add(TComp e) {
    if( this->length == this->capacity) {
        resize();
    }
    int pos = 0;
    while (pos < this->length && this->r(this->e[pos], e)) {
        pos++;
    }

    for (int i = this->length; i > pos; i--) {
        this->e[i] = this->e[i - 1];
    }

    this->e[pos] = e;
    this->length++;
}

//theta(n)
void SortedBag::resize() {
    capacity *= 2;
    TElem *newE = new TElem[capacity];
    for (int i = 0; i < this->length; i++)
        newE[i] = e[i];
    delete[] e;
    e = newE;
}

//BC: theta(1)
//WC: theta(n)
//total: O(n)
bool SortedBag::remove(TComp e) {
	int pos = 0;
    while(pos < this->length && this->e[pos]!=e)
        pos++;
    if (pos == this->length)
        return false;
    for(int i = pos; i < this->length; i++)
        this->e[i]= this->e[i+1];
    this->length -=1;
	return true;
}

//BC: theta(1)
//WC: theta(n)
//total: O(n)
bool SortedBag::search(TComp elem) const {
	for(int i = 0; i<this->length;i++)
        if( this->e[i] == elem )
            return true;
	return false;
}

//theta(n)
int SortedBag::nrOccurrences(TComp elem) {
    int cnt = 0;
    for(int i=0; i<(this->length); i++)
        if(elem == this->e[i])
            cnt++;
	return cnt;
}


//theta(1)
int SortedBag::size() {
	return this->length;
}

//theta(1)
bool SortedBag::isEmpty() const {
	if(this->length == 0)
        return true;
	return false;
}

//theta(1)
SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}

//theta(1)
SortedBag::~SortedBag() {
	delete[] this->e;
}


///BC: theta(1)
///WC: theta(this->length)
/// total: theta(this->length)
int SortedBag::removeOccurrences(int nr, TElem elem) {
    int removedCount = 0;

    if (nr < 0)
        throw std::exception();

    for (int i = 0; i < this->length; i++) {
        if (this->e[i] == elem && removedCount < nr) {
            removedCount++;
        } else {
            this->e[i - removedCount] = this->e[i];
        }
    }

    this->length -= removedCount;
    return removedCount;
}


