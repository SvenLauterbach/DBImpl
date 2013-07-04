#include "slottedpage.h"

SlottedPage::SlottedPage() : header(), slots() {
	header.dataStart = ((char*)this + PAGE_SIZE);
	header.freeSpace = ((char*)this + sizeof(SlottedPageHead));
	header.avaiablefreeSpace = PAGE_SIZE - sizeof(SlottedPageHead);
}
