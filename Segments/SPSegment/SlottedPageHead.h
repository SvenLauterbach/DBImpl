/*
 * SlottedPageHead.h
 *
 *  Created on: Jul 7, 2013
 *      Author: sven
 */

#ifndef SLOTTEDPAGEHEAD_H_
#define SLOTTEDPAGEHEAD_H_

#include "../../BufferManager/buffermanager.h"


class SlottedPageHead {

private:
	unsigned int slotCount;

	/*
	 * this pointer points to the adress where the first records start
	 */
	unsigned int dataStart;

	/*
	 * this pointer points to the address where the last slot ends
	 * (the address where the free space begins)
	 */
	unsigned int freeSpace; //pointer to the end of the freespace

	/*
	 * the amount of free space in the page. Note: this is the actual free
	 * space, not the space between the freeSpace and dataStart pointer.
	 * Due to the removal of records the page gets fragmented, so this
	 * represents the actual avaiable space.
	 */
	unsigned int avaiablefreeSpace;

public:

	SlottedPageHead();
	void* getDataStartPointer();
	unsigned int getDataStart();
	void increaseDataStartPointer(unsigned int length);
	void* getFreeSpacePointer();
	void increaseFreeSpacePointer(unsigned int length);
	unsigned int getAvaiableFreeSpace();
	void increaseAvaiableFreeSpace(unsigned int value);
	void decreaseAvaiableFreeSpace(unsigned int value);
	unsigned int getFreeSpace();
	unsigned int getSlotCount();
	void addSlot();
};

#endif /* SLOTTEDPAGEHEAD_H_ */
