#include "SortedSet.h"
#include "SortedSetIterator.h"

///theta(cap)
SortedSet::SortedSet(Relation r){
    this->nodes = new DLLANode[10];
    this->cap=10;
    this->length=0;
    this->head=-1;
    this->tail=-1;
    this->relation=r;
    for (int i = 0; i < cap; i++) {
        this->nodes[i].next = i + 1;
        this->nodes[i].prev = -1;
    }
    this->nodes[this->cap-1].next = -1;
    this->nodes[this->cap-1].prev = -1;
    this->firstEmpty = 0;
}

///theta(1)
int SortedSet::allocate() {
    TElem newElem = this->firstEmpty;
    if (newElem != -1) {
        this->firstEmpty = this->nodes[this->firstEmpty].next;
        if (this->firstEmpty != -1)
            this->nodes[this->firstEmpty].prev = -1;
        this->nodes[newElem].next = -1;
        this->nodes[newElem].prev = -1;
    }
    return newElem;
}

///B.c: theta(1), W.c: theta(length), Total: O(length)
bool SortedSet::add(TComp elem) {
    if(search(elem))
        return false;

    int new_index = allocate();
    if (new_index == -1) {
        DLLANode* newNodes = new DLLANode[this->cap * 2];
        for (int i = 0; i < this->cap; i++) {
            newNodes[i].prev = this->nodes[i].prev;
            newNodes[i].element = this->nodes[i].element;
            newNodes[i].next = this->nodes[i].next;
        }
        for (int i = this->cap; i < this->cap * 2 - 1; i++) {
            newNodes[i].next = i + 1;
            newNodes[i].prev = - 1;
        }
        newNodes[this->cap * 2 - 1].next = -1;
        newNodes[this->cap * 2 - 1].prev = -1;
        delete[] this->nodes;
        this->nodes = newNodes;
        this->firstEmpty = this->cap;
        this->cap = this->cap * 2;


        new_index = this->allocate();
    }


    this->nodes[new_index].element = elem;


    int current = this->head;
    int prev = -1;
    while (current != -1 && this->relation(this->nodes[current].element, elem)) {
        prev = current;
        current = this->nodes[current].next;
    }


    if (prev == -1) {

        this->nodes[new_index].next = this->head;
        if (this->head != -1)
            this->nodes[this->head].prev = new_index;
        this->head = new_index;
        if (this->tail == -1)
            this->tail = new_index;
    } else {

        this->nodes[new_index].next = current;
        this->nodes[new_index].prev = prev;
        this->nodes[prev].next = new_index;
        if (current != -1)
            this->nodes[current].prev = new_index;
        else
            this->tail = new_index;
    }

    this->length++;

    return true;
}

///B.c: theta(1), W.c: theta(length), Total: O(length)
bool SortedSet::remove(TComp elem) {
    int pos = this->searchPosition(elem);
    if (pos == -1)
        return false;

    if (pos == this->head) {
        this->head = this->nodes[pos].next;
        if (this->head != -1)
            this->nodes[this->head].prev = -1;
    } else {
        int prev = this->nodes[pos].prev;
        int next = this->nodes[pos].next;
        this->nodes[prev].next = next;
        if (next != -1)
            this->nodes[next].prev = prev;
        else
            this->tail = prev;
    }


    this->nodes[pos].next = this->firstEmpty;
    this->nodes[pos].prev = -1;
    if (this->firstEmpty != -1)
        this->nodes[this->firstEmpty].prev = pos;
    this->firstEmpty = pos;
    this->length--;

    return true;
}

///B.c: theta(1), W.c: theta(length), Total: O(length)
bool SortedSet::search(TComp elem) const {
    int current = this->head;

    while (current != -1) {
        if (this->nodes[current].element == elem && this->relation(this->nodes[current].element, elem)) {
            return true;
        }
        current = this->nodes[current].next;
    }

    return false;
}



///B.c: theta(1), W.c: theta(length), Total: O(length)
int SortedSet::searchPosition(TComp e){
    int current = this->head;

    while (current != -1) {
        if (this->nodes[current].element == e && this->relation(this->nodes[current].element, e)) {
            return current;
        }
        current = this->nodes[current].next;
    }

    return -1;
}

///theta(1)
int SortedSet::size() const {
	return length;
}


///theta(1)
bool SortedSet::isEmpty() const {
    if (this->length == 0)return true;
    return false;
}

///theta(1)
SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {
    delete[] this->nodes;
}