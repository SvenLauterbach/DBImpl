#ifndef BTREENODE_H
#define BTREENODE_H
#include <vector>
#include "../Segments/tid.h"

template<typename T, class cmp>
class BTreeNode
{
    BTreeNode();
    void add(std::pair<T, TID> value);
    void remove(T key);
    TID lookup(T Key);
    
    
private:
   
    std::vector<T> keySlots;
    std::vector<T> childPointers;
    int count;
    bool isLeave;
};

#endif // BTREENODE_H
