#ifndef BTREE_H
#define BTREE_H

class BTreeSegment;
template<typename T, class cmp> class BTreeNode;
template<typename T, class cmp> class LeafNode;
class TID;

#include "btreesegment.h"
/*#include "../Segments/tid.h"
#include "btreesegment.h"
#include "btreenode.h"
*/

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

    LeafNode<T, cmp>& lookupLeaf(T key);
};

#endif // BTREE_H
