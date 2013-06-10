#include "btreesegment.h"

BTreeSegment::BTreeSegment(SegmentInformation info, BufferManager& bm) : Segment(info, bm), bm(bm)
{

}

TID BTreeSegment::insert(const BTreeNode<class T, class cmp>& node)
{

}

bool BTreeSegment::remove(BTreeNode<class T, class cmp> node)
{

}

const BTreeNode<class T, class cmp>&  BTreeSegment::lookup(TID nodeId)
{

}

bool BTreeSegment::update(const BTreeNode<class T, class cmp>& node)
{

}

