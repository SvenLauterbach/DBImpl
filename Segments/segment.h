#ifndef SEGMENT_H
#define SEGMENT_H

#include "../BufferManager/buffermanager.h"
#include "segmentinformation.h"

class Segment
{

public:
    Segment(SegmentInformation info, BufferManager& bm);

protected:
    SegmentInformation getSegmentInformation()
    {
    	return info;
    }

    BufferManager& getBufferManager()
    {
    	return bufferManager;
    }

private:
    SegmentInformation info;
    BufferManager& bufferManager;
};

#endif // SEGMENT_H
