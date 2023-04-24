#pragma once
#include "SortedIndexedList.h"
#include<stack>

//DO NOT CHANGE THIS PART
class ListIterator {
	friend class SortedIndexedList;
private:
	const SortedIndexedList& list;
	ListIterator(const SortedIndexedList& list);

	//TODO - Representation
	int currentPosition;


public:
	void first();
	void next();
	bool valid() const;
	TComp getCurrent() const;
};


