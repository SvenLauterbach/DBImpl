#include "slottedpage.h"

SlottedPage::SlottedPage() : header(), slots() {

}

unsigned int SlottedPage::insert(const Record& record)
{
	header.decreaseAvaiableFreeSpace(record.getLen() + sizeof(SlottedPageSlot));
	unsigned int slotId = header.getSlotCount();

	/*
	 * first we should move the dataStart Pointer. As you can see in
	 * image above the data grow backwards, this means the pointer
	 * should move to the left. To achieve this we have to subtract the
	 * records length from the current datastart address
	 */
	header.increaseDataStartPointer(record.getLen());

	/*
	 * copy the record data to the new free space
	 */
	memmove(header.getDataStartPointer(), record.getData(), record.getLen());

	/*
	 * create a Page Slot and then copy its content to the freeSpace Pointer
	 */
	SlottedPageSlot newSlot;
	newSlot.offset = header.getDataStart();
	newSlot.length = record.getLen();
	newSlot.isFree = false;

	slots[slotId] = newSlot;

	/*
	 * finallay move the freeSpace pointer to the end of the slot we just inserted.
	 * The freespace pointer grows forward, so we have to add the length of the
	 * new slot.
	 */
	header.increaseFreeSpacePointer(sizeof(SlottedPageSlot));

	header.addSlot();


	return slotId;
}

void SlottedPage::update(unsigned int slotId, const Record& record)
{
	header.increaseAvaiableFreeSpace(slots[slotId].length);

	memset(getRecordAddress(slotId), 0, slots[slotId].length);

	slots[slotId].length = record.getLen();

	void* data = (char*)this + slots[slotId].offset;
	memmove(data, record.getData(), record.getLen());

	header.decreaseAvaiableFreeSpace(record.getLen());
}

void SlottedPage::remove(unsigned int slotId)
{
	slots[slotId].isFree = true;
	header.increaseAvaiableFreeSpace(slots[slotId].length);
}

const Record& SlottedPage::lookup(unsigned int slotId)
{
	//std::cout << (void*) this << " slot " << slotId << " length: " << slots[slotId].length << " - offest: " << getRecordAddress(slotId) << std::endl;
	char* pointer = (char*)getRecordAddress(slotId);
	Record* record = new Record(slots[slotId].length, pointer);

	return *record;
}

SlottedPageSlot* SlottedPage::getSlot(unsigned int slotId)
{
	return &slots[slotId];
}

bool SlottedPage::isEmpty()
{
	return header.getSlotCount() == 0;
}

void SlottedPage::init()
{
	header = SlottedPageHead();
	/*
	std::cout << std::endl;
	std::cout << "Page initialized:" << std::endl;
	std::cout << "  FreeSpace: " << header.getFreeSpace();
	std::cout << "  AvailableSpace: " << header.getAvaiableFreeSpace();
	std::cout << std::endl;
	*/
}

unsigned int SlottedPage::getFreeSpace()
{
	return header.getFreeSpace();
}

bool SlottedPage::isCompactable()
{
	if(header.getFreeSpace() <= (header.getAvaiableFreeSpace() / 100) * 20)
	{
		return true;
	}

	return false;
}

void SlottedPage::compact()
{
	SlottedPage* page = static_cast<SlottedPage*>(malloc(PAGE_SIZE));
	page->init();

	for(int i = 0; i < header.getSlotCount(); i++)
	{
		SlottedPageSlot* slot = this->getSlot(i);

		// just copy a slot reference
		if(slot->isSlotReference() != TID::NULLTID())
		{
			page->slots[i] = *slot;
			page->header.addSlot();
			page->header.increaseFreeSpacePointer(sizeof(SlottedPageSlot));
			page->header.decreaseAvaiableFreeSpace(sizeof(SlottedPageSlot));
		}
		else if(slot->isFree == true)
		{
			page->header.decreaseAvaiableFreeSpace(sizeof(SlottedPageSlot));
			unsigned int slotId = page->header.getSlotCount();

			SlottedPageSlot newSlot;
			newSlot.isFree = true;
			newSlot.length = 0;
			newSlot.offset = page->header.getDataStart();

			page->slots[slotId] = newSlot;

			page->header.increaseFreeSpacePointer(sizeof(SlottedPageSlot));
			page->header.addSlot();

			/*memcpy((char*)page + sizeof(SlottedPageHead) + (i + sizeof(SlottedPageSlot)),
				   (char*)this + sizeof(SlottedPageHead) + (i + sizeof(SlottedPageSlot)),
				   sizeof(SlottedPageSlot));*/
		}
		else
		{
			/*
			memcpy((char*)page + sizeof(SlottedPageHead) + (i + sizeof(SlottedPageSlot)),
				   (char*)this + sizeof(SlottedPageHead) + (i + sizeof(SlottedPageSlot)),
				   sizeof(SlottedPageSlot));
			memcpy((char*)page + slot->offset, (char*)this + slot->offset, sizeof(slot->length));
			*/

			page->insert(Record(slot->length, (char*)getRecordAddress(i)));
		}
	}

	memmove((char*)this, (char*)page, PAGE_SIZE);
}

void SlottedPage::dump()
{

	std::cout << std::endl;
	std::cout << "Header:" << std::endl;
	std::cout << "Available Free Space: " << header.getAvaiableFreeSpace() << std::endl;
	std::cout << "data start:" << header.getDataStart() << std::endl;
	std::cout << "free space start: " << header.getFreeSpace() << std::endl;
	std::cout << "slot count: " << header.getSlotCount() << std::endl;
	std::cout << std::endl;
	std::cout << "Slots:" << std::endl;

	for(int i = 0; i < header.getSlotCount(); i++)
	{
		SlottedPageSlot slot = slots[i];
		std::cout << "Slot " << i << std::endl;

		TID possibleSlotReference = slot.isSlotReference();
		if(possibleSlotReference != TID::NULLTID())
		{
			std::cout << "is reference to TID(" << possibleSlotReference.getPageId() << ", " << possibleSlotReference.getSlotId() << ")" << std::endl;
		}
		else if(!slot.isFree)
		{
			slot.dump((char*)getRecordAddress(i));
		}

		std::cout << std::endl;
	}
}

void SlottedPage::dump(unsigned int slotId)
{
	slots[slotId].dump((char*) getRecordAddress(slotId));
}

void* SlottedPage::getRecordAddress(unsigned int slotId)
{
	return (char*) this + slots[slotId].offset;
}
