#include "Bag.h"

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;
	
private:
	const Bag& bag;
    /*struct DLLNode {
        TElem element;
        TElem frequenz;
        DLLNode* prev;
        DLLNode* next;
    };*/
    //DLLNode* current_node;
    Bag::DLLNode* current_node;
    //Bag::DLLNode* head;
    //Bag::DLLNode* tail;
    int currentFrequency;
    BagIterator(const Bag& c);
public:
	void first();
	void next();
	TElem getCurrent() const;
	bool valid() const;
};
