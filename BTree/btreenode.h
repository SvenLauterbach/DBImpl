#ifndef BTREENODE_H
#define BTREENODE_H

class TID;

#define NODE_SIZE 4

template<typename T, class cmp>
class BTreeNode
{
public:
    BTreeNode();
    virtual ~BTreeNode();
    void add(std::pair<T, TID> value);
    void remove(T key);
    TID find(T key);
    bool isLeaf() { return _isLeaf; };
    
    
protected:
    // TODO LSN for recovery
    int count;
    bool _isLeaf;
};

#endif // BTREENODE_H
