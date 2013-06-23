#include "tid.h"


TID::TID(): slotId(0), pageId(0)
{

}

TID::TID(unsigned int pageId, unsigned int slotId) : slotId(slotId), pageId(pageId)
{
}

unsigned int TID::getPageId()
{
	return pageId;
}

unsigned int TID::getSlotId()
{
	return slotId;
}

