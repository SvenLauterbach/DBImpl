#ifndef SEGMENTINFORMATION_H
#define SEGMENTINFORMATION_H

enum SegmentType { SP, BT};

class SegmentInformation
{

public:
    SegmentInformation(unsigned int id, SegmentType type, unsigned int offset, unsigned int nrOfPages);
    unsigned int segmentId;
    SegmentType type;
    unsigned int offset;
    unsigned int nrOfPages;
};

#endif // SEGMENTINFORMATION_H
