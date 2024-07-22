#pragma once
#define NULL_TELEM -111111

typedef int TElem;

class BagIterator;

struct Node {
    TElem element;
    int frequency;
    Node* next;

    Node(TElem e, int freq) : element(e), frequency(freq), next(nullptr) {}
};

class Bag {
private:
    Node* head;
    int length;


public:
    // Constructor
    Bag();

    // Adds an element to the bag
    void add(TElem e);

    // Removes one occurrence of an element from the bag
    // Returns true if an element was removed, false otherwise
    bool remove(TElem e);

    // Checks if an element appears in the bag
    bool search(TElem e) const;

    // Returns the number of occurrences for an element in the bag
    int nrOccurrences(TElem e) const;

    // Returns the number of elements in the bag
    int size() const;

    // Returns an iterator for this bag
    BagIterator iterator() const;

    // Checks if the bag is empty
    bool isEmpty() const;

    // Destructor
    ~Bag();

    Node* getHead() const {
        return head;
    }

    void addOccurrences(int nr, TElem elem);

private:

    static Node* createNode(TElem e, int freq);

};
