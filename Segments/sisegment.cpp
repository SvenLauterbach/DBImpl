#include "sisegment.h"

SISegment::SISegment() : segmentCount(0)
{
}


SegmentInformation SISegment::CreateSegment(SegmentType type, unsigned int size)
{
	/*
	 * before creating a segment we need to determine the id.
	 * If this is not the first segment we increment the id
	 * of the last segment
	 *
	 */
	unsigned int id = segmentCount;
    
    std::stringstream sstm;
    sstm << "segment." << id << ".db";

    SegmentInformation newSegInfos(id,
				    type,
				    sstm.str(),
				    size);

    memcpy((segments + id), &newSegInfos, sizeof(newSegInfos));
    
    segmentCount++;

    return newSegInfos;
}

SegmentInformation SISegment::GetSegment(unsigned int id)
{
    SegmentInformation newSegInfos = segments[id];
    
    return newSegInfos;
}



