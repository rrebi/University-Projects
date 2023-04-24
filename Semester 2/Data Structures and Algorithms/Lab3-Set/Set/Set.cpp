#include "Set.h"
#include "SetITerator.h"
#include <exception>
 
using namespace std;

//WC=AC=BC=Theta(n), => overall complexity = theta(n), where n = initial capacity
Set::Set() {
	//TODO - Implementation
	this->dlla.capacity = cap;
	this->dlla.head = -1;
	this->dlla.tail = -1;
	this->dlla.size = 0;
	this->dlla.firstEmpty = 0;

	this->dlla.nodes = new node[cap];

	for (int i = 0; i < cap - 1; i++) {
		this->dlla.nodes[i].next = i + 1;
	}
	this->dlla.nodes[cap - 1].next = -1;

	for (int i = 1; i < cap; i++) {
		this->dlla.nodes[i].prev = i - 1;
	}
	this->dlla.nodes[0].prev = -1;
}


//WC=AC=Theta(n), BC = Theta(1) => overall complexity = O(n)
void Set::insertPosition(TElem e, int pos)
{	
	
	if (pos<0 || pos>dlla.size + 1)
		throw exception();
	
	int newElem = allocate();
	if (newElem == -1) {
		resize();
		newElem = allocate();
	}
	dlla.nodes[newElem].info = e;
	if (pos == 0) {
		if (dlla.head == -1) {
			dlla.head = newElem;
			dlla.tail = newElem;
		}
		else {
			dlla.nodes[newElem].next = dlla.head;
			dlla.nodes[dlla.head].prev = newElem;
			dlla.head = newElem;
		}
	}
	else {
		int currentNode = dlla.head;
		int currentPos = 0;
		while (currentNode != -1 && currentPos < pos - 1) {
			currentNode = dlla.nodes[currentNode].next;
			currentPos++;
		}
		if (currentNode != -1) {
			int nodNext = dlla.nodes[currentNode].next;
			dlla.nodes[newElem].next = nodNext;
			dlla.nodes[newElem].prev = currentNode;
			dlla.nodes[currentNode].next = newElem;
			if (nodNext == -1) {
				dlla.tail = newElem;
			}
			else {
				dlla.nodes[nodNext].prev = newElem;
			}
		}
	}
}

//WC=AC=BC=Theta(n), => overall complexity = theta(n), where n = capacity
void Set::resize()
{
	node* newElems = new node[dlla.capacity * 2];

	//copy the first half
	for (int i = 0; i < dlla.capacity; i++)
		newElems[i] = dlla.nodes[i];

	//init the second half nexts
	for (int i = dlla.capacity;i < 2 * dlla.capacity - 1;i++)
	{
		newElems[i].next = i + 1;
	}
	newElems[dlla.capacity * 2 - 1].next = -1;

	//init the second half prevs
	for (int i = dlla.capacity + 1; i < 2 * dlla.capacity; i++)
	{
		newElems[i].prev = i - 1;
	}
	newElems[dlla.capacity].prev = -1;

	//copy the other stuff and double capacity
	dlla.firstEmpty = dlla.capacity;
	dlla.capacity *= 2;
	delete[] dlla.nodes;
	dlla.nodes = newElems;
}

//WC=AC=BC=Theta(1) => overall complexity = theta(1)
int Set::allocate()
{
	int newElem = dlla.firstEmpty;
	if (newElem != -1) {
		dlla.nodes[dlla.firstEmpty].prev = -1;
		dlla.firstEmpty = dlla.nodes[dlla.firstEmpty].next;
		dlla.nodes[newElem].next = -1;
		dlla.nodes[newElem].prev = -1;
	}
	return newElem;
}

//WC=AC=BC=Theta(1) => overall complexity = theta(1)
void Set::free(int poz)
{
	dlla.nodes[poz].next = dlla.firstEmpty;
	dlla.nodes[poz].prev = -1;
	if(dlla.firstEmpty != -1)
		dlla.nodes[dlla.firstEmpty].prev = poz;
	dlla.firstEmpty = poz;
}

//WC=AC=Theta(n), BC = Theta(1) => overall complexity = O(n)
bool Set::add(TElem elem) {
	//TODO - Implementation
	if (search(elem))
		return false;
	int current = dlla.head;
	int currentPosition = 0;
	while (current != -1 && currentPosition < this->size() && dlla.nodes[current].info != elem) {
		current = dlla.nodes[current].next;
		currentPosition++;
	}
	insertPosition(elem, currentPosition);
	this->dlla.size++;
	return true;
}

//WC=AC=Theta(n), BC = Theta(1) => overall complexity = O(n)
bool Set::remove(TElem elem) {
	//TODO - Implementation
	if (!search(elem))
		return false;
	int currentNode = this->dlla.head;
	int previousNode = -1;
	while (currentNode != -1 || size()>0) {
		if (this->dlla.nodes[currentNode].info == elem) {
			if (currentNode == this->dlla.head) {
				this->dlla.head = this->dlla.nodes[currentNode].next;
			}
			if (currentNode == this->dlla.tail) {
				this->dlla.tail = this->dlla.nodes[currentNode].prev;
			}
			if (this->dlla.nodes[currentNode].next != -1) {
				this->dlla.nodes[previousNode].next = this->dlla.nodes[currentNode].prev;
			}
			if (this->dlla.nodes[currentNode].prev != -1) {
				this->dlla.nodes[previousNode].next = this->dlla.nodes[currentNode].next;
			}
			this->free(currentNode);
			this->dlla.size--;
			return true;
		}
		previousNode = currentNode;
		currentNode = this->dlla.nodes[currentNode].next;

	}
	return false;
}

//WC=AC=Theta(n), BC = Theta(1) => overall complexity = O(n)
bool Set::search(TElem elem) const {
	//TODO - Implementation
	if (isEmpty())
		return false;
	int currentNode = dlla.head;
	while (currentNode != -1) {
		if (dlla.nodes[currentNode].info == elem)
			return true;
		currentNode = dlla.nodes[currentNode].next;
	}
	return false;
}

//WC=AC=BC=Theta(1) => overall complexity = theta(1)
int Set::size() const {
	//TODO - Implementation
	return this->dlla.size;
}

//WC=AC=BC=Theta(1) => overall complexity = theta(1)
bool Set::isEmpty() const {
	//TODO - Implementation
	return this->dlla.size == 0;
}

//WC=AC=BC=Theta(1) => overall complexity = theta(1)
Set::~Set() {
	//TODO - Implementation
	delete[]dlla.nodes;
}

//WC=AC=BC=Theta(1) => overall complexity = theta(1)
SetIterator Set::iterator() const {
	return SetIterator(*this);
}


