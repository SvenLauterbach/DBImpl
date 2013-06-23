#include "segmentinformation.h"

SegmentInformation::SegmentInformation(unsigned int id, SegmentType type, std::string fileName, unsigned int nrOfPages)
 : segmentId(id), type(type), fileName(fileName), nrOfPages(nrOfPages), freePages()
{

}

SegmentInformation::SegmentInformation(const SegmentInformation& rhs)
	: fileName(rhs.fileName),
	  segmentId(rhs.segmentId),
	  type(rhs.type),
	  nrOfPages(rhs.nrOfPages),
	  freePages(rhs.freePages)
{

}

