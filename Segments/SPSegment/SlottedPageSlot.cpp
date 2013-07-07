/*
 * SlottedPageSlot.cpp
 *
 *  Created on: Jul 7, 2013
 *      Author: sven
 */

#include "SlottedPageSlot.h"

SlottedPageSlot::SlottedPageSlot() {
	// TODO Auto-generated constructor stub

}

TID SlottedPageSlot::isSlotReference()
{
	long long magicBytes = std::numeric_limits<long long>().max();
	long long magicBytesBuffer;
	TID tid = TID::NULLTID();

	memcpy(&magicBytesBuffer, this, sizeof(long long));

	if(magicBytes == magicBytesBuffer)
	{
		memcpy(&tid, (char*)this + sizeof(long long), sizeof(TID));
	}

	return tid;
}

void SlottedPageSlot::createTIDReferenceSlot(TID tid)
{
	//std::cout << "creating slot reference for TID(" << tid.getPageId() << ", " << tid.getSlotId() << ")" << std::endl;
	long long magicByte = std::numeric_limits<long long>().max();
	memcpy(this, &magicByte, sizeof(magicByte));
	memcpy(((char*)this + sizeof(magicByte)), &tid, sizeof(tid));
}

void SlottedPageSlot::dump(char* recordData)
{
	std::cout << "length: " << length << std::endl;
	std::cout << "offset: " << offset << std::endl;
	std::cout << "isEmpty: " << isFree << std::endl;

	std::string text(recordData, length);

	std::cout << "data: " << text << std::endl;
}

