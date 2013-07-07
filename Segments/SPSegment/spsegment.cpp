#include "spsegment.h"

SPSegment::SPSegment(SegmentInformation info, BufferManager& bm) : Segment(info, bm)
{

}

void SPSegment::Dump(TID recordId)
{
	SegmentInformation infos = getSegmentInformation();
	BufferManager& bufferManager = getBufferManager();
	std::string filename = infos.getFileName();
	BufferFrame& frame = bufferManager.getPage(recordId.getPageId(), filename, true);
	SlottedPage* page = static_cast<SlottedPage*>(frame.getData());

	std::cout << "Infos for TID(" << recordId.getPageId() << ", " << recordId.getSlotId() << ")" << std::endl;

	page->dump();
}

const Record& SPSegment::lookup(TID recordId)
{
	SegmentInformation infos = getSegmentInformation();
	BufferManager& bufferManager = getBufferManager();

	/*
	 * first we need to get the page from the bufferManager
	 */
	std::string filename = infos.getFileName();
	BufferFrame& frame = bufferManager.getPage(recordId.getPageId(), filename, true);

	/*
	 * After retrieving the page we have */
	SlottedPage* page = static_cast<SlottedPage*>(frame.getData());

	/*
	 * Now we have the slot, we create the record.
	 * Info: the constructor of the record class copy's the data
	 * provided as a pointer in the parameters to a new buffer
	 */
	SlottedPageSlot* slot = page->getSlot(recordId.getSlotId());

	std::cout << "Infos for TID(" << recordId.getPageId() << ", " << recordId.getSlotId() << ")" << std::endl;
	page->dump(recordId.getSlotId());

	TID possibleReference = slot->isSlotReference();

	bufferManager.unfixPage(frame, false);

	if(possibleReference == TID::NULLTID())
	{
		return page->lookup(recordId.getSlotId());
	}
	else
	{
		return lookup(possibleReference);
	}
}

TID SPSegment::insert(const Record& record)
{
    SegmentInformation infos = getSegmentInformation();
    BufferManager& bm = getBufferManager();

    for(unsigned int i = 0; i <= infos.nrOfPages; i++)
    {
    	BufferFrame& frame = bm.getPage(i, infos.getFileName(), true);

    	SlottedPage* page = (SlottedPage*)frame.getData();

    	/*
    	 * if this page doesn't contain any slot we have to initliaze the pointer
    	 */
    	if(page->isEmpty())
    	{
    		//std::cout << "Initializing new slotted page: " << i << std::endl;
    		page->init();
    	}


    	if(page->isCompactable())
    	{
    		page->compact();
    	}

		/*
		 * calculate the free space
		 *
		 * Page-Layout:
		 * ____________________________________
		 * |______|______|                     |
		 * |            ^- freespace pointer  |
		 * |                                  |
		 * |                   _______________|
		 * |___________________|______________|
		 *                     ^-dataStart pointer
		 *
		 * If we subtract the freespace pointer from the dataStart pointer
		 * we get the space between those 2 pointers
		 */
    	unsigned int freeSpace = page->getFreeSpace();


    	//std::cout << "Insert => Freespace: " << freeSpace << " RecordSize: " << sizeof(SlottedPageSlot) + record.getLen() << std::endl;
		if(freeSpace > sizeof(SlottedPageSlot) + record.getLen())
		{
			unsigned int slotId = page->insert(record);
			TID result(i, slotId);

			bm.unfixPage(frame, true);

			return result;
		}
		else
		{

			bm.unfixPage(frame, false);
		}
    }

    /*
     * If we reach this lines the for loop couln't find some page with enough freespace,
     */
    return TID(0,0);
}


bool SPSegment::remove(TID recordId)
{
	SegmentInformation infos = getSegmentInformation();
	BufferManager& bm = getBufferManager();

	BufferFrame& frame = bm.getPage(recordId.getPageId(), infos.getFileName(), true);
	SlottedPage* page = static_cast<SlottedPage*>(frame.getData());

	/*
	if(page->isCompactable())
	{
		page->compact();
	}*/

	TID possibleReference  = isSlotReference(page, recordId);

	if(possibleReference != TID::NULLTID())
	{
		this->remove(possibleReference);
	}

	page->remove(recordId.getSlotId());

	bm.unfixPage(frame, true);

	return true;
}

bool SPSegment::update(TID recordId, const Record& record)
{
	SegmentInformation infos = getSegmentInformation();
	/*
	 * tidForUpdate holds the tid we want to update
	 * (this can be the tid passed as a parameter or
	 * a reference).
	 */

	/*
	 * 1. We have to lookup the referenced slot and check
	 * if this slot reference another slot or if it
	 * contains the actual data.
	 */
	BufferManager& bm = getBufferManager();
	BufferFrame& frame = bm.getPage(recordId.getPageId(), infos.getFileName(), true);


	SlottedPage* page = static_cast<SlottedPage*>(frame.getData());
	SlottedPageSlot* slot = page->getSlot(recordId.getSlotId());
	TID possibleReference = slot->isSlotReference();

	/*
	if(page->isCompactable())
	{
		page->compact();
	}*/


	if(slot->length >= record.getLen() && possibleReference == TID::NULLTID())
	{
		//In-Place update
		page->update(recordId.getSlotId(), record);
	}
	else
	{
		//check if this is an already referenced slot
		if(possibleReference != TID::NULLTID())
		{
			/*
			 * The slot is already a reference to another slot,
			 * we have to delete the "old" reference and create
			 * a new reference to the updated record, which we just
			 * insert somewhere else.
			 */
			this->remove(possibleReference);

			TID newTid = insert(record);
			slot->createTIDReferenceSlot(newTid);
		}
		else
		{
			/*
			 * the record is not referenced.
			 */
			TID newTid = insert(record);
			slot->createTIDReferenceSlot(newTid);
		}
	}

	bm.unfixPage(frame, true);
}


TID SPSegment::isSlotReference(SlottedPage* page, TID recordId)
{
	SlottedPageSlot* slot = page->getSlot(recordId.getSlotId());
	TID possibleReference = slot->isSlotReference();

	return possibleReference;
}

