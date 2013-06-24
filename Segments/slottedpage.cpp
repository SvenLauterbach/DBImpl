#include "slottedpage.h"

SlottedPage::SlottedPage()
{
    
}

const Record& SlottedPage::lookup(TID recordId)
{

}

TID SlottedPage::insert(const Record& record)
{
    /*
     * First we have to check if there is any free slot and if there
     * is a free slot we have to check if its large enough to store the 
     * record data
     */
    int freeSlot = getFreeSlot(record.getLen());
    
    /* no free space */
    if(freeSlot < 0)
    {
    	//return TID::NULL;
    }

    SlottedPageSlot slot = slots[freeSlot];
    header.freeSpace =  (void*)header.freeSpace - record.getLen();
    memcpy(header.freeSpace, record.getData(), record.getLen());
    slot.isFree = false;
    slot.length = record.getLen();
    slot.offset = header.freeSpace;

}

/*
 * ToDo: change return type, iterator is strange and only for the "slots.end()" comparison
 * if we found no free slot
 */
int SlottedPage::getFreeSlot(unsigned int size)
{
    /* no c++11 for loop :S because of iterator return type */
    for(std::vector<SlottedPageSlot>::iterator it = slots.begin(); it!=slots.end(); ++it)
    {
		if(it->isFree && it->length > size)
		{
			return slots.begin() - it;
		}
    }
    
    return -1;
}



