
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
	for (i=0; i < this->count; i++) {
		if ( !cmp(key[i], newKey) ) {
			pos = i;
			break;
		}
	}
	assert(i!=this->count);

	// move following entries to the right
	for (i = --this->count; i >= pos; i--) {
		key[i+1] = key[i];
		child[i+1] = child[i];
	}
	key[pos] = newKey;
	child[pos] = value;
	this->count++;
}

template<typename T, class cmp>
void InnerNode<T, cmp>::remove(T searchKey)
{
	int i,pos;
	// find place of the to be deleted key
	for (i=0; i < this->count; i++) {
		if ( !cmp(key[i], searchKey) ) {
			pos = i;
			break;
		}
	}
	assert(i!=this->count);
	assert(key[i]==searchKey);

	// move following entries to the left
	for (; i < this->count; i--) {
		key[i] = key[i+1];
		child[i] = child[i+1];
	}
	this->count--;
	// TODO: what if count now equals zero?
}

template<typename T, class cmp>
TID InnerNode<T,cmp>::find(T searchKey) {

	for ( int i = 0; i < this->count; i++) {
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

	for (int i = this->count/2; i < this->count; i++) {
		new_node.add(key[i], tid[i]);
	}
	this->count = this->count/2;

	return new_node;
}

template<typename T, class cmp>
bool InnerNode<T, cmp>::isFull()
{
	return false;
}

template<typename T, class cmp>
unsigned int InnerNode<T, cmp>::maxKey()
{
	return 0;
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
		BTreeNode<T,cmp> leaf2;
		BTreeNode<T,cmp> parent;
		BTreeSegment segment;
		// no free space -> split leaf in two
		LeafNode<T, cmp>& new_node = split();
		TID new_node_tid = segment.insert(leaf2);

		// TODO: get parent, but how to get the root?
		// Maybe move the whole method to BTree class
		parent.insert(maxKey(), new_node);
		( cmp(key, maxKey()) ? this : new_node ).add(key, value);
	}
}

