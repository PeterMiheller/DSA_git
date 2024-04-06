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
    this->sizeOfBag = 0;
}

//Complexity:
// - Best Case: theta(1)
// - Worst Case: theta(n)
// - Average Case: theta(n)
void Bag::add(TElem elem) {
 /*   DLLNode* n = nullptr;
    n = new DLLNode;
    n->element = elem;
    if (this->tail == nullptr) { //if we don't have an end
        if (this->head == nullptr) { //if we dont have a start
            this->head = n; //set the start to n
        }
        this->tail = n; //set the end to n
    }
    else {
        this->tail->next = n; //our bag's end's next node equals n;
        n->prev = this->tail; //n's previous equals our current tail
        this->tail = this->tail->next; //our tail equals n
    }
}*/if(this->head == nullptr) {
        // If the bag is empty, add the element to the bag
        // and set the head and tail to the new node
        auto* newNode = new DLLNode;
        newNode->element = elem;
        newNode->frequenz = 1;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        this->head = newNode;
        this->tail = newNode;
        this->sizeOfBag++;
    }else{
        // Search for the element in the bag
        // If it is found, increase the frequency
       DLLNode* currentNode = this->head;
        while (currentNode != nullptr) {
            if (currentNode->element == elem) {
                currentNode->frequenz++;
                this->sizeOfBag++;
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
        this->sizeOfBag++;
    }
}

//Complexity:
// - Best Case: theta(1)
// - Worst Case: theta(n)
// - Average Case: theta(n)
bool Bag::remove(TElem elem){
    if(this->head == nullptr) {
        return false;
    }

    DLLNode* currentNode = this->head;
    while (currentNode != nullptr) {
        if (currentNode->element == elem) {
            if (currentNode->frequenz > 1) {
                currentNode->frequenz--;
                this->sizeOfBag--;
                return true;
            }else{
                if (currentNode == this->head) {
                    this->head = currentNode->next;
                    if (this->head != nullptr) {
                        this->head->prev = nullptr;
                    }
                    delete currentNode;
                    this->sizeOfBag--;
                    return true;
                }else if (currentNode == this->tail) {
                    this->tail = currentNode->prev;
                    if (this->tail != nullptr) {
                        this->tail->next = nullptr;
                    }
                    delete currentNode;
                    this->sizeOfBag--;
                    return true;
                }else{
                    currentNode->prev->next = currentNode->next;
                    currentNode->next->prev = currentNode->prev;
                    delete currentNode;
                    this->sizeOfBag--;
                    return true;
                }
            }
        }
        currentNode = currentNode->next;
    }
    return false;
}
/* {
    if (this->head == nullptr||this->tail==nullptr) return false; //if we have no elements
    DLLNode* traverser = this->head; //our starting point is our bag's starting point
    while (true) {
        if (traverser->element == elem) { //if we found our element
            DLLNode* last = traverser->prev; //the element before ours
            DLLNode* succ = traverser->next; //the element after ours
            last->next = succ; //put the element before our's 's next element to the element after our's
            succ->prev = last; //set the element after our's 's previous element to the element before our's
            delete traverser; //delete our element
            return true;
        }
        else
        if (traverser->next == nullptr) return false; //If we reached the end
        else traverser = traverser->next; //move forward
    }
	//return false;
}

{
    if (this->head == nullptr) return false; // Dacă sacul este gol, nu putem elimina nimic

    DLLNode* traverser = this->head; // Inițializăm traverser la începutul sacului
    while (traverser != nullptr) {
        if (traverser->element == elem) { // Dacă am găsit elementul de eliminat
            if (traverser == this->head) { // Dacă elementul de eliminat este primul din sac
                this->head = traverser->next; // Actualizăm head la următorul element
                if (this->head != nullptr) {
                    this->head->prev = nullptr; // Dacă există un următor element, actualizăm prev-ul lui
                } else {
                    this->tail = nullptr; // Dacă nu există următor element, actualizăm și tail-ul la nullptr
                }
            } else if (traverser == this->tail) { // Dacă elementul de eliminat este ultimul din sac
                this->tail = traverser->prev; // Actualizăm tail la elementul anterior
                this->tail->next = nullptr; // Actualizăm next-ul elementului anterior la nullptr
            } else { // Dacă elementul de eliminat este în mijlocul sacului
                traverser->prev->next = traverser->next; // Actualizăm next-ul elementului anterior
                traverser->next->prev = traverser->prev; // Actualizăm prev-ul elementului următor
            }
            delete traverser; // Eliberăm memoria ocupată de elementul eliminat
            return true; // Returnăm true dacă am reușit să eliminăm elementul
        }
        traverser = traverser->next; // Trecem la următorul element din sac
    }
    return false; // Dacă nu am găsit elementul de eliminat, returnăm false
}*/

//Complexity:
// - Best Case: theta(1)
// - Worst Case: theta(n)
// - Average Case: theta(n)
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
    /*
    DLLNode* traverser = this->head; // Start from the beginning of the bag
    while (traverser != nullptr) {
        if (traverser->element == elem) {
            // Found the element in the bag
            return true;
        }
        traverser = traverser->next; // Move to the next node
    }
    // Element not found
    return false;
}*/
//Complexity:
// - Best Case: theta(1)
// - Worst Case: theta(n)
// - Average Case: theta(n)
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
   /* int count = 0;
    DLLNode* traverser = this->head; // Start from the beginning of the bag
    while (traverser != nullptr) {
        if (traverser->element == elem) {
            // Found an occurrence of the element
            count++;
        }
        traverser = traverser->next; // Move to the next node
    }
    return count;*/

	//return 0;

//Complexity: theta(1)
//Best Case == Worst Case == Average Case == theta(1)
int Bag::size() const {
    return this->sizeOfBag;
    /*int count = 0;
    DLLNode* traverser = this->head; // Start from the beginning of the bag
    while (traverser != nullptr) {
        count++; // Increment the count for each node
        traverser = traverser->next; // Move to the next node
    }
    return count;*/

	//return 0;
}

//Complexity: theta(1)
//Best Case == Worst Case == Average Case == theta(1)
bool Bag::isEmpty() const {
    return this->sizeOfBag == 0;
    //return (this->head == nullptr);
	//return 0;
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
    // Traverse the linked list and delete each node
   /* while (this->head != nullptr) {
        DLLNode* temp = this->head; // Store the current head
        this->head = this->head->next; // Move to the next node
        delete temp; // Deallocate memory for the current node
    }
    // Set tail to nullptr (optional, but good practice)
    this->tail = nullptr;*/



