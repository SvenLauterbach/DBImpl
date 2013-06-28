#include "segmentinformation.h"

SegmentInformation::SegmentInformation(unsigned int id, SegmentType type, unsigned int nrOfPages)
 : segmentId(id), type(type), nrOfPages(nrOfPages), freePages()
{

}

SegmentInformation::SegmentInformation() {
}

SegmentInformation::SegmentInformation(const SegmentInformation& rhs)
	: segmentId(rhs.segmentId),
	  type(rhs.type),
	  nrOfPages(rhs.nrOfPages),
	  freePages(rhs.freePages)
{

}

