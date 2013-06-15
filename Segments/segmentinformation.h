#ifndef SEGMENTINFORMATION_H
#define SEGMENTINFORMATION_H

#include <string>

enum SegmentType { SP, BT};

class SegmentInformation
{

public:
    SegmentInformation(unsigned int id, SegmentType type, std::string fileName, unsigned int nrOfPages);
    unsigned int segmentId;
    SegmentType type;
    unsigned int nrOfPages;
    std::string fileName;
};

#endif // SEGMENTINFORMATION_H
