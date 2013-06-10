#ifndef SEGMENT_H
#define SEGMENT_H

#include "segmentinformation.h"

class Segment
{

public:
    Segment(SegmentInformation info);
    
protected:
    SegmentInformation getSegmentInformation()
    {
	return info;
    }

private:
    SegmentInformation info;
};

#endif // SEGMENT_H
