#ifndef SLOTTEDPAGE_H
#define SLOTTEDPAGE_H
#include "tid.h"
#include "record.hpp"
#include <vector>


class SlottedPageSlot {
public:
	unsigned int offset;
	unsigned int length;
	bool isFree;
};

class SlottedPageHead {
public:
	unsigned int slotCount;
	unsigned int dataStart;
	unsigned int freeSpace;
};

class SlottedPage
{

public:
	SlottedPage(void* pageData);

	TID insert(const Record& record);
	bool remove(TID recordId);
	const Record& lookup(TID recordId);
	bool update(TID recordId, const Record& record);

	SlottedPageHead getHeader()
	{
	    return header;
	}

private:

	SlottedPageHead header;
	std::vector<SlottedPageSlot> slots;

	int getFreeSlot(unsigned int size);
};

#endif // SLOTTEDPAGE_H
