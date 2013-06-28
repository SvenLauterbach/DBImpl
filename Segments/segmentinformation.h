#ifndef SEGMENTINFORMATION_H
#define SEGMENTINFORMATION_H

#include <string>
#include <vector>
#include <sstream>

enum SegmentType { SP, BT};

struct SegmentInformation
{

public:
	SegmentInformation();
    SegmentInformation(unsigned int id, SegmentType type, unsigned int nrOfPages);
    SegmentInformation(const SegmentInformation& rhs);

    unsigned int segmentId;
    SegmentType type;
    unsigned int nrOfPages;
    std::vector<unsigned int> freePages;

    std::string getFileName()
    {
    	 std::stringstream sstm;
    	 sstm << "segment." << segmentId << ".db";

    	 return sstm.str();
    }
};

#endif // SEGMENTINFORMATION_H
