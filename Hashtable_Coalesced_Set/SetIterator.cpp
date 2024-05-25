#include "SetIterator.h"
#include "Set.h"
#include <iostream>
using namespace std;


SetIterator::SetIterator(const Set& m) : set(m)
{
    //TODO - Implementation
    //Complexity:
    //- Best Case: Theta(1)
    //- Worst Case: Theta(n)
    //- Average Case: Theta(1)
    //- General Case: O(n)
    this->current = 0;
    move_iterator();
}


void SetIterator::first() {
    //TODO - Implementation
    //Complexity:
    //- Best Case: Theta(1)
    //- Worst Case: Theta(n)
    //- Average Case: Theta(1)
    //- General Case: O(n)
    this->current = 0;
    move_iterator();
}


void SetIterator::next() {
    //TODO - Implementation
    //Complexity:
    //- Best Case: Theta(1)
    //- Worst Case: Theta(n)
    //- Average Case: Theta(1)
    //- General Case: O(n)
    if(!valid())
        throw exception();
    this->current++;
    move_iterator();
}


TElem SetIterator::getCurrent()
{
    //TODO - Implementation
    //Complexity:
    //Theta(1)
    if(!valid())
        throw exception();
    return this->set.elements[this->current];

}

bool SetIterator::valid() const {
    //TODO - Implementation
    //Complexity:
    //Theta(1)
    if(this->current < this->set.capacity && this->set.elements[this->current] != NULL_TELEM)
        return true;
    return false;

}

void SetIterator::move_iterator() {
    //Complexity:
    //- Best Case: Theta(1)
    //- Worst Case: Theta(n) -if the set is full of empty slots
    //- Average Case: Theta(1)
    //- General Case: O(n)
    // if the current element reached the end of the array
    // or the current element is NULL_TELEM, then we move to the next element
    while ((this->current < this->set.capacity) && this->set.elements[this->current] == NULL_TELEM )
        this->current++;
}


