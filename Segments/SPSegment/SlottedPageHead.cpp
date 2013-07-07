/*
 * SlottedPageHead.cpp
 *
 *  Created on: Jul 7, 2013
 *      Author: sven
 */

#include "SlottedPageHead.h"

SlottedPageHead::SlottedPageHead()  :
	dataStart(PAGE_SIZE),
	freeSpace(sizeof(SlottedPageHead)),
	avaiablefreeSpace(PAGE_SIZE - sizeof(SlottedPageHead)),
	slotCount(0)
{
	// TODO Auto-generated constructor stub

}

void* SlottedPageHead::getDataStartPointer()
{
	return (char*)this + dataStart;
}

unsigned int SlottedPageHead::getDataStart()
{
	return dataStart;
}

void SlottedPageHead::increaseDataStartPointer(unsigned int length)
{
	dataStart -= length;
}

void* SlottedPageHead::getFreeSpacePointer()
{
	return (char*)this + freeSpace;
}

void SlottedPageHead::increaseFreeSpacePointer(unsigned int length)
{
	freeSpace += length;
}

unsigned int SlottedPageHead::getAvaiableFreeSpace()
{
	return avaiablefreeSpace;
}

void SlottedPageHead::increaseAvaiableFreeSpace(unsigned int value)
{
	//std::cout << "FreeSpace: " << getFreeSpace();
	//std::cout << " old avaiable space: " << avaiablefreeSpace;
	avaiablefreeSpace += value;
	//std::cout << "(" << value << ")" <<" new availablespace: " << avaiablefreeSpace << std::endl;
}

void SlottedPageHead::decreaseAvaiableFreeSpace(unsigned int value)
{
	//std::cout << "FreeSpace: " << getFreeSpace();
	//std::cout << " old avaiable space: " << avaiablefreeSpace;
	avaiablefreeSpace -= value;
	//std::cout << "(" << value << ")" <<" new availablespace: " << avaiablefreeSpace << std::endl;

}

unsigned int SlottedPageHead::getFreeSpace()
{
	return dataStart - freeSpace;
}

unsigned int SlottedPageHead::getSlotCount()
{
	return slotCount;
}

void SlottedPageHead::addSlot()
{
	slotCount++;
}

