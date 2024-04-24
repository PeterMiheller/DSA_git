#include "MultiMapIterator.h"
#include "MultiMap.h"

//Complexity:
//Best Case == Worst Case == Average Case == theta(1)
MultiMapIterator::MultiMapIterator(const MultiMap &c) : col(c) {
    //TODO - Implementation
    this->current_element = this->col.head;
}

//Complexity:
//Best Case == Worst Case == Average Case == theta(1)
TElem MultiMapIterator::getCurrent() const {
    //TODO - Implementation
    if (!valid())
        throw exception();
    else
        return this->col.nodes[this->current_element].info;
}

//Complexity:
//Best Case == Worst Case == Average Case == theta(1)
bool MultiMapIterator::valid() const {
    //TODO - Implementation
    if (this->current_element == -1)
        return false;
    return true;
}

//Complexity:
//Best Case == Worst Case == Average Case == theta(1)
void MultiMapIterator::next() {
    //TODO - Implementation
    if (!valid())
        throw exception();
    else
        this->current_element = col.nodes[this->current_element].next;


}

//Complexity:
//Best Case == Worst Case == Average Case == theta(1)
void MultiMapIterator::first() {
    //TODO - Implementation
    this->current_element = this->col.head;
}

