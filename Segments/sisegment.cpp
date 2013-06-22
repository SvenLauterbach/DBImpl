#include "sisegment.h"

SISegment::SISegment() : segments()
{
}

SegmentInformation SISegment::CreateSegment(SegmentType type, unsigned int size)
{
	unsigned int id = 0;

	if(segments.size() != 0)
	{
		SegmentInformation segInfos = segments[id];
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



