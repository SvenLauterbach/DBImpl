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

private:
	T key[NODE_SIZE];
	TID tid[NODE_SIZE];
	LeafNode next;
};

#endif /* LEAFNODE_H_ */
