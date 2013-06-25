#ifndef SLOTTEDPAGE_H
#define SLOTTEDPAGE_H
#include "tid.h"
#include "record.hpp"
#include <vector>


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
};

class SlottedPage
{
	SlottedPageHead header;
	SlottedPageSlot slots[1];
};

#endif // SLOTTEDPAGE_H
