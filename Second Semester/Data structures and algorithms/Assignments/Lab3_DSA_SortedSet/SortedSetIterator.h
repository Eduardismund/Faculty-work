#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& multime;
	SortedSetIterator(const SortedSet& m);

	TElem current;

public:
	void first();
	void next();
    void previous();
	TElem getCurrent();
	bool valid() const;
};

