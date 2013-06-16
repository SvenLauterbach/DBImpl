#ifndef SEGMENTINFORMATION_H
#define SEGMENTINFORMATION_H

#include <string>
#include <vector>

enum SegmentType { SP, BT};

class SegmentInformation
{

public:
    SegmentInformation(unsigned int id, SegmentType type, std::string fileName, unsigned int nrOfPages);
    unsigned int segmentId;
    SegmentType type;
    unsigned int nrOfPages;
    std::string fileName;
    std::vector<unsigned int> freePages;
};

#endif // SEGMENTINFORMATION_H
