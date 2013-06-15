#ifndef LEAFNODE_H_
#define LEAFNODE_H_

#include "btreenode.h"
#include "../Segments/tid.h"

template<typename T, class cmp>
class LeafNode : public BTreeNode<T,cmp>
{
public:
	LeafNode();
	virtual ~LeafNode();
	TID find(T searchKey);
	LeafNode<T,cmp>& split();
	void add(T newKey, TID value);
	void remove(T searchKey);

	T maxKey() { return key[this->count-1]; }


private:
	T key[NODE_SIZE];
	TID tid[NODE_SIZE];
	LeafNode next;
};

#endif /* LEAFNODE_H_ */
