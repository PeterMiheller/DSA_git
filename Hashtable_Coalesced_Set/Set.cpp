#include "Set.h"
#include "SetIterator.h"
#include <iostream>

Set::Set() {
    //TODO - Implementation
    //Complexity:
    //- Best Case == Worst Case == Average Case ==  Theta(capacity)
    //- General Case: O(capacity)
    // It creates an empty set.

    this->capacity = 100;
    this->elements = new TElem[this->capacity];
    this->next = new int[this->capacity];
    for (int i = 0; i < this->capacity ; i++) {
        this->elements[i] = NULL_TELEM;
        this->next[i] = -1;
    }
    this->firstEmpty = 0;
    this->nrOfElements = 0;
}


bool Set::add(TElem elem) {
    //TODO - Implementation
    //Complexity:
    //- Best Case: Theta(1) - If the hash of the element is added to the first empty slot.
    //- Worst Case: Theta(capacity)-If the element need to be added to the end of a long linked list with the same hash value.
    //- Average Case: Theta(1) -Assuming a good hash function distributes elements evenly.
    //- General Case: O(capacity)

    //If the first empty is equal with the capacity, it does resize.
    if (this->firstEmpty == this->capacity)
        resize();

    int i = hash(elem);
    // If the element's hash value is NULL_TELEM, it means that the element is not in the set, because the position is free.
    // The element is added to the elements array of the first free position.
    if (this->elements[i] == NULL_TELEM) {
        this->elements[i] = elem;
        if (i == this->firstEmpty) {
            this->firstEmpty++;
            while ((this->firstEmpty < this->capacity) && this->elements[this->firstEmpty] != NULL_TELEM)
                this->firstEmpty++;
        }
        this->nrOfElements++;
        return true;
    }

    // If the element is already in the set, the method returns false.
    int j = -1;
    while (i != -1) {
        if (this->elements[i] == elem)
            return false;
        j = i;
        i = this->next[i];
    }

    // If the element is not in the set, it is added to the elements array of the first free position.
    //  The next array is updated.
    this->elements[this->firstEmpty] = elem;
    this->next[firstEmpty] = -1;
    this->next[j] = this->firstEmpty;
    this->firstEmpty++;
    while ((this->firstEmpty < this->capacity) && this->elements[this->firstEmpty] != NULL_TELEM)
        this->firstEmpty++;
    this->nrOfElements++;
    return true;
}


bool Set::remove(TElem elem) {
    //TODO - Implementation
    //Complexity:
    //- Best Case: Theta(1)- If the element is the first element with a particular hash value.
    //- Worst Case: Theta(capacity) -when iterating through a long linked list.
    //- Average Case: Theta(1)
    //- General Case: O(capacity)

    int i = hash(elem);
    int j = -1;
    //search the element in the set
    while (i != -1 && this->elements[i] != elem) {
        j = i;
        i = this->next[i];
    }

    //if not found return false
    if (i == -1) {
        return false;
    } else {
        //While the element to be removed has a next element, we replace it with the next element.
        //If the element to be removed doesn't have a next element,we replace it with the last element.
        bool checked = false;
        do {
            int current = this->next[i];
            int previous = i;
            // We find the next element with the same hash
            while (current != -1 && hash(this->elements[current]) != i) {
                previous = current;
                current = this->next[current];
            }

            if (current == -1) {
                checked = true;
            } else {
                // We put instead of the removed element the next element with the same hash
                this->elements[i] = this->elements[current];
                i = current;
                j = previous;
            }
        } while (!checked);

        // If the element to be removed doesn't have a next element, we replace it with the last element that means -1.
        if (j != -1) {
            this->next[j] = this->next[i];
        }
        this->elements[i] = NULL_TELEM;
        this->next[i] = -1;
        //if i is smaller than firsteEmpty, we change it
        if (i < this->firstEmpty) {
            this->firstEmpty = i;
        }
    }
    this->nrOfElements = this->nrOfElements - 1;
    return true;
}


bool Set::search(TElem elem) const {
    //TODO - Implementation
    //Complexity:
    //- Best Case: Theta(1) - If the element is the first element with a particular hash value.
    //- Worst Case: Theta(capacity)-when iterating through a long linked list.
    //- Average Case: Theta(1)
    //- General Case: O(capacity)
    //It uses the hash function to find the position of the element, and then
    // it searches for the element in the list of elements with the same hash.

    int i = hash(elem);
    while (i != -1 && this->elements[i] != elem) {
        i = this->next[i];
    }
    if (i == -1) {
        return false;
    } else {
        return true;
    }
}


int Set::size() const {
    //TODO - Implementation
    //Complexity:
    //Theta(1)
    return this->nrOfElements;
}


bool Set::isEmpty() const {
    //TODO - Implementation
    //Complexity:
    //Theta(1)
    if (this->nrOfElements == 0)
        return true;
    return false;
}


Set::~Set() {
    //TODO - Implementation
    //Complexity:
    //Theta(1)
    delete[] this->elements;
    delete[] this->next;
}


SetIterator Set::iterator() const {
    return SetIterator(*this);
}

int Set::hash(TElem e) const {
    //Complexity:
    //Theta(1)
    //Returns the hash value of an element.
    if (e < 0)
        return abs(e) % this->capacity;
    return e % this->capacity;

}

void Set::resize() {
    //Complexity:
    //- Best Case: Theta(capacity)
    //- Worst Case: Theta(capacity)- In the worst case, all elements might need to be rehashed on the same position.
    //- Average Case: Theta(capacity)
    //- General Case: O(capacity)
    // Step 1: Copy the existing elements to a temporary array
    auto *old = new TElem[this->nrOfElements];
    for (int i = 0; i < this->nrOfElements; ++i) {
        old[i] = NULL_TELEM;
    }
    int current = 0;
    for (int i = 0; i < this->capacity; ++i) {
        if (this->elements[i] != NULL_TELEM) {
            old[current] = this->elements[i];
            current++;
        }
    }
    // Step 2: Resize the capacity
    this->capacity = this->capacity * 2;
    auto *new_elems = new TElem[this->capacity];
    int *new_next = new int[this->capacity];
    for (int i = 0; i < this->capacity; ++i) {
        new_elems[i] = NULL_TELEM;
        new_next[i] = -1;
    }
    delete[] this->elements;
    delete[] this->next;
    this->elements = new_elems;
    this->next = new_next;

    // Step 3: Rehash all elements into the new larger arrays
    this->firstEmpty = 0;
    int oldNrOfElements = this->nrOfElements;
    this->nrOfElements = 0;
    for (int i = 0; i < oldNrOfElements; ++i) {
        add(old[i]);
    }
    delete[] old;
}
