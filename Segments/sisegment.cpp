#include "sisegment.h"

SISegment::SISegment() : segments()
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
	unsigned int id = 0;

	if(segments.size() != 0)
	{
		std::vector<SegmentInformation>::reverse_iterator it = segments.rbegin();
		SegmentInformation s = (*it);
		id = s.segmentId + 1;
	}
    
    std::stringstream sstm;
    sstm << "segment." << id << ".db";

    SegmentInformation newSegInfos(id,
				    type,
				    sstm.str(),
				    size);

    segments.insert(segments.begin() + id, newSegInfos);
    
    return newSegInfos;
}

SegmentInformation SISegment::GetSegment(unsigned int id)
{

    SegmentInformation newSegInfos = segments[id];
    
    return newSegInfos;
}



