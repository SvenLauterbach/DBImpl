#include "btreesegment.h"

BTreeSegment::BTreeSegment(SegmentInformation info, BufferManager& bm) : Segment(info, bm)
{

}

unsigned int BTreeSegment::insert(const BTreeNode<class T, class cmp>& node)
{
	SegmentInformation info = getSegmentInformation();
	BufferManager& bufferManager = getBufferManager();

	FreeSpaceInventory fsi(info);


	/*
	 * 1.) check if we have enough space for the new node
	 */
	unsigned int pageId = fsi.freePage();

	BufferFrame& frame = bufferManager.getPage(pageId, true);
	memcpy(frame.getData(), &node, PAGE_SIZE);
	bufferManager.unfixPage(frame, true);

	return pageId;
}

/*
 * Remove a node from the segment
 */
bool BTreeSegment::remove(BTreeNode<class T, class cmp> node)
{
	SegmentInformation info = getSegmentInformation();

	info.freePages.push_back(node.getId());
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

