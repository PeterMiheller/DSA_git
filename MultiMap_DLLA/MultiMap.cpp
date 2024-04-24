#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

//Complexity:
//Best Case == Worst Case == Average Case == theta(n)
MultiMap::MultiMap() {
    //TODO - Implementation
    this->head = -1;
    this->tail = -1;
    this->firstEmpty = 0;
    this->nrElems = 0;
    this->cap = 10;
    this->nodes = new DLLANode[this->cap];
    // Initialize elements in the array
    for (int i = 0; i < this->cap - 1; i++) {// Initialize the next and previous pointers for each node
        this->nodes[i].next = i + 1;
        this->nodes[i].prev = i - 1;
        this->nodes[i].info = NULL_TELEM;
    }

    // Initialize the last node
    this->nodes[this->cap - 1].next = -1;// Set the next pointer of the last node to -1 (indicating the end of the list)
    this->nodes[this->cap - 1].prev = this->cap - 2;// Set the previous pointer of the last node to the second to last node
    this->nodes[this->cap - 1].info = NULL_TELEM;

}

//Complexity:
// - Best Case: theta(1)
// - Worst Case: theta(n)
// - Average Case: theta(n)
// - General Case: O(n)
void MultiMap::add(TKey c, TValue v) {
    //TODO - Implementation
    /*if (nrElems==cap) {
        resize();
        firstEmpty = nrElems;
    }*/
    TElem pair = std::make_pair(c, v);
    //Case 1: The list is empty!
    if (isEmpty()) {
        int newNodePos = allocate();
        this->nodes[newNodePos].info = pair;
        this->head = newNodePos;
        this->tail = newNodePos;
        this->nodes[newNodePos].next = -1;
        this->nodes[newNodePos].prev = -1;
        this->nrElems++;
        return;

    }

    // Case 2: the element will be placed after the tail
    int newNodePos = allocate();
    this->nodes[newNodePos].info = pair;
    this->nodes[newNodePos].prev = this->tail;
    this->nodes[newNodePos].next = -1;
    this->nodes[this->tail].next = newNodePos;
    this->tail = newNodePos;
    this->nrElems++;


}

//Complexity:
// - Best Case: theta(1)
// - Worst Case: theta(n)
// - Average Case: theta(n)
// - General Case: O(n)
bool MultiMap::remove(TKey c, TValue v) {
    //TODO - Implementation
    int current = this->head;
    while (current != -1) {
        if (this->nodes[current].info.first == c && this->nodes[current].info.second == v)// We found the element
        {
            //we have to remove the element from the list
            //Case 1:  the list have only one element
            if (current == this->head && current == this->tail) {
                this->head = -1;
                this->tail = -1;
            }
                //Case 2: the element we have to remove is the head
            else if (current == this->head) {
                this->head = this->nodes[current].next;
                this->nodes[this->head].prev = -1;
            }
                //Case 3: the element we have to remove is the tail
            else if (current == this->tail) {
                this->tail = this->nodes[current].prev;
                this->nodes[this->tail].next = -1;
            }
                //Case 4: the element we have to remove is somewhere between the head and the tail
            else {
                this->nodes[this->nodes[current].prev].next = this->nodes[current].next;
                this->nodes[this->nodes[current].next].prev = this->nodes[current].prev;
            }
            //We free the position of the deleted node
            free(current);
            this->nrElems--;
            return true;

        }
        current = this->nodes[current].next;
    }
    return false;

}

//Complexity:
//Best Case == Worst Case == Average Case == theta(n)
vector<TValue> MultiMap::search(TKey c) const {
    //TODO - Implementation
    vector<TValue> values;

    // Traverse the list starting from the head
    int current = this->head;
    while (current != -1) {
        if (this->nodes[current].info.first == c) { // If the key matches
            values.push_back(this->nodes[current].info.second);
        }
        current = this->nodes[current].next; // Move to the next node
    }

    return values;
}


//Complexity:
//Best Case == Worst Case == Average Case == theta(1)
int MultiMap::size() const {
    //TODO - Implementation
    return this->nrElems;
}


//Complexity:
//Best Case == Worst Case == Average Case == theta(1)
bool MultiMap::isEmpty() const {
    //TODO - Implementation
    if (this->nrElems == 0)
        return true;
    return false;
}

//Complexity:
//Best Case == Worst Case == Average Case == theta(1)
MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
}

//Complexity:
//Best Case == Worst Case == Average Case == theta(n)
void MultiMap::resize() {
    // Allocate a new array with the new capacity
    int newCapacity = this->cap * 2;
    DLLANode *newNodes = new DLLANode[newCapacity];

    // Copy elements from the old array to the new array
    for (int i = 0; i < this->nrElems; i++) {
        newNodes[i] = this->nodes[i];
    }

    // Deallocate the old array
    delete[] this->nodes;

    // Update the capacity and the pointer to the array
    this->cap = newCapacity;
    this->nodes = newNodes;

    // Reinitialize the elements added at the end of the new array
    for (int i = this->nrElems; i < this->cap - 1; i++) {
        this->nodes[i].next = i + 1;
        this->nodes[i].prev = i - 1;
        this->nodes[i].info = NULL_TELEM;
    }
    this->nodes[this->cap - 1].next = -1;// The last element in the array does not have a next element
    this->nodes[this->cap - 1].prev = this->cap - 2;// Update the pointer to the previous element of the last element in the array
    this->nodes[this->cap - 1].info = NULL_TELEM;

}

//Complexity:
//Best Case == Worst Case == Average Case == theta(1)
MultiMap::~MultiMap() {
    //TODO - Implementation
    delete[] this->nodes;
}

//Complexity:
// - Best Case: theta(1)
// - Worst Case: theta(n) if we do the resize
// - Amortized Case: O(n)/n = theta(1)
// - General Case: O(n)
int MultiMap::allocate() {

    //We check first if we reached the maximum capacity, and in this case we do a resize
    if (this->nrElems == this->cap) {//sau firstEmpty==-1
        resize();
        this->firstEmpty = this->nrElems;
    }
    int newElem = this->firstEmpty;
    if (newElem != -1) {// Check if newElem is a valid position
        this->firstEmpty = this->nodes[this->firstEmpty].next;// Move firstEmpty to the next available free position
        if (this->firstEmpty != -1)
            this->nodes[this->firstEmpty].prev = -1;
        this->nodes[newElem].next = -1;// Set the next pointer of the allocated node to -1
        this->nodes[newElem].prev = -1;// Set the previous pointer of the allocated node to -1
    }
    return newElem;// Return the position of the newly allocated node
}

//Complexity:
//Best Case == Worst Case == Average Case == theta(1)
void MultiMap::free(int pos) {
    this->nodes[pos].next = this->firstEmpty;
    this->nodes[pos].prev = -1;
    if (this->firstEmpty != -1)
        this->nodes[this->firstEmpty].prev = pos;
    this->firstEmpty = pos;
}
