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
	for (i=0; i < this->count; i++) {
		if ( !cmp(key[i], newKey) ) {
			pos = i;
			break;
		}
	}
	assert(i!=this->count);

	// move following entries to the right
	for (i = --this->count; i >= this->pos; i--) {
		key[i+1] = key[i];
		tid[i+1] = tid[i];
	}
	key[pos] = newKey;
	tid[pos] = value;
	this->count++;
}

template<typename T, class cmp>
void LeafNode<T, cmp>::remove(T searchKey)
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
		tid[i] = tid[i+1];
	}
	this->count--;
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

	for (int i = this->count/2; i < this->count; i++) {
		new_leaf.add(key[i], tid[i]);
	}
	this->count = this->count/2;
	new_leaf.next = next;
	next = new_leaf;

	return new_leaf;
}


