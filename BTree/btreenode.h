#ifndef BTREENODE_H
#define BTREENODE_H
#include <utility>
#include <algorithm>
#include <vector>
#include "../Segments/tid.h"
#include "../BufferManager/bufferframe.h"
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

    //ToDO: refactor inline getter
    unsigned int getId()
    {
    	return id;
    }
    
protected:
    // TODO LSN for recovery
    bool _isLeaf;
    unsigned int maxNrOfRecords; //how many records can we store in this node
    unsigned int count; //actual number of records

    std::vector<T> keys; //seperator
    std::vector<TID> records;

    /*
     *  the id is usefull to reference this node in other nodes
     *  and we can use this id as a page id in the segment;
     */
    unsigned int id;

    int getIndex(T key);
};

template<typename T, class cmp>
BTreeNode<T, cmp>::BTreeNode()
	: keys(), records()
{
	_isLeaf = false;

	unsigned int sizeForPayLoad = PAGE_SIZE - sizeof(_isLeaf) - sizeof(id) - sizeof(maxNrOfRecords) - sizeof(count);
	maxNrOfRecords = (sizeForPayLoad / (sizeof(TID) + sizeof(T)));
}

template<typename T, class cmp>
BTreeNode<T, cmp>::~BTreeNode()
{

}

template<typename T, class cmp>
void BTreeNode<T, cmp>::add(T key, TID value)
{
	keys.push_back(key);
	records.push_back(value);
	count++;
}

template<typename T, class cmp>
void BTreeNode<T, cmp>::remove(T Key)
{
	int index = getIndex(Key);

	keys.remove(keys.begin() + index);
	records.erase(records.begin() + index);
}

template<typename T, class cmp>
int BTreeNode<T, cmp>::getIndex(T Key)
{
	typename std::vector<T>::iterator it;
	it = std::find(keys.begin(), keys.end(), Key);

	if(it == keys.end())
	{
		//return ;
	}

	int index = it - keys.begin();

	return index;
}

template<typename T, class cmp>
TID BTreeNode<T, cmp>::find(T Key)
{
	int index = getIndex(Key);

	if(index == -1)
	{
		//return nullptr;
	}

	return records[index];
}

#endif // BTREENODE_H
