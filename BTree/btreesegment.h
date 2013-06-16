#ifndef BTREESEGMENT_H
#define BTREESEGMENT_H

#include <string.h>
#include "btreenode.h"
#include "../Segments/tid.h"
#include "../Segments/segment.h"
#include "../Segments/FreeSpaceInventory.h"
#include "../BufferManager/buffermanager.h"

class SegmentInformation;

class BTreeSegment : public Segment
{

public:
    BTreeSegment(SegmentInformation info, BufferManager& bm);

    unsigned int insert(const BTreeNode<class T, class cmp>& node);
	bool remove(BTreeNode<class T, class cmp> node);
	const BTreeNode<class T, class cmp>& lookup(TID tid);
	bool update(const BTreeNode<class T, class cmp>& node);
};

#endif // BTREESEGMENT_H
