#include "ShortTest.h"
#include <assert.h>
#include <exception>
#include "Bag.h"
#include "BagIterator.h"


void testAll() { 
	Bag b;
	assert(b.isEmpty() == true);
	assert(b.size() == 0); 
	b.add(5);
	b.add(1);
	b.add(10);
	b.add(7);
	b.add(1);
	b.add(11);
	b.add(-3);
	assert(b.size() == 7);
	assert(b.search(10) == true);
	assert(b.search(16) == false);
	assert(b.nrOccurrences(1) == 2);
	assert(b.nrOccurrences(7) == 1);
	assert(b.remove(1) == true);
	assert(b.remove(6) == false);
	assert(b.size() == 6);
	assert(b.nrOccurrences(1) == 1);
	BagIterator it = b.iterator();
	it.first();
	while (it.valid()) {
		TElem e = it.getCurrent();
		it.next();
	}

    ///test functionality

    Bag c;
    int l;
    c.add(5);
    c.add(1);
    c.add(10);
    c.add(7);
    c.add(1);
    c.add(11);
    c.add(5);
    ///add
    c.addOccurrences(3,5);
    assert(c.nrOccurrences(5)== 5);
    l=c.size();

    ///create a new element and increases the length
    c.addOccurrences(4,4);
    assert(c.nrOccurrences(4)==4);
    assert(c.size()==l+1);

    try {
        c.addOccurrences(-2, 5);
        assert(false);
    } catch (const std::exception& e) {
        assert(true);
    }
}
