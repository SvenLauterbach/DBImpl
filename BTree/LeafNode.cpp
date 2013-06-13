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
TID LeafNode<T,cmp>::find(T searchKey) {

	for ( int i = 0; i < this->count; i++) {
		if ( !cmp(key[i], searchKey) ) {
			return tid[i];
		}
	}
	return nullptr;
}
