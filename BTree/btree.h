#ifndef BTREE_H
#define BTREE_H

#include "../Segments/tid.h"
#include "btreesegment.h"
#include "btreenode.h"

template<typename T, class cmp>
class BTree
{

public:
    BTree(BTreeSegment segment);
    
    void insert(T key, TID tid);
    void erase(T Key);
    TID lookup(T Key);

private:
    BTreeNode<T, cmp> root;
    BTreeSegment segment;
};

#endif // BTREE_H
