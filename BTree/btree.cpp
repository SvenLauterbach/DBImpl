#include "btree.h"


template<typename T, class cmp>
BTree<T, cmp>::BTree(BTreeSegment segment)
{
    
}

template<typename T, class cmp>
void BTree<T, cmp>::erase(T Key)
{

}

template<typename T, class cmp>
void BTree<T, cmp>::insert(T key, TID tid)
{

}

template<typename T, class cmp>
TID BTree<T, cmp>::lookup(T key)
{
	BTreeNode<T, cmp>& current = root;
	TID next_tid;
	while ( current.isLeaf() != true ) {
		next_tid = current.find(key);
		// get node from segment
		current = segment.lookup(next_tid);
	}
	if ( current.isLeaf() ) {
		// get tid of key
		return current.find(key);
	}
	else return NULL;
}


