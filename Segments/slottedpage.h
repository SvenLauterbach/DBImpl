#ifndef SLOTTEDPAGE_H
#define SLOTTEDPAGE_H
#include "tid.h"
#include "record.hpp"
#include <vector>
#include "../BufferManager/buffermanager.h"


class SlottedPageSlot {
public:
	void* offset;
	unsigned int length;
	bool isFree;
};

class SlottedPageHead {
public:
	unsigned int slotCount;

	/*
	 * this pointer points to the adress where the first records start
	 */
	void* dataStart;

	/*
	 * this pointer points to the address where the last slot ends
	 * (the address where the free space begins)
	 */
	void* freeSpace; //pointer to the end of the freespace

	/*
	 * the amount of free space in the page. Note: this is the actual free
	 * space, not the space between the freeSpace and dataStart pointer.
	 * Due to the removal of records the page gets fragmented, so this
	 * represents the actual avaiable space.
	 */
	unsigned int avaiablefreeSpace;
};

class SlottedPage
{
public:
	SlottedPageHead header;
	// TODO warum hat eine SlottedPage nur einen Slot? --Andi
	SlottedPageSlot slots[1];

	SlottedPage();
};

#endif // SLOTTEDPAGE_H
