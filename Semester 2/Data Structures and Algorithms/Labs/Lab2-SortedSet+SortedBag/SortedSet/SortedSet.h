#pragma once
//DO NOT INCLUDE SETITERATOR

#include <utility>

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef TElem TComp;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TELEM -11111
class SortedSetIterator;

//TODO node
struct Node {
	//TElem info;
	std::pair<TComp, int> info;
	Node* prev;
	Node* next;
};

class SortedSet {
	friend class SortedSetIterator;
private:
	//TODO - Representation
	Relation relation;
	Node* head;
	Node* tail;
	int length;

public:
	//constructor
	SortedSet(Relation r);


	//adds an element to the sorted set
	//if the element was added, the operation returns true, otherwise (if the element was already in the set) 
	//it returns false
	bool add(TComp e);

	
	//removes an element from the sorted set
	//if the element was removed, it returns true, otherwise false
	bool remove(TComp e);

	//checks if an element is in the sorted set
	bool search(TElem elem) const;


	//returns the number of elements from the sorted set
	int size() const;

	//checks if the sorted set is empty
	bool isEmpty() const;

	//returns an iterator for the sorted set
	SortedSetIterator iterator() const;

	// destructor
	~SortedSet();

	//adds all elements of s into the SortedSet (assume both sets use the same relation)
	void unionFct(const SortedSet& s);
};
