#include "ShortTest.h"
#include <assert.h>
#include "Set.h"
#include "SetIterator.h"
#include <stdexcept>

void testAll() { 
	Set s;
	assert(s.isEmpty() == true);
	assert(s.size() == 0); 
	assert(s.add(5)==true);
	assert(s.add(1)==true);
	assert(s.add(10)==true);
	assert(s.add(7)==true);
	assert(s.add(1)==false);
	assert(s.add(10)==false);
	assert(s.add(-3)==true);
	assert(s.size() == 5);
	assert(s.search(10) == true);
	assert(s.search(16) == false);
	assert(s.remove(1) == true);
	assert(s.remove(6) == false);
	assert(s.size() == 4);


	SetIterator it = s.iterator();
	it.first();
	int sum = 0;
	while (it.valid()) {
		TElem e = it.getCurrent();
		sum += e;
		it.next();
	}
	assert(sum == 19);

    it.first();
    assert(it.getCurrent() == -3);
    it.next();
    assert(it.getCurrent() == 5);
    it.next();
    assert(it.getCurrent() == 7);
    it.next();
    assert(it.getCurrent() == 10);
    it.previous();
    assert(it.getCurrent() == 7);
    it.previous();
    assert(it.getCurrent() == 5);
    it.previous();
    assert(it.getCurrent() == -3);
    it.previous();
    assert(it.valid() == false);

    try {
        it.previous();
        assert(false);
    } catch (const std::runtime_error& e) {
        assert(true);
    }
}

