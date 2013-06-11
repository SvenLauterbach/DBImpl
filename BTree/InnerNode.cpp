
#include "InnerNode.h"

template<typename T, class cmp>
InnerNode<T,cmp>::InnerNode()
{
	// TODO Auto-generated constructor stub

}

template<typename T, class cmp>
InnerNode<T,cmp>::~InnerNode()
{
	// TODO Auto-generated destructor stub
}


template<typename T, class cmp>
void InnerNode<T, cmp>::add(T newKey, TID value)
{
	int i,pos;
	// find correct place for new entry
	for (i=0; i < count; i++) {
		if ( !cmp(key[i], newKey) ) {
			pos = i;
			break;
		}
	}
	assert(i!=count);

	// move following entries to the right
	for (i = --count; i >= pos; i--) {
		key[i+1] = key[i];
		child[i+1] = child[i];
	}
	key[pos] = newKey;
	child[pos] = value;
	count++;
}

template<typename T, class cmp>
void InnerNode<T, cmp>::remove(T searchKey)
{
	int i,pos;
	// find place of the to be deleted key
	for (i=0; i < count; i++) {
		if ( !cmp(key[i], searchKey) ) {
			pos = i;
			break;
		}
	}
	assert(i!=count);
	assert(key[i]==searchKey);

	// move following entries to the left
	for (; i < count; i--) {
		key[i] = key[i+1];
		child[i] = child[i+1];
	}
	count--;
	// TODO: what if count now equals zero?
}

template<typename T, class cmp>
TID InnerNode<T,cmp>::find(T searchKey) {

	for ( int i = 0; i < count; i++) {
		if ( !cmp(key[i], searchKey) ) {
			return child[i];
		}
	}
	return upper;
}

template<typename T, class cmp>
InnerNode<T, cmp>& InnerNode<T, cmp>::split()
{
	InnerNode<T,cmp> new_node = new InnerNode<T,cmp>();

	for (int i = count/2; i < count; i++) {
		new_node.add(key[i], tid[i]);
	}
	count = count/2;

	return new_node;
}


template<typename T, class cmp>
void InnerNode<T, cmp>::insert(T key, TID value)
{
	if (!isFull())
	{
		add(key, value);
	}
	else
	{
		// no free space -> split leaf in two
		LeafNode<T, cmp>& new_node = split(leaf);
		TID new_node_tid = segment.insert(leaf2);

		// TODO: get parent, but how to get the root?
		// Maybe move the whole method to BTree class
		parent.insert(maxKey(), new_node);
		( cmp(key, maxKey()) ? this : new_node ).add(key, value);
	}
}

