#include "ShortTest.h"
#include <assert.h>
#include "Map.h"
#include "MapIterator.h"


void testAll() { //call each function to see if it is implemented
	Map m;
	assert(m.isEmpty() == true);
	assert(m.size() == 0); //add elements
	assert(m.add(5,5)==NULL_TVALUE);
	assert(m.add(1,111)==NULL_TVALUE);
	assert(m.add(10,110)==NULL_TVALUE);
	assert(m.add(7,7)==NULL_TVALUE);
	assert(m.add(1,1)==111);
	assert(m.add(10,10)==110);
	assert(m.add(-3,-3)==NULL_TVALUE);
	assert(m.size() == 5);
	assert(m.search(10) == 10);
	assert(m.search(16) == NULL_TVALUE);
	assert(m.remove(1) == 1);
	assert(m.remove(6) == NULL_TVALUE);
	assert(m.size() == 4);


	TElem e;
	MapIterator id = m.iterator();
	id.first();
	int s1 = 0, s2 = 0;
	while (id.valid()) {
		e = id.getCurrent();
		s1 += e.first;
		s2 += e.second;
		id.next();
	}
	assert(s1 == 19);
	assert(s2 == 19);
    Map m2;
    m2.add(1, 10);
    m2.add(2, 20);
    m2.add(3, 30);
    MapIterator id2 = m2.iterator();
    id2.first();
    std::pair<TKey, TValue> new_pair(4,100);
    id2.modify_current(new_pair);
    assert(m2.search(4) == 100);
    id2.next();
    std::pair<TKey, TValue> new_pair2(2,50);
    id2.modify_current(new_pair2);
    assert(m2.search(2) == 50);
    id2.next();
    std::pair<TKey, TValue> new_pair3(6,70);
    id2.modify_current(new_pair3);
    assert(m2.search(6) == 70);

}


