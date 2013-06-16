/*
 * FreeSpaceInventory.h
 *
 *  Created on: Jun 16, 2013
 *      Author: sven
 */

#ifndef FREESPACEINVENTORY_H_
#define FREESPACEINVENTORY_H_

#include "segmentinformation.h"
#include "../BufferManager/buffermanager.h"
#include <sys/stat.h>

class FreeSpaceInventory {
public:
	FreeSpaceInventory(SegmentInformation info);
	virtual ~FreeSpaceInventory();

	unsigned int freePage();

private:
	SegmentInformation info;
};

#endif /* FREESPACEINVENTORY_H_ */
