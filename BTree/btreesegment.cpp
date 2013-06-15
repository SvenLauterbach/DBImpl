#include "btreesegment.h"

BTreeSegment::BTreeSegment(SegmentInformation info, BufferManager& bm) : Segment(info, bm)
{

}

unsigned int BTreeSegment::insert(const BTreeNode<class T, class cmp>& node)
{
	SegmentInformation info = getSegmentInformation();
	BufferManager& bufferManager = getBufferManager();


}

bool BTreeSegment::remove(BTreeNode<class T, class cmp> node)
{

}

const BTreeNode<class T, class cmp>&  BTreeSegment::lookup(TID tid)
{
	SegmentInformation info = getSegmentInformation();
	BufferManager& bufferManager = getBufferManager();

	BufferFrame& frame = bufferManager.getPage(tid.getPageId(), true);

	BTreeNode<class T, class cmp>* node = static_cast<BTreeNode<class T, class cmp>*>(frame.getData());

	return *node;
}

bool BTreeSegment::update(const BTreeNode<class T, class cmp>& node)
{
	SegmentInformation info = getSegmentInformation();
	BufferManager& bufferManager = getBufferManager();

	BufferFrame& frame = bufferManager.getPage(0, true);

	//BÖSE!
	memcpy(frame.getData(), &node, PAGE_SIZE);

	bufferManager.unfixPage(frame, true);
}

