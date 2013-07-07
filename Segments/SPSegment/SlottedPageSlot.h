/*
 * SlottedPageSlot.h
 *
 *  Created on: Jul 7, 2013
 *      Author: sven
 */

#ifndef SLOTTEDPAGESLOT_H_
#define SLOTTEDPAGESLOT_H_

#include <iostream>
#include <string.h>
#include "../tid.h"

class SlottedPageSlot {
public:
	unsigned int offset;
	unsigned int length;
	bool isFree;

	SlottedPageSlot();
	TID isSlotReference();
	void createTIDReferenceSlot(TID tid);
	void dump(char* recordData);
};

#endif /* SLOTTEDPAGESLOT_H_ */
