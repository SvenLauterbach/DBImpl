#ifndef BTREENODE_H
#define BTREENODE_H
#include <utility>
#include "../Segments/tid.h"
class TID;

#define NODE_SIZE 4

template<typename T, class cmp>
class BTreeNode
{
public:
    BTreeNode();
    virtual ~BTreeNode();
    void add(T key, TID value);
    void remove(T key);
    TID find(T key);
    bool isLeaf() { return _isLeaf; };
    bool isFull() { return count == NODE_SIZE; }
    bool isHalfFull() { return count >= NODE_SIZE/2; }
    TID lookup(T Key);

    
    
protected:
    // TODO LSN for recovery
    int count;
    bool _isLeaf;
};

#endif // BTREENODE_H
