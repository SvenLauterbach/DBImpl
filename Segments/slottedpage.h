#ifndef SLOTTEDPAGE_H
#define SLOTTEDPAGE_H
#include "tid.h"
#include "record.hpp"
#include <vector>

class SlottedPage
{

public:
        SlottedPage(void* pageData);
        TID insert(const Record& record);
        bool remove(TID recordId);
        const Record& lookup(TID recordId);
        bool update(TID recordId, const Record& record);
	
	class SlottedPageHead {
	public:
	    unsigned int slotCount;
	    unsigned int dataStart; 
	    unsigned int freeSpace;
	};
	
	SlottedPageHead getHeader()
	{
	    return header;
	}

private:
	    
	class SlottedPageSlot {
	public:
	    unsigned int offset;
	    unsigned int length;
	    bool isFree;
	};
	
	SlottedPageHead header;
	std::vector<SlottedPageSlot> slots;
	
	std::vector<SlottedPage::SlottedPageSlot>::iterator getFreeSlot(unsigned int size);
};

#endif // SLOTTEDPAGE_H
