#include "SortedSetIterator.h"
#include <exception>

using namespace std;

//Theta(1)
SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	//TODO - Implementation
	this->currentNode = m.head;
	this->currentFrequency = 1;
}

//Theta(1)
void SortedSetIterator::first() {
	//TODO - Implementation
	this->currentNode = this->multime.head;
	this->currentFrequency = 1;
}

//Theta(1)
void SortedSetIterator::next() {
	//TODO - Implementation
	if (this->currentNode != nullptr) {
		if (this->currentFrequency == this->currentNode->info.second) {
			this->currentNode = this->currentNode->next;
			this->currentFrequency = 1;
		}
		else {
			this->currentFrequency++;
		}
	}
	else
		throw exception();
}

//Theta(1)
TElem SortedSetIterator::getCurrent()
{
	//TODO - Implementation
	if (this->currentNode == nullptr)
		throw exception();
	return this->currentNode->info.first;
}

//Theta(1)
bool SortedSetIterator::valid() const {
	//TODO - Implementation
	if (this->currentNode == nullptr)
		return false;
	else
		return true;
}

