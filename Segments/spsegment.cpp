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
	std::string filename = infos.getFileName();
	BufferFrame& frame = bufferManager.getPage(recordId.getPageId(), filename, true);

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
    	BufferFrame& frame = bm.getPage(i, infos.getFileName(), true);

    	SlottedPage* page = (SlottedPage*)frame.getData();

    	/*
    	 * if this page doesn't contain any slot we have to initliaze the pointer
    	 */
    	if(page->header.slotCount == 0)
    	{
    		std::cout << "Initializing new slotted page: " << i << std::endl;
    		InitializePage(page);
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
    	unsigned int freeSpace = getFreeSpace(page);

		if(freeSpace > sizeof(SlottedPageSlot) + record.getLen())
		{
			std::cout << "free space in " << i << " before insert: " << freeSpace << " Bytes" << std::endl;
			std::cout << "insert new record of size " << record.getLen() << " to page " << i << std::endl;
			/*
			 * first we should move the dataStart Pointer. As you can see in
			 * image above the data grow backwards, this means the pointer
			 * should move to the left. To achieve this we have to subtract the
			 * records length from the current datastart address
			 */
			page->header.dataStart = (void*)(page->header.dataStart - record.getLen());

			/*
			 * copy the record data to the new free space
			 */
			memcpy(page->header.dataStart, record.getData(), record.getLen());

			/*
			 * create a Page Slot and then copy its content to the freeSpace Pointer
			 */
			SlottedPageSlot newSlot;
			newSlot.offset = page->header.dataStart;
			newSlot.length = record.getLen();
			newSlot.isFree = false;

			memcpy(page->header.freeSpace, &newSlot, sizeof(newSlot));

			/*
			 * finallay move the freeSpace pointer to the end of the slot we just inserted.
			 * The freespace pointer grows forward, so we have to add the length of the
			 * new slot.
			 */
			page->header.freeSpace = (void*) (page->header.freeSpace + sizeof(newSlot));

			TID result(i, page->header.slotCount);

			/*
			 * increase slotcount (captain obvious)
			 */
			page->header.slotCount++;

			page->header.avaiablefreeSpace -= record.getLen() + sizeof(newSlot);

			/*
			 * after inserting the record write all changes back to disk
			 */
			bm.unfixPage(frame, true);

			std::cout << "returning TID(" << result.getPageId() << ", " << result.getSlotId() << ")" << std::endl;

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

void SPSegment::Compact(SlottedPage* page)
{
	unsigned int freeSpace = getFreeSpace(page);

	if(freeSpace <= (page->header.avaiablefreeSpace / 100) * 20)
	{
		SlottedPage* newPage = static_cast<SlottedPage*>(malloc(PAGE_SIZE));

		InitializePage(newPage);

		memcpy(newPage, &(page->header), sizeof(SlottedPageHead));

		for(int i = 0; i <= page->header.slotCount; i++)
		{
			if(!page->slots[i].isFree)
			{
				newPage->slots[i] = page->slots[i];
				//memcpy()
			}
		}
	}
}

void SPSegment::InitializePage(SlottedPage* page)
{
	page->header.dataStart = ((char*)page + PAGE_SIZE);
	page->header.freeSpace = ((char*)page + sizeof(SlottedPageHead));
	page->header.avaiablefreeSpace = PAGE_SIZE - sizeof(SlottedPageHead);
}

unsigned int SPSegment::getFreeSpace(SlottedPage* page)
{
	unsigned int freeSpace = (char*)page->header.dataStart - (char*)page->header.freeSpace;
	return freeSpace;
}

bool SPSegment::remove(TID recordId)
{
	SegmentInformation infos = getSegmentInformation();
	BufferManager& bm = getBufferManager();

	BufferFrame& frame = bm.getPage(recordId.getPageId(), infos.getFileName(), true);
	SlottedPageSlot* slot = getSlot(frame, recordId);

	slot->isFree = true;

	SlottedPage* page = (SlottedPage*)frame.getData();

	page->header.avaiablefreeSpace += slot->length;

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
	bool isReferenced = false;

	/*
	 * 1. We have to lookup the referenced slot and check
	 * if this slot reference another slot or if it
	 * contains the actual data.
	 */
	BufferManager& bm = getBufferManager();
	BufferFrame& frame = bm.getPage(recordId.getPageId(), infos.getFileName(), true);


	SlottedPage* page = static_cast<SlottedPage*>(frame.getData());
	SlottedPageSlot* slot = getSlot(frame, recordId);
	SlottedPageSlot* referencedSlot = nullptr;

	TID possibleReference = isSlotReference(*slot);

	if(slot->length >= record.getLen() && possibleReference == TID::NULLTID())
	{
		//In-Place update
		page->header.avaiablefreeSpace += (slot->length - record.getLen());

		const Record& currentRecord = this->lookup(recordId);
		Record p(currentRecord.getLen(), record.getData());

		memcpy(slot->offset, p.getData(), p.getLen());
		slot->length = currentRecord.getLen();
	}
	else
	{
		page->header.avaiablefreeSpace += slot->length;

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
			createTIDReferenceSlot(*slot, newTid);
		}
		else
		{
			/*
			 * the record is not referenced.
			 */
			TID newTid = insert(record);
			createTIDReferenceSlot(*slot, newTid);
		}
	}

	/*
	const Record& currentRecord = lookup(recordId);





	if(possibleReference != TID::NULLTID())
	{
		//ok, its a reference to another slot
		//tidForUpdate = possibleReference;
		//referencedSlot = getSlot(frame, recordId);
		isReferenced = true;
	}


	/*
	 * if the updated record is smaller or equal
	 * than the old one, we can make an in-place update
	 */
	/*
	if(currentRecord.getLen() >= record.getLen())
	{
		Record p(currentRecord.getLen(), record.getData());

		memcpy(slot->offset, p.getData(), p.getLen());
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
	/*
		if(possibleReference == TID::NULLTID())
		{

		}
		else
		{

		}
	}*/
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
	SlottedPage* page = (SlottedPage*)frame.getData();

	return &(page->slots[recordId.getSlotId()]);
	//return (SlottedPageSlot*)(frame.getData() + sizeof(SlottedPageHead) + (recordId.getSlotId() * sizeof(SlottedPageHead)));
}

TID SPSegment::isSlotReference(SlottedPageSlot slot)
{
	long long magicBytes = std::numeric_limits<long long>().max();
	long long magicBytesBuffer;
	TID tid = TID::NULLTID();
	void* buffer = static_cast<void*>(&slot);

	memcpy(&magicBytesBuffer, buffer, sizeof(long long));

	if(magicBytes == magicBytesBuffer)
	{
		memcpy(&tid, buffer + sizeof(long long), sizeof(TID));
	}

	return tid;
}

void SPSegment::createTIDReferenceSlot(SlottedPageSlot& slot, TID tid)
{
	std::cout << "creating slot reference for TID(" << tid.getPageId() << ", " << tid.getSlotId() << ")" << std::endl;
	long long magicByte = std::numeric_limits<long long>().max();
	void* buffer = static_cast<void*>(&slot);
	memcpy(buffer, &magicByte, sizeof(magicByte));
	memcpy((buffer + sizeof(magicByte)), &tid, sizeof(tid));
}

