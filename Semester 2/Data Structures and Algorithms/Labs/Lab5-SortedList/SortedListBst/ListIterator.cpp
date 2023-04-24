#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

//WC=AC=BC=Theta(1), => overall complexity = theta(1)
ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	//TODO - Implementation
	this->currentPosition = 0;
}

//WC=AC=BC=Theta(1), => overall complexity = theta(1)
void ListIterator::first() {
	//TODO - Implementation
	this->currentPosition = 0;
}

//WC=AC=BC=Theta(1), => overall complexity = theta(1)
void ListIterator::next() {
	//TODO - Implementation
	if (!this->valid())
	{
		exception myex;
		throw myex;
	}
	this->currentPosition++;
}

//WC=AC=BC=Theta(1), => overall complexity = theta(1)
bool ListIterator::valid() const {
	//TODO - Implementation
	if (this->currentPosition < list.size())return true;
	return false;
}

//BC=O(1), WC=O(n), AC=O(log(n))
TComp ListIterator::getCurrent() const {
	//TODO - Implementation
	if (!this->valid())
	{
		exception myex;
		throw myex;
	}
	return list.getElement(this->currentPosition);
}



