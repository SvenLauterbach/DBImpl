
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
TID InnerNode<T,cmp>::find(T searchKey) {

	for ( int i = 0; i < this->count; i++) {
		if ( !cmp(key[i], searchKey) ) {
			return child[i];
		}
	}
	return upper;
}
