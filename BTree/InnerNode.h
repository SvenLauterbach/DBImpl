#ifndef InnerNode_H_
#define InnerNode_H_

#include "btreenode.h"
#include "../Segments/tid.h"
#include "btreesegment.h"
#include "LeafNode.h"

template<typename T, class cmp>
class InnerNode: public BTreeNode<T,cmp>
{
public:
	InnerNode();
	virtual ~InnerNode();
	TID find(T searchKey);
	InnerNode<T, cmp>& split();
	void remove(T searchKey);
	void insert(T key, TID value);
	void add(T newKey, TID value);
	unsigned int maxKey();
	bool isFull();

private:
	T key[NODE_SIZE];
	TID tid[NODE_SIZE];
	TID child[NODE_SIZE];
	TID upper; // "page" of right-most child
};

#endif /* InnerNode_H_ */
