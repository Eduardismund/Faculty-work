#include "Bag.h"

class BagIterator {
private:
    const Bag& bag;
    Node* currentNode; // Pointer to the current node being iterated over
    int currentFrequency; // Frequency of the current element

    void moveToNextElement(); // Helper function to move to the next distinct element

public:
    BagIterator(const Bag& c);

    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;
};

