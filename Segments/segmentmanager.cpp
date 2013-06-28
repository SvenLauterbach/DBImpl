#include "segmentmanager.h"


SegmentManager::SegmentManager(BufferManager& bufferManager)
 : bufferManager(bufferManager)
{

}

/*
 * Default Größe = 2 Page
 */
SegmentID SegmentManager::createSegment(SegmentType segmentType, unsigned int size = 2)
{
	/*
	 * we need the segment Inventory to register the created segment
	 */
	BufferFrame& frame = bufferManager.getPage(0, bufferManager.getMasterFile(), true);
    SISegment* segmentInventory = static_cast<SISegment*>(frame.getData());

    SegmentInformation result = segmentInventory->CreateSegment(segmentType, size);
    
    bufferManager.unfixPage(frame, true);
    
    /*
     * after creating registering the new segment we have to create the file for the segment
     */
    int fileHandle = 0;

    if((fileHandle = open(result.fileName.c_str(), O_CREAT)) < 0)
    {
    	//exception
    }

    if(posix_fallocate(fileHandle, 0 , size * PAGE_SIZE) < 0)
    {
    	//exception
    }

    off_t sizef = lseek(fileHandle, 0, SEEK_END);
    ftruncate(fileHandle, 0);
    ftruncate(fileHandle, sizef);

    return result.segmentId;
}

Segment& SegmentManager::getSegment(SegmentID id)
{
    BufferFrame& frame = bufferManager.getPage(0, bufferManager.getMasterFile(), false);
    SISegment* segmentInventory = static_cast<SISegment*>(frame.getData());	
    bufferManager.unfixPage(frame, true);
    
    SegmentInformation info = segmentInventory->GetSegment(id);
    
    Segment* segment = nullptr;
    
    switch(info.type)
    {
	case SegmentType::SP:
	    segment = new SPSegment(info, bufferManager);
	    break;
	case SegmentType::BT:
		segment = new BTreeSegment(info, bufferManager);
		break;
	default:
	    segment = new Segment(info, bufferManager);
    }

    return *segment;
}




