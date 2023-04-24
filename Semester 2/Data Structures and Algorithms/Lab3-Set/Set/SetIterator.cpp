#include "SetIterator.h"
#include "Set.h"
#include <exception>

//WC=AC=BC=Theta(1) => overall complexity = theta(1)
SetIterator::SetIterator(const Set& m) : set(m)
{
	//TODO - Implementation
	this->list = m.dlla;
	this->currentElement = m.dlla.head;
}

//WC=AC=BC=Theta(1) => overall complexity = theta(1)
void SetIterator::first() {
	//TODO - Implementation
	this->currentElement = set.dlla.head;
}

//WC=AC=BC=Theta(1) => overall complexity = theta(1)
void SetIterator::next() {
	//TODO - Implementation

	if (!valid()) {
		throw std::exception();
	}
	this->currentElement = this->list.nodes[this->currentElement].next;
}

//WC=AC=BC=Theta(1) => overall complexity = theta(1)
TElem SetIterator::getCurrent()
{
	//TODO - Implementation
	if (!valid()) {
		throw std::exception();
	}
	return this->list.nodes[this->currentElement].info;
}

//WC=AC=BC=Theta(1) => overall complexity = theta(1)
bool SetIterator::valid() const {
	//TODO - Implementation

	return this->currentElement != -1;
}


//WC=AC=BC=theta(k)
void SetIterator::jumpForward(int k)
{
	if (k <= 0 || !valid())
		throw std::exception();
	
	while (k > 0) {
		if (this->currentElement = set.dlla.tail)
		{
			if (k > 1)
				!valid();
			else
				this->currentElement = +1;
		}
		next();
		k--;
	}
}



