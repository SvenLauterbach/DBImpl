#include "segmentinformation.h"

SegmentInformation::SegmentInformation(unsigned int id, SegmentType type, std::string fileName, unsigned int nrOfPages)
 : segmentId(id), type(type), fileName(fileName), nrOfPages(nrOfPages)
{

}

