/*
 * FreeSpaceInventory.cpp
 *
 *  Created on: Jun 16, 2013
 *      Author: sven
 */

#include "FreeSpaceInventory.h"

FreeSpaceInventory::FreeSpaceInventory(SegmentInformation info) : info(info) {
	// TODO Auto-generated constructor stub

}

FreeSpaceInventory::~FreeSpaceInventory() {
	// TODO Auto-generated destructor stub
}

unsigned int FreeSpaceInventory::freePage()
{
	/*
	struct stat filestatus;
	stat(info.fileName.c_str(), &filestatus);

	return ((filestatus.st_size / PAGE_SIZE) - info.nrOfPages);
	*/
	std::vector<unsigned int>::iterator it = info.freePages.end();
	return (*it);
}

