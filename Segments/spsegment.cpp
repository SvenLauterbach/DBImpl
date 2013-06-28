#include "spsegment.h"

SPSegment::SPSegment(SegmentInformation info, BufferManager& bm) : Segment(info, bm)
{

}

const Record& SPSegment::lookup(TID recordId)
{
	SegmentInformation infos = getSegmentInformation();
	BufferManager& bufferManager = getBufferManager();

	/*
	 * first we need to get the page from the bufferManager
	 */
	BufferFrame& frame = bufferManager.getPage(recordId.getPageId(), true);

	/*
	 * After retrieving the page we have */
	SlottedPageSlot* slot = getSlot(frame, recordId);

	/*
	 * Now we have the slot, we create the record.
	 * Info: the constructor of the record class copy's the data
	 * provided as a pointer in the parameters to a new buffer
	 */
	Record* record = new Record(slot->length, (char*)slot->offset);

	return *record;
}



TID SPSegment::insert(const Record& record)
{
    SegmentInformation infos = getSegmentInformation();
    BufferManager& bm = getBufferManager();

    for(unsigned int i = 0; i <= infos.nrOfPages; i++)
    {
    	BufferFrame& frame = bm.getPage(i, true);

    	SlottedPageHead* header = (SlottedPageHead*)frame.getData();

    	/*
    	 * calculate the free space
    	 * ____________________________________
    	 * |____________|                     |
    	 * |            ^- freespace pointer  |
    	 * |                                  |
    	 * |                   _______________|
    	 * |___________________|______________|
    	 *                     ^-dataStart pointer
    	 *
    	 * If we subtract the freespace pointer from the dataStart pointer
    	 * we get the space between those 2 pointers
    	 */
    	unsigned int freeSpace = (&(header->dataStart) - &(header->freeSpace));

    	if(freeSpace > sizeof(SlottedPageSlot) + record.getLen())
    	{
    		/*
    		 * first we should move the dataStart Pointer. As you can see in
    		 * image above the data grow backwards, this means the pointer
    		 * should move to the left. To achieve this we have to subtract the
    		 * records length from the current datastart address
    		 */
    		header->dataStart = (void*)(header->dataStart - record.getLen());

    		/*
    		 * copy the record data to the new free space
    		 */
    		memcpy(header->dataStart, record.getData(), record.getLen());

    		/*
    		 * create a Page Slot and then copy its content to the freeSpace Pointer
    		 */
    		SlottedPageSlot newSlot;
    		newSlot.offset = header->dataStart;
    		newSlot.length = record.getLen();
    		newSlot.isFree = false;

    		memcpy(header->freeSpace, &newSlot, sizeof(newSlot));

    		/*
    		 * finallay move the freeSpace pointer to the end of the slot we just inserted.
    		 * The freespace pointer grows forward, so we have to add the length of the
    		 * new slot.
    		 */
    		header->freeSpace = (void*) (header->freeSpace + sizeof(newSlot));

    		/*
    		 * increase slotcount
    		 */
    		header->slotCount++;

    		/*
    		 * after inserting the record write all changes back to disk
    		 */
    		bm.unfixPage(frame, true);

    		TID result(i, header->slotCount);

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

	BufferFrame& frame = bm.getPage(recordId.getPageId(), true);
	SlottedPageSlot* slot = getSlot(frame, recordId);

	slot->isFree = true;

	bm.unfixPage(frame, true);

	return true;
}

bool SPSegment::update(TID recordId, const Record& record)
{
	/*
	 * tidForUpdate holds the tid we want to update
	 * (this can be the tid passed as a parameter or
	 * a reference).
	 */
	TID tidForUpdate = recordId;

	/*
	 * 1. We have to lookup the referenced slot and check
	 * if this slot reference another slot or if it
	 * contains the actual data.
	 */
	BufferManager& bm = getBufferManager();
	BufferFrame& frame = bm.getPage(recordId.getPageId(), true);
	SlottedPageSlot* slot = getSlot(frame, recordId);

	TID possibleReference = isSlotReference(*slot);

	if(possibleReference != TID::NULLTID())
	{
		//ok, its a reference to another slot
		tidForUpdate = possibleReference;
	}

	const Record& currentRecord = lookup(tidForUpdate);

	/*
	 * if the updated record is smaller or equal
	 * than the old one, we can make an in-place update
	 */
	if(currentRecord.getLen() >= record.getLen())
	{
		Record p(currentRecord.getLen(), record.getData());

		memcpy(&p, &currentRecord, sizeof(p));
		slot->length = currentRecord.getLen();
	}
	else
	{
		/*
		 * the new data is larger than the old data, so
		 * we have to create a new record. This new Record
		 * should be referenced. But first we have to check
		 * if the record is already referenced:
		 *
		 * slot -> references other TID -> slot with actual data
		 */
		if(possibleReference == TID::NULLTID())
		{
			/*
			 * the record is not referenced.
			 */
			TID newTid = insert(record);
			createTIDReferenceSlot(*slot, newTid);
		}
		else
		{
			/*
			 * The slot is already a reference to another slot,
			 * we have to delete the "old" reference and create
			 * a new reference to the updated record, which we just
			 * insert somewhere else.
			 */
			this->remove(possibleReference);

			TID newTid = insert(record);
			createTIDReferenceSlot(*slot, newTid);
		}
	}
}

SlottedPageSlot* SPSegment::getSlot(BufferFrame& frame, TID recordId)
{

	/* Getting the address of the slot is quite simple, just add the fixed size
	 * header and n size of the slots, where n is the slot id we want
	 * to access.
	 *
	 * _______________________________________________________________________
	 * | fixed size header | slot | slot | ... | slot |
	 * |                   ^- pointer to the first slot
	 */
	return (SlottedPageSlot*)(frame.getData() + sizeof(SlottedPageHead) + (recordId.getSlotId() * sizeof(SlottedPageHead)));
}

TID SPSegment::isSlotReference(SlottedPageSlot slot)
{
	long long magicBytes = std::numeric_limits<long long>().max();
	long long magicBytesBuffer;
	TID tid = TID::NULLTID();

	memcpy(&magicBytesBuffer, &slot, 8);

	if(magicBytes == magicBytesBuffer)
	{
		memcpy(&tid, (&slot + 8), 8);
	}

	return tid;
}

void SPSegment::createTIDReferenceSlot(SlottedPageSlot& slot, TID tid)
{
	long long magicByte = std::numeric_limits<long long>().max();
	memcpy(&slot, &magicByte, sizeof(long long));
	memcpy((&slot + sizeof(long long)), &tid, sizeof(long long));
}

