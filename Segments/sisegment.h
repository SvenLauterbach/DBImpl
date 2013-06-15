#ifndef SISEGMENT_H
#define SISEGMENT_H
#include "segmentmanager.h"
#include "segmentinformation.h"
#include "segment.h"
#include <string>
#include <sstream>
#include <map>

class SISegment
{

public:
    SISegment();
    SegmentInformation CreateSegment(SegmentType type, unsigned int size);
    SegmentInformation GetSegment(unsigned int id);
    void Grow(unsigned int id, unsigned int size);
    
private:
    /* map segments id's to pages */
    std::map<unsigned int, SegmentInformation> segments;
};

#endif // SISEGMENT_H
