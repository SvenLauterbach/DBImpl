#include "btreenode.h"

template<typename T, class cmp>
BTreeNode<T, cmp>::BTreeNode()
{
	_isLeaf = false;
	count = 0;
}

template<typename T, class cmp>
TID BTreeNode<T, cmp>::lookup(T Key)
{
	// Implemented in child classes
	return 0;
}

/*
template<typename T, class cmp>
void BTreeNode<T, cmp>::add(T key, TID value)
{
	// Implemented in child classes
}

template<typename T, class cmp>
void BTreeNode<T, cmp>::remove(T key)
{
	// Implemented in child classes
}
*/


