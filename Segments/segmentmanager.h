#ifndef SEGMENTMANAGER_H
#define SEGMENTMANAGER_H

#include "../BufferManager/buffermanager.h"
#include "segment.h"
#include "sisegment.h"
#include <memory>
#include "segmentinformation.h"

typedef unsigned int SegmentID; 

class SegmentManager
{

public:
    SegmentManager(BufferManager& bufferManager);
    SegmentID createSegment(SegmentType segmentType, unsigned int size);
    Segment& getSegment(SegmentID id);
    
private:
    BufferManager& bufferManager;
};

#endif // SEGMENTMANAGER_H
