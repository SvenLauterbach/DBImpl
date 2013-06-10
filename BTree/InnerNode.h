#ifndef InnerNode_H_
#define InnerNode_H_

#include "btreenode.h"

template<typename T, class cmp>
class InnerNode: public BTreeNode<T,cmp>
{
public:
	InnerNode();
	virtual ~InnerNode();
	TID find(T searchKey);

private:
	T key[NODE_SIZE];
	TID child[NODE_SIZE];
	TID upper; // "page" of right-most child
};

#endif /* InnerNode_H_ */
