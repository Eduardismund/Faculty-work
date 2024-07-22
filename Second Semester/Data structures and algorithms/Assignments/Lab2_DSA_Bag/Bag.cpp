#include "Bag.h"
#include "BagIterator.h"
#include <exception>

// Constructor
Bag::Bag() {
    head = nullptr;
    length = 0;
}

///BC: theta(1)->found on first position
///WC: theta(n)->goes through the whole linked list and doesn't find it
///Total: O(n)
void Bag::add(TElem elem) {
    Node* current = head;
    while (current != nullptr) {
        if (current->element == elem) {
            current->frequency++;
            length++;
            return;
        }
        current = current->next;
    }
    Node* newNode = createNode(elem, 1);
    newNode->next = head;
    head = newNode;
    length++;
}

///BC: theta(1)->the head needs to be removed
///WC: theta(n)->goes through the whole linked list
///Total: O(n)
bool Bag::remove(TElem elem) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->element == elem) {
            if (current->frequency > 1) {
                current->frequency--;
            } else {
                if (previous != nullptr) {
                    previous->next = current->next;
                } else {
                    head = current->next;
                }
                delete current;
            }
            length--;
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
}

///BC: theta(1)->found on first position
///WC: theta(n)->goes through the whole linked list
///Total: O(n)
bool Bag::search(TElem elem) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->element == elem) {
            return true;
        }
        current = current->next;
    }
    return false;
}

///theta(1)
BagIterator Bag::iterator() const {
    return BagIterator(*this);
}

///BC: theta(1)->found on first position
///WC: theta(n)->goes through the whole linked list
///Total: O(n)

int Bag::nrOccurrences(TElem elem) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->element == elem) {
            return current->frequency;
        }
        current = current->next;
    }
    return 0;
}

// theta(1)
int Bag::size() const {
    return length;
}

// theta(1)
bool Bag::isEmpty() const {
    return length == 0;
}

// theta(n)
Bag::~Bag() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    length = 0;
}


Node* Bag::createNode(TElem e, int freq) {
    return new Node(e, freq);
}


///BC: theta(1)
///WC: theta(n)
///total: O(n)
void Bag::addOccurrences(int nr, TElem elem) {
    if(nr<0)
    {
        throw std::exception();
    }
    Node* current = head;
    while(current)
    {
        if(current->element==elem) {
            current->frequency += nr;
            return;
        }
        current=current->next;
    }
    Node* newNode = createNode(elem, nr);
    newNode->next=head;
    head = newNode;
    length++;
}
