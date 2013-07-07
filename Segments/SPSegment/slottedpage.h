#ifndef SLOTTEDPAGE_H
#define SLOTTEDPAGE_H
#include "../tid.h"
#include "../record.hpp"
#include "SlottedPageSlot.h"
#include "SlottedPageHead.h"
#include <vector>
#include "../../BufferManager/buffermanager.h"




class SlottedPage
{
public:

	SlottedPage();
	unsigned int insert(const Record& record);
	const Record& lookup(unsigned int slotId);
	void update(unsigned int slotId, const Record& record);
	void remove(unsigned int slotId);

	SlottedPageSlot* getSlot(unsigned int slotId);
	bool isEmpty();
	unsigned int getFreeSpace();
	void init();
	bool isCompactable();
	void compact();
	void dump();
	void dump(unsigned int slotId);

private:
	SlottedPageHead header;
	SlottedPageSlot slots[1];

	void* getRecordAddress(unsigned int slotId);
};

#endif // SLOTTEDPAGE_H
