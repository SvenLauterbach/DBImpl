#include "sisegment.h"

SISegment::SISegment()
{

}

SegmentInformation SISegment::CreateSegment(SegmentType type, unsigned int size)
{
    /*
     * we should create a Segment so we need to gather the following information:
     *  - ID -> we autoincrement the ids
     *  - type -> parameter
     *  - offset -> it is the offset + size of the last segment
     *  - size -> parameter
     */
    
    /*
     * according to http://www.cplusplus.com/reference/map/map/ a map is always ordered
     * by its key. so we know the last element in the map is the last segment which was
     * inserted, because we autoincrement the key.
     */
    std::map<unsigned int, SegmentInformation>::iterator it = segments.end();
    
    SegmentInformation SegInfos = (*it).second;
    unsigned int id = SegInfos.segmentId + 1;
    std::stringstream sstm;
    sstm << "segment." << id << ".db" << std::endl;

    SegmentInformation newSegInfos(id,
				    type,
				    sstm.str(),
				    size);
    
    segments.insert(std::pair<unsigned int, SegmentInformation>(newSegInfos.segmentId, newSegInfos));
    
    return newSegInfos;
}

SegmentInformation SISegment::GetSegment(unsigned int id)
{
    std::map<unsigned int, SegmentInformation>::iterator it = segments.find(id);
    
    if(it == segments.end())
    {
	//Segment id konnte nicht gefunden werden, ToDo: Exception
    }
    
    return (*it).second;
}



