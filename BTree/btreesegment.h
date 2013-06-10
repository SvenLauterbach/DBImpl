#ifndef BTREESEGMENT_H
#define BTREESEGMENT_H

#include "btreenode.h"
#include "../Segments/tid.h"
#include "../Segments/segment.h"
#include "../BufferManager/buffermanager.h"

class SegmentInformation;

class BTreeSegment : public Segment
{

public:
    BTreeSegment(SegmentInformation info, BufferManager& bm);

    TID insert(const BTreeNode<class T, class cmp>& node);
	bool remove(BTreeNode<class T, class cmp> node);
	const BTreeNode<class T, class cmp>& lookup(TID nodeId);
	bool update(const BTreeNode<class T, class cmp>& node);

private:
	BufferManager& bm;
};

#endif // BTREESEGMENT_H
