#ifndef SISEGMENT_H
#define SISEGMENT_H
#include "segmentmanager.h"
#include "segmentinformation.h"
#include "segment.h"
#include <map>

class SISegment
{

public:
    SISegment();
    unsigned int CreateSegment(SegmentType type, unsigned int size);
    SegmentInformation GetSegment(unsigned int id);
    
private:
    /* map segments id's to pages */
    std::map<unsigned int, SegmentInformation> segments;
};

#endif // SISEGMENT_H
