#include <assert.h>
#include <exception>
#include <iostream>
#include "Matrix.h"

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
 	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);


    m.setMainDiagonal(7);
    assert(m.element(0, 0) == 7);
    assert(m.element(1, 1) == 7);
    assert(m.element(2, 2) == 7);
    assert(m.element(3, 3) == 7);

    Matrix n(4, 5);
    try {
        n.setMainDiagonal(8);
        assert(false);
    } catch (exception& e){
        assert(true);
    }
}
