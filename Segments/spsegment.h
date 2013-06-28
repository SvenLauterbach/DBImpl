#ifndef SPSEGMENT_H
#define SPSEGMENT_H
#include "segment.h"
#include "slottedpage.h"
#include "tid.h"
#include "record.hpp"
#include "../BufferManager/buffermanager.h"
#include "slottedpage.h"

class SPSegment : public Segment
{

public:
    SPSegment(SegmentInformation info, BufferManager& bufferManager);
    TID insert(const Record& record);
    bool remove(TID recordId);
    const Record& lookup(TID recordId);
    bool update(TID recordId, const Record& record);

private:
    void createTIDReferenceSlot(SlottedPageSlot& slot, TID tid);
    SlottedPageSlot* getSlot(BufferFrame& frame, TID recordId);
    TID isSlotReference(SlottedPageSlot slot);
};

#endif // SPSEGMENT_H
