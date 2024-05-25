#include "Map.h"
#include "MapIterator.h"
// ADT-Map repräsentiert mit Hilfe eines dynamischen Arrays von Paaren der Form(key,value)
Map::Map() {
    //TODO - Implementation
    this->nrElems = 0;
    this->cap = 15;
    this->elements = new std::pair<TKey, TValue>[this->cap];
}

Map::~Map() {
    //TODO - Implementation
    delete[] this->elements;
}

TValue Map::add(TKey c, TValue v) {
    //TODO - Implementation
    /*
		functia de adaugare in array
		//complexitate: theta(n)
        complexitate: best->theta(1), worst-> theta(n), avg->theta(n), general case O(n)
	*/
    //check if it is full
    if (this->nrElems == this->cap) {
        resizeUp();

    }
    int count = 0;//numarul aparitiilor
    int index = 0;
    //int help_index = 0;//tine minte la care index era elementul pe care il cautam
    //we look if the key already exists in the map
    while (index < this->nrElems ) {//&& count < 2
        if (this->elements[index].first == c) {
            count++;
            //help_index = index;
            break;
        }
        index++;
    }
    //if the key already exists in the map, then the value associated to the key is replaced by the new value
    // the old value is returned
    if (count == 1) {
        std::pair<TKey, TValue> result(NULL_TVALUE, NULL_TVALUE);
        result.second = this->elements[index].second;
        this->elements[index].second = v;
        return result.second;
    }
        //if the key does not exist, a new pair is added and the value null is returned
    else {
        TElem newpair(c, v);
        this->elements[this->nrElems] = newpair;
        this->nrElems++;
        return NULL_TVALUE;
    }

}

TValue Map::search(TKey c) const {
    //TODO - Implementation
    /*
		functia de cautare returneaza valoare elementului cautat daca elementul dat este gasit in array si
        NULL_TVALUE daca nu este gasit
		complexitate: best->theta(1), worst-> theta(n), avg->theta(n), general case O(n)
	*/
    std::pair<TKey, TValue> result(NULL_TVALUE, NULL_TVALUE);
    for (int i = 0; i < this->nrElems; i++) {
        if (this->elements[i].first == c) {
            result.second = this->elements[i].second;
            return result.second;
        }

    }
    return NULL_TVALUE;
}


TValue Map::remove(TKey c) {
    //TODO - Implementation
    /*
       functia de elimimare din array. Daca gaseste elementul, returneaza valoarea elementului sters, daca nu
       returneaza NULL_TVALUE
       complexitate: best->theta(1), worst-> theta(n), avg->theta(n), general Case->O(n)
   */
    if (this->nrElems <= this->cap / 4 && this->nrElems > 0) {
        resizeDown();

    }
    std::pair<TKey, TValue> removedValue(NULL_TVALUE, NULL_TVALUE);
    int index = 0;
    while (index < this->nrElems) {
        if (this->elements[index].first == c) {
            removedValue.second = this->elements[index].second;
            this->elements[index].first = this->elements[this->nrElems - 1].first;//ultimul element vine pe pozitia eliminata
            this->elements[index].second = this->elements[this->nrElems - 1].second;
            this->nrElems--;
            return removedValue.second;
        }
        index++;
    }
    return NULL_TVALUE;
}


int Map::size() const {
    //TODO - Implementation
    /*
		functia returneaza numarul de elemente din array, sau 0 daca nrElems=0
		complexitate:Theta(1)
	*/
    if (this->nrElems > 0) {
        return this->nrElems;
    } else
        return 0;
}

bool Map::isEmpty() const {
    //TODO - Implementation
    /*
		functia verifica daca arrayul este gol prin compararea nr de elemente cu 0
		complexitate: Theta(1)
	*/
    if (this->nrElems == 0)
        return true;
    else
        return false;
}

MapIterator Map::iterator() const {
    return MapIterator(*this);
}

void Map::resizeUp() {
    /*
       functia de resize. Creeaza un array nou cu cap dubla.
       Atribuie fiecarei pozitii din arrayul nou valoarea din arrayul vechi.
       Sterge arrayul vechi si atribuie la this->elements elementele din arrayul nou facut.
       complexitate: Theta(n)
   */
    int newCapacity = this->cap * 2;
    std::pair<TKey, TValue> *newElements = new std::pair<TKey, TValue>[newCapacity];
    for (int i = 0; i < this->nrElems; i++) {
        newElements[i] = this->elements[i];
    }
    delete[] this->elements;
    this->elements = newElements;
    this->cap = newCapacity;
}


void Map::resizeDown() {
    /*
       functia de resize. Creeaza un array nou cu cap injumatatita.
       Atribuie fiecarei pozitii din arrayul nou valoarea din arrayul vechi.
       Sterge arrayul vechi si atribuie la this->elements elementele din arrayul nou facut.
       complexitate: Theta(n)
   */
    int newCapacity = this->cap / 2;
    std::pair<TKey, TValue> *newElements = new std::pair<TKey, TValue>[newCapacity];
    for (int i = 0; i < this->nrElems; i++) {
        newElements[i] = this->elements[i];
    }
    delete[] this->elements;
    this->elements = newElements;
    this->cap = newCapacity;

}



