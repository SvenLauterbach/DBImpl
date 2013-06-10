#ifndef SPSEGMENT_H
#define SPSEGMENT_H
#include "segment.h"
#include "tid.h"
#include "record.hpp"
#include "../BufferManager/buffermanager.h"

class SPSegment : public Segment
{

public:
    SPSegment(SegmentInformation info, BufferManager& bufferManager);
    TID insert(const Record& record);
    bool remove(TID recordId);
    const Record& lookup(TID recordId);
    bool update(TID recordId, const Record& record);
    
private:
    BufferManager& bufferManager;
};

#endif // SPSEGMENT_H
