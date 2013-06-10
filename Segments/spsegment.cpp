#include "spsegment.h"
#include "slottedpage.h"
#include "slottedpage.h"

SPSegment::SPSegment(SegmentInformation info, BufferManager& bufferManager) : Segment(info), bufferManager(bufferManager)
{

}

const Record& SPSegment::lookup(TID recordId)
{
    
}

TID SPSegment::insert(const Record& record)
{
    SegmentInformation infos = getSegmentInformation();
    
    unsigned int firstpage = infos.offset;
    unsigned int lastpage = infos.offset + infos.nrOfPages;
    
    /*
     * iterate over all pages of this segment and find a page which has enough free space to
     * store the record
     */
    for(int i = firstpage; i <= lastpage; i++)
    {
	BufferFrame& frame = bufferManager.getPage(i, true);
	SlottedPage slottedPage(frame.getData());
	
	
	if(slottedPage.getHeader().freeSpace > record.getLen())
	{
	    TID tid = slottedPage.insert(record);
	    
	    bufferManager.unfixPage(frame, true);
	    
	    return tid;
	}
	
	bufferManager.unfixPage(frame, false);
    }
    
    //found no free space, exception
}

bool SPSegment::remove(TID recordId)
{
	return true;
}

bool SPSegment::update(TID recordId, const Record& record)
{
	return true;

}

