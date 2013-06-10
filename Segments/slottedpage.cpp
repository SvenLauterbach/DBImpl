#include "slottedpage.h"

SlottedPage::SlottedPage(void* pageData)
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
    std::vector<SlottedPage::SlottedPageSlot>::iterator freeSlot = getFreeSlot(record.getLen());
    
    /* no free space */
    if(freeSlot == slots.end())
    {
	
    }
}

/*
 * ToDo: change return type, iterator is strange and only for the "slots.end()" comparison
 * if we found no free slot
 */
std::vector<SlottedPage::SlottedPageSlot>::iterator SlottedPage::getFreeSlot(unsigned int size)
{
    /* no c++11 for loop :S because of iterator return type */
    for(std::vector<SlottedPage::SlottedPageSlot>::iterator it = slots.begin(); it!=slots.end(); ++it)
    {
	if((*it).isFree && (*it).length > size)
	{
	    return it;
	}
    }
    
    return slots.end();
}



