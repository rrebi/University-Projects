#include "SortedSet.h"
#include "SortedSetIterator.h"

//Theta(1)
SortedSet::SortedSet(Relation r) {
	//TODO - Implementation
	this->relation = r;
	this->head = nullptr;
	this->tail = nullptr;
	this->length = 0;
}

//BC: Theta(1), WC: Theta(nrNodes), Total: O(nrNodes)
bool SortedSet::add(TComp elem) {
	//TODO - Implementation

    if (search(elem))
        return false;

    if (this->length == 0) {
        Node* newNode = new Node();
        newNode->info.first = elem;
        newNode->info.second = 1;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        this->head = newNode;
        this->tail = newNode;
        this->length++;
        return true;
    }
    else {
        Node* currentNode = this->head;
        bool found = false;
        while (currentNode != nullptr && !found && this->relation(currentNode->info.first, elem)) {
            if (currentNode->info.first == elem) {
                currentNode->info.second++;
                this->length++;
                found = true;
            }
            else
                currentNode = currentNode->next;
        }
        if (!found) {
            if (currentNode == this->head && currentNode != nullptr) {
                Node* newNode = new Node();
                newNode->info.first = elem;
                newNode->info.second = 1;
                newNode->prev = nullptr;
                newNode->next = currentNode;
                currentNode->prev = newNode;
                this->head = newNode;
                this->length++;
                return true;
            }
            else if (currentNode == nullptr) {
                Node* newNode = new Node();
                newNode->info.first = elem;
                newNode->info.second = 1;
                newNode->next = currentNode;
                newNode->prev = this->tail;
                this->tail->next = newNode;
                this->tail = newNode;
                this->length++;
                return true;
            }
            else {
                Node* newNode = new Node();
                newNode->info.first = elem;
                newNode->info.second = 1;
                newNode->prev = currentNode->prev;
                newNode->next = currentNode;
                currentNode->prev->next = newNode;
                currentNode->prev = newNode;
                this->length++;
                return true;
            }
        }
    }
}


//BC: Theta(1), WC: Theta(nrNodes), Total: O(nrNodes)
bool SortedSet::remove(TComp elem) {
    //TODO - Implementation
    bool found = false;

    if (!search(elem) || isEmpty())
        return false;

    Node* currentNode = this->head;

    while (currentNode != nullptr && !found && this->relation(currentNode->info.first, elem)) {
        if (currentNode->info.first == elem) {
            found = true;
        }
        else {
            currentNode = currentNode->next;
        }
    }
    Node* delNode = currentNode;

    if (currentNode != nullptr)
    {
        this->length--;
        if (currentNode == this->head)
            if (currentNode == this->tail)
            {
                this->head = nullptr;
                this->tail = nullptr;
            }
            else
            {
                this->head = this->head->next;
                this->head->prev = nullptr;
            }
        else if (currentNode == this->tail)
        {
            this->tail = this->tail->prev;
            this->tail->next = nullptr;
        }
        else
        {
            currentNode->next->prev = currentNode->prev;
            currentNode->prev->next = currentNode->next;
        }
        delete delNode;
        return true;
    }
    return false;
}


//BC: Theta(1), WC: Theta(nrNodes), Total: O(nrNodes)
bool SortedSet::search(TElem elem) const
{
    //TODO - Implementation
    Node* currentNode = this->head;
    bool found = false;
    while (currentNode != nullptr && !found && this->relation(currentNode->info.first, elem)) {
        if (currentNode->info.first == elem) {
            found = true;
        }
        else {
            currentNode = currentNode->next;
        }
    }
    return found;
}


//Theta(1)
int SortedSet::size() const {
	//TODO - Implementation
	return this->length;
}


//Theta(1)
bool SortedSet::isEmpty() const {
	//TODO - Implementation
	if (this->head != nullptr)
		return false;
	return true;
}


SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}

//Theta(nrNodes)
SortedSet::~SortedSet() {
	//TODO - Implementation

	Node* prevNode = nullptr;
	Node* currentNode = this->head;
	while (currentNode != nullptr) {
		prevNode = currentNode;
		currentNode = currentNode->next;
		delete prevNode;
	}
}


void SortedSet::unionFct(const SortedSet& s)
{
    Node* currentNode = s.head;

    while (currentNode != nullptr) {
        add(currentNode->info.first);
        currentNode = currentNode->next;
    }
}



