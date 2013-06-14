#include "LeafNode.h"

template<typename T, class cmp>
LeafNode<T, cmp>::LeafNode()
{
	// TODO Auto-generated constructor stub

}

template<typename T, class cmp>
LeafNode<T, cmp>::~LeafNode()
{
	// TODO Auto-generated destructor stub
}

template<typename T, class cmp>
void LeafNode<T, cmp>::add(T newKey, TID value)
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
		tid[i+1] = tid[i];
	}
	key[pos] = newKey;
	tid[pos] = value;
	count++;
}

template<typename T, class cmp>
void LeafNode<T, cmp>::remove(T searchKey)
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
		tid[i] = tid[i+1];
	}
	count--;
	// TODO: what if count now equals zero?
}


template<typename T, class cmp>
TID LeafNode<T,cmp>::find(T searchKey) {

	for ( int i = 0; i < this->count; i++) {
		if ( !cmp(key[i], searchKey) ) {
			return tid[i];
		}
	}
	return nullptr;
}

template<typename T, class cmp>
LeafNode<T, cmp>& LeafNode<T, cmp>::split()
{
	LeafNode<T,cmp> new_leaf = new LeafNode<T,cmp>();

	for (int i = count/2; i < count; i++) {
		new_leaf.add(key[i], tid[i]);
	}
	count = count/2;
	new_leaf.next = next;
	next = new_leaf;

	return new_leaf;
}


