#include "Map.h"
#include "MapIterator.h"
#include <exception>

using namespace std;


MapIterator::MapIterator(const Map &d) : map(d) {
    //TODO - Implementation
    this->index = 0;
}


void MapIterator::first() {
    //TODO - Implementation
    this->index = 0;

}


void MapIterator::next() {
    //TODO - Implementation
    /*
		functia creste iteratorul cu 1 daca pozitia urmatoare este valida,
		daca nu returneaza o exceptie
		complexitate: theta(1)
	*/

    if (valid()) {//this->index < this->map.nrElems
        this->index++;
    } else {
        throw exception();

    }
}


TElem MapIterator::getCurrent() {
    //TODO - Implementation
    /*
		functia returneaza elementrul de pe pozitia curenta daca aceasta este valida,
		daca nu returneaza exceptie
		complexitate: theta(1)
	*/
    if (valid())
        return this->map.elements[this->index];
    else
        throw exception();
}


bool MapIterator::valid() const {
    //TODO - Implementation
    /*
		functia verifica daca iteratorul este valid
		complexitate: theta(1)
	*/

    if (!map.isEmpty() && this->index < map.nrElems)
        return true;
    return false;
}

void MapIterator::modify_current(std::pair<TKey, TValue> new_pair) {
    //complexity Best: theta(1) worst :theta(n) avg: theta(n) General O(n)
    if (valid()) {//verify if the iterator is valid
        for (int i = 0; i < map.nrElems; i++)// verify if the key allready exists
            if(this->map.elements[i].first == new_pair.first){
                this->map.elements[i].second = new_pair.second;//We change the value
                return;}
        this->map.elements[this->index].first = new_pair.first;//if the key does not exist we change thekey
        this->map.elements[this->index].second = new_pair.second;// Modify the value associated with the new key
    }
    else
        throw exception();// If the iterator is not valid, throw an exception
}
/* function modify_current(pair(m,n)) is:
    //pre: n ist ein Value und m ist ein Key.map ist ein Map
    // post: eine neue Value und Key wird zum current hingefugt oder das Schlussel wird geändert
    if valid() then
            for i<-0, map.size,i+1 execute
                if map.elements[i]<-m
                    map.elements[i].first<-m
                    end-if
            end-for
        current.map.first <-  m
        current.map.second <-  n
    else
        @error, invalid position
        end if
   end-function

 */



