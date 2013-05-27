#include "segmentinformation.h"

SegmentInformation::SegmentInformation(unsigned int id, SegmentType type, unsigned int offset, unsigned int nrOfPages)
 : segmentId(id), type(type), offset(offset), nrOfPages(nrOfPages)
{

}

