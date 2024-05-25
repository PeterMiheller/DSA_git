#pragma once
#include "Map.h"
class MapIterator
{
    //DO NOT CHANGE THIS PART
    friend class Map;
private:
    const Map& map;
    //TODO - Representation
    int index;

    MapIterator(const Map& m);
public:
    void first();
    void next();
    TElem getCurrent();
    bool valid() const;
    void modify_current(std::pair<TKey, TValue> new_pair);
};


