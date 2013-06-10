#include "segmentmanager.h"
#include "spsegment.h"

SegmentManager::SegmentManager(BufferManager& bufferManager)
 : bufferManager(bufferManager)
{

}

SegmentID SegmentManager::createSegment(SegmentType segmentType, unsigned int size)
{
    SegmentID result;
    
    BufferFrame& frame = bufferManager.getPage(0, true);
    SISegment* segmentInventory = static_cast<SISegment*>(frame.getData());	

    
    switch(segmentType)
    {
	case SegmentType::SP:
	    result = segmentInventory->CreateSegment(SegmentType::SP, size);
	    
    }
    
    bufferManager.unfixPage(frame, true);
    
    return result;
}

Segment& SegmentManager::getSegment(SegmentID id)
{
    BufferFrame& frame = bufferManager.getPage(0, false);
    SISegment* segmentInventory = static_cast<SISegment*>(frame.getData());	
    bufferManager.unfixPage(frame, true);
    
    SegmentInformation info = segmentInventory->GetSegment(id);
    
    Segment* segment = nullptr;
    
    switch(info.type)
    {
	case SegmentType::SP: 
	    segment = new SPSegment(info, bufferManager);
	default:
	    segment = new Segment(info);
    }
    
    
    return *segment;
}



