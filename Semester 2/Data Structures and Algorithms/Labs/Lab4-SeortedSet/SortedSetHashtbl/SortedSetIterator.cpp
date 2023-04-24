#include "SortedSetIterator.h"
#include <exception>

using namespace std;

// theta(MOD)
SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
    //clone the hashtable locally
    itHashTable = new Node * [m.MOD];

    first();
}

void SortedSetIterator::first()
// theta(MOD)
{
    //clone the hashtable locally
    for (int i = 0; i < multime.MOD; i++)
        itHashTable[i] = multime.hashTable[i].head;

    //search for minimum value (with respect to the relation) from the locally cloned hashtable
    Node* first = nullptr;
    int position;
    for (int i = 0; i < multime.MOD; i++)
    {
        if (itHashTable[i] == nullptr)
            continue;

        if (first == nullptr || multime.relation(itHashTable[i]->value, first->value))
        {
            first = itHashTable[i];
            position = i;
        }
    }

    //minimum was found
    if (first != nullptr)
    {
        currentElement = first->value;
        itHashTable[position] = itHashTable[position]->next; // eliminate node 'first' from the locally cloned hashTable
    }
    else
        currentElement = NULL_TELEM;
}


void SortedSetIterator::next()
// theta(MOD)
{
    //if iterator not valid throw exception
    if (!valid())
        throw std::exception();

    //search for next element
    Node* next = nullptr;
    int position;
    for (int i = 0; i < multime.MOD; i++)
    {
        //empty sll at this hashvalue
        if (itHashTable[i] == nullptr) continue;

        //if next was not found yet or there is a value closer to the current one that satisfies the relation => next = newValue
        if (next == nullptr || multime.relation(itHashTable[i]->value, next->value))
        {
            next = itHashTable[i];
            position = i;
        }
    }
    //next element was found
    if (next != nullptr)
    {
        //set current element to next and eliminate the node 'next' from the iterator hashTable
        currentElement = next->value;
        itHashTable[position] = itHashTable[position]->next;
    }
    else
        currentElement = NULL_TELEM;
}

// theta(1)
TElem SortedSetIterator::getCurrent()
{
    if (!valid())
        throw std::exception();
    return currentElement;
}



bool SortedSetIterator::valid() const
// theta(1)
{
    return (currentElement != NULL_TELEM);
}
