#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
#include <mmcobj.h>

using namespace std;

//Complexity: theta(1)
Bag::Bag() {
    this->head = nullptr;
    this->tail = nullptr;
    //this->sizeOfBag = 0;
}

//Complexity:
// - Best Case: theta(1)
// - Worst Case: theta(n)
// - Average Case: theta(n)
// - General Case: O(n)
void Bag::add(TElem elem) {
    if(this->head == nullptr) {
        // If the bag is empty, add the element to the bag
        // and set the head and tail to the new node
        auto* newNode = new DLLNode;
        newNode->element = elem;
        newNode->frequenz = 1;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        this->head = newNode;
        this->tail = newNode;
        //this->sizeOfBag++;
    }else{
        // Search for the element in the bag
        // If it is found, increase the frequency
       DLLNode* currentNode = this->head;
        while (currentNode != nullptr) {
            if (currentNode->element == elem) {
                currentNode->frequenz++;
                //this->sizeOfBag++;
                return;
            }
            currentNode = currentNode->next;
        }

        // If it is not found, add it to the end of the bag
        auto* newNode = new DLLNode;

        newNode->element = elem;
        newNode->frequenz = 1;
        newNode->next = nullptr;
        newNode->prev = this->tail;

        this->tail->next = newNode;
        this->tail = newNode;
        //this->sizeOfBag++;
    }
}

//Complexity:
// - Best Case: theta(1)
// - Worst Case: theta(n)
// - Average Case: theta(n)
// - General Case: O(n)
bool Bag::remove(TElem elem){
    if(this->head == nullptr) {
        return false;
    }

    DLLNode* currentNode = this->head;
    while (currentNode != nullptr) {
        if (currentNode->element == elem) {
            if (currentNode->frequenz > 1) {
                currentNode->frequenz--;
                //this->sizeOfBag--;
                return true;
            }else{
                if (currentNode == this->head) {
                    this->head = currentNode->next;
                    if (this->head != nullptr) {//lista goala,ar da eroare ca am accesa prev de la o lista goala
                        this->head->prev = nullptr;
                    }
                    delete currentNode;
                    //this->sizeOfBag--;
                    return true;
                }else if (currentNode == this->tail) {
                    this->tail = currentNode->prev;
                    if (this->tail != nullptr) {//lista goala
                        this->tail->next = nullptr;
                    }
                    delete currentNode;
                    //this->sizeOfBag--;
                    return true;
                }else{
                    currentNode->prev->next = currentNode->next;// Această linie de cod actualizează pointerul next al nodului anterior la currentNode astfel încât să pointeze către nodul următor al lui currentNode
                    currentNode->next->prev = currentNode->prev;// Această linie de cod actualizează pointerul prev al nodului următor la currentNode astfel încât să pointeze către nodul anterior al lui currentNode
                    delete currentNode;
                    //this->sizeOfBag--;
                    return true;
                }
            }
        }
        currentNode = currentNode->next;
    }
    return false;
}

//Complexity:
// - Best Case: theta(1)
// - Worst Case: theta(n)
// - Average Case: theta(n)
// - General Case: O(n)
bool Bag::search(TElem elem) const {
    if(this->head == nullptr) {
        return false;
    }

    DLLNode* currentNode = this->head;
    while (currentNode != nullptr) {
        if (currentNode->element == elem) {
            return true;
        }
        currentNode = currentNode->next;
    }

    return false;
}

//Complexity:
// - Best Case: theta(1)
// - Worst Case: theta(n)
// - Average Case: theta(n)
// - General Case: O(n)
int Bag::nrOccurrences(TElem elem) const {
        if(this->head == nullptr) {
            return 0;
        }

        DLLNode* currentNode = this->head;
        while (currentNode != nullptr) {
            if (currentNode->element == elem) {
                return currentNode->frequenz;
            }
            currentNode = currentNode->next;
        }

        return 0;
    }

//Complexity:
//Best Case == Worst Case == Average Case == theta(1) or
//Best Case == Worst Case == Average Case == theta(n)
int Bag::size() const {
    //return this->sizeOfBag;
    int count = 0;
    DLLNode* currentNode = this->head;
    if (currentNode == nullptr) {
        return 0; // Bag is empty
    }else{
        while (currentNode != nullptr) {
            count = count + currentNode->frequenz; // Increment the count for each node
            currentNode = currentNode->next; // Move to the next node
        }
    }

    return count;

}

//Complexity: theta(1)
//Best Case == Worst Case == Average Case == theta(1)
bool Bag::isEmpty() const {
    //return this->sizeOfBag == 0;
    return this->size()==0;
}
//Complexity: theta(1)
//Best Case == Worst Case == Average Case == theta(1)
BagIterator Bag::iterator() const {
	return BagIterator(*this);
}
//Complexity: theta(n)
//Best Case == Worst Case == Average Case == theta(n)
Bag::~Bag() {
    DLLNode* currentNode = this->head;
    while (currentNode != nullptr) {
       DLLNode* nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
    delete currentNode;
}

//Complexity:
//Best Case == Worst Case == Average Case == theta(n)
void Bag::reverse() {
    // If the list is empty return
    if (this->head == nullptr) {
        return;
    }
    DLLNode* aux = nullptr;
    DLLNode* current = this->head;
// swap next and prev for all nodes of linked list
    while (current != nullptr) {
        aux = current->prev;
        current->prev = current->next;
        current->next = aux;
        current = current->prev;
}
    this->head = aux->prev;
    this->tail = aux;
}
/*
  function reverse()
        if(dll.head=NIL)
            return
        end-if
        newNode aux<- allocate()
        newNode current<- allocate()
        current<-dll.head
        while(current!=NIL) execute
            aux<-current.prev
            current.prev<-current.next
            current.next<-aux
            current<-current.prev
        end-while
        dll.head<-aux.prev
        dll.tail<-aux
  end-function

 */

