#include "main_segments.h"
#include "Segments/segmentmanager.h"
#include "BufferManager/buffermanager.h"

#include <iostream>

#include <map>

class test
{

public:
	test() : map() {}
	void insert() {
		SegmentInformation* seg = new SegmentInformation(0, SegmentType::BT, "", 1);
		map.insert(std::make_pair(9, *seg));
	}
private:
	std::map<unsigned int, SegmentInformation> map;
};


int main(int argc, char** argv)
{

	BufferManager bm("data.db", 1024);
	SegmentManager manager(bm);

	SegmentID btreesegmentid = manager.createSegment(SegmentType::BT, 1);

	BTreeSegment& segment = (BTreeSegment&)manager.getSegment(btreesegmentid);

	std::cout << "test";
}
