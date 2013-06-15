#include <cassert>
#include "btree.h"
#include "../Segments/tid.h"
#include "btreesegment.h"
#include "btreenode.h"
#include "InnerNode.h"

template<typename T, class cmp>
BTree<T, cmp>::BTree(BTreeSegment segment)
{
    
}


template<typename T, class cmp>
TID BTree<T, cmp>::lookup(T key)
{
	LeafNode<T, cmp>& current = lookupLeaf(key);
	return current.find(key);
}

template<typename T, class cmp>
LeafNode<T, cmp>& BTree<T, cmp>::lookupLeaf(T key)
{
	BTreeNode<T, cmp>& current = root;
	TID next_tid;
	while ( current.isLeaf() != true )
	{
		next_tid = current.find(key);
		// get node from segment
		current = segment.lookup(next_tid);
	}
	assert(current.isLeaf());
	return current;
}

template<typename T, class cmp>
void BTree<T, cmp>::insert(T key, TID tid)
{
	//LeafNode<T, cmp>& leaf = lookupLeaf(key);
	BTreeNode<T, cmp>& current = root;
	InnerNode<T, cmp>& parent;
	TID next_tid;
	while ( current.isLeaf() != true )
	{
		next_tid = current.find(key);
		parent = current;
		// get node from segment
		current = segment.lookup(next_tid);
	}
	assert(current.isLeaf());

	LeafNode<T, cmp>& leaf = current;

	if ( !leaf.isFull() )
	{
		leaf.add(key);
	}
	else
	{
		// no free space -> split leaf in two
		LeafNode<T, cmp>& leaf2 = leaf.split(leaf);
		TID leaf2_tid = segment.insert(leaf2);
		( cmp(key, leaf.maxKey()) ? leaf : leaf2 ).add(key, tid);

		parent.insert(leaf.maxKey(), leaf2_tid);
	}

}

template<typename T, class cmp>
void BTree<T, cmp>::erase(T key)
{
	LeafNode<T, cmp>& leaf = lookupLeaf(key);
	leaf.remove(key);

	// we simplify the delete logic and accept under-full inner nodes
}

