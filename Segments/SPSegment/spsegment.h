#ifndef SPSEGMENT_H
#define SPSEGMENT_H
#include "../segment.h"
#include "slottedpage.h"
#include "../tid.h"
#include "../record.hpp"
#include "../../BufferManager/buffermanager.h"
#include "slottedpage.h"

class SPSegment : public Segment
{

public:
    SPSegment(SegmentInformation info, BufferManager& bufferManager);
    TID insert(const Record& record);
    bool remove(TID recordId);
    const Record& lookup(TID recordId);
    bool update(TID recordId, const Record& record);

    class iterator
    {
    public:

		iterator(TID tid, BufferManager& bm, SegmentInformation segInfos)
    		: tid(tid),
    		  bm(bm),
    		  infos(segInfos)
    	{

    	}

		iterator operator++()
		{
			/*
			 * first we need the header of the current page and look if we reach the end of the slots
			 */
			BufferFrame& frame = bm.getPage(tid.getPageId(), infos.getFileName(), false);

			SlottedPageHead* header = static_cast<SlottedPageHead*>(frame.getData());

			if(header->getSlotCount() == 0)
			{
				tid = TID::NULLTID();

				return *this;
			}
			else if(header->getSlotCount() - 1 > tid.getSlotId())
			{
				tid = TID(tid.getPageId(), tid.getSlotId() + 1);
				return *this;
			}
			else
			{
				/*
				 * the iterator is on the last slot of this page.
				 * check if this is the last page or if we can
				 * iterate to the next page.
				 */
				if(infos.nrOfPages - 1 == tid.getPageId())
				{
					tid = TID::NULLTID();
					return *this;
				}

				tid = TID(tid.getPageId() + 1, 0);

				return *this;
			}
		}

		TID& operator*() { return tid; }
		TID* operator->() { return &tid; }
		bool operator==(const iterator& rhs) { return tid == rhs.tid; }
		bool operator!=(const iterator& rhs) { return tid != rhs.tid; }

	private:
		TID tid;
		BufferManager& bm;
		SegmentInformation infos;
    };

    iterator begin()
    {
    	SegmentInformation infos = getSegmentInformation();
    	BufferManager& bm = getBufferManager();

    	if(infos.nrOfPages == 0)
    	{
    		return end();
    	}

    	BufferFrame& frame = bm.getPage(0, infos.getFileName(), true);
    	SlottedPageHead* head = static_cast<SlottedPageHead*>(frame.getData());

    	if(head->getSlotCount() == 0)
    	{
    		return end();
    	}

    	TID tid(0,0);

    	return iterator(tid, bm, infos);
    }

    iterator end()
    {
    	SegmentInformation infos = getSegmentInformation();
    	BufferManager& bm = getBufferManager();

    	return iterator(TID::NULLTID(), bm, infos);
    }

    /*
    static void createTIDReferenceSlot(SlottedPageSlot* slot, TID tid);
	static TID isSlotReference(SlottedPageSlot* slot);*/
	static TID isSlotReference(SlottedPage* page, TID recordId);
	void Dump(TID recordId);

private:

};

#endif // SPSEGMENT_H
