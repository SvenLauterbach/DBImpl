#ifndef BTREE_H
#define BTREE_H

#include </home/sven/projects/BufferManager/Segments/tid.h>
#include "btreesegment.h"

template<typename T, class cmp>
class BTree
{

public:
    BTree(BTreeSegment segment);
    
    void insert(T key, TID tid);
    void erase(T Key);
    TID lookup(T Key);
};

#endif // BTREE_H
