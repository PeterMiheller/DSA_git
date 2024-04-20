#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

//Complexity: theta(1)
BagIterator::BagIterator(const Bag& c): bag(c){
    // Initialize the iterator to the beginning (head) of the bag
    //this->current_node = nullptr;
    this->current_node = c.head;
    this->currentFrequency = 1;
}
//Complexity: theta(1)
void BagIterator::first() {
    // Set the iterator to the beginning (head) of the bag
    this->current_node = this->bag.head;
}

//Complexity: theta(1)
void BagIterator::next() {
    if (!valid()) {
        throw exception();
    }else{
        if (this->currentFrequency < this->current_node->frequenz) {
            this->currentFrequency++;
        }else{
            this->current_node = this->current_node->next;
            this->currentFrequency = 1;}
    }
}

//Complexity: theta(1)
bool BagIterator::valid() const {
    // Check if the iterator is pointing to a valid node
    if (this->current_node == nullptr) {
        return false;
    }
    return true;
}


//Complexity: theta(1)
TElem BagIterator::getCurrent() const{
    if (!valid()) {
        throw exception();
    }else
        // Return the element at the current position
        return this->current_node->element;

}
