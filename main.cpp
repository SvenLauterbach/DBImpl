#include "main_segments.h"
#include "Segments/segmentmanager.h"
#include "BufferManager/buffermanager.h"
#include "BTree/btree.h"
#include "BTree/btreenode.h"
#include "Segments/segmentinformation.h"
#include <iostream>
#include <map>

bool BufferManagerSimpleTest();
bool BTreeNodeSimpleTest();
bool SISegmentSimpleTest();

int main(int argc, char** argv)
{

	if(BufferManagerSimpleTest() == true)
	{
		std::cout << "[passed] - BufferManagerSimpleTest" << std::endl;
	}
	else
	{
		std::cout << "[failed] - BufferManagerSimpleTest" << std::endl;
	}

	if(BTreeNodeSimpleTest() == true)
	{
		std::cout << "[passed] - BTreeNodeSimpleTest" << std::endl;
	}
	else
	{
		std::cout << "[failed] - BTreeNodeSimpleTest" << std::endl;
	}

	/*

	Segmentation fault

	*/

	if(SISegmentSimpleTest() == true)
	{
		std::cout << "[passed] - SISegmentSimpleTest" << std::endl;
	}
	else
	{
		std::cout << "[failed] - SISegmentSimpleTest" << std::endl;
	}
}

bool SPSegmentSimpleTest()
{
	BufferManager bm("data.db", 1024);


}

bool BTreeNodeSimpleTest()
{
	BTreeNode<unsigned int, std::greater<unsigned int> > node;

	TID tid1(1, 2);
	TID tid2(2, 3);
	TID tid3(4, 5);

	node.add(1, tid1);
	node.add(2, tid2);
	node.add(3, tid3);

	TID tid_3 = node.find(3);
	TID tid_1 = node.find(1);
	TID tid_2 = node.find(2);

	if(tid1.getPageId() == tid_1.getPageId() &&
	   tid1.getSlotId() == tid_1.getSlotId() &&
	   tid2.getPageId() == tid_2.getPageId() &&
	   tid2.getSlotId() == tid_2.getSlotId() &&
	   tid3.getPageId() == tid_3.getPageId() &&
	   tid3.getSlotId() == tid_3.getSlotId())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool SISegmentSimpleTest()
{
	/*
	 * Lambda Expression for comparing 2 SegmentInformation objects
	 */
	auto f = [](SegmentInformation s1, SegmentInformation s2) -> bool
		         {
					return (s1.fileName.compare(s2.fileName) == 0 &&
						   s1.nrOfPages == s2.nrOfPages &&
						   s1.segmentId == s2.segmentId &&
						   s1.type == s2.type);
		         };


	BufferManager bm("data.db", 1024);

	BufferFrame& frame = bm.getPage(0, true);

	SISegment* sisegment = (SISegment*) frame.getData();

	if(sisegment->Size() > 0)
	{
		std::cout << sisegment->Size() << std::endl;
	}

	SegmentInformation id1 = sisegment->CreateSegment(SegmentType::BT, 1);
	SegmentInformation id2 = sisegment->CreateSegment(SegmentType::SP, 2);

	SegmentInformation segInfos1 = sisegment->GetSegment(id1.segmentId);
	SegmentInformation segInfos2 = sisegment->GetSegment(id2.segmentId);

	bm.unfixPage(frame, true);

	BufferFrame& frame_test = bm.getPage(0, true);

	SISegment* sisegment_test = static_cast<SISegment*>(frame_test.getData());

	SegmentInformation segInfos1_test = sisegment_test->GetSegment(segInfos1.segmentId);
	SegmentInformation segInfos2_test = sisegment_test->GetSegment(segInfos2.segmentId);

	bm.unfixPage(frame_test, false);

	if(f(segInfos1, segInfos1_test) &&
	   f(segInfos2, segInfos2_test))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BTreeSegmentSimpleTest()
{
	/*
	BufferManager bm("data.db", 1024);


	SegmentManager manager(bm);

	SegmentID btreesegmentid = manager.createSegment(SegmentType::BT, 1);

	BTreeSegment& segment = (BTreeSegment&)manager.getSegment(btreesegmentid);

	std::map<unsigned int, SegmentInformation> map;

	SegmentInformation* seg = new SegmentInformation(9, SegmentType::BT, "test", 1);
	SegmentInformation* seg2 = new SegmentInformation(10, SegmentType::SP, "Sven", 2);

	map.insert(std::make_pair(10, *seg));
	map.insert(std::make_pair(11, *seg2));

	BufferFrame& frame = bm.getPage(2, true);
	*/
	return false;
}

/*
 * Creates some random data, write it to a page, reopen the page and compare the
 * data from the page with the generated data
 */
bool BufferManagerSimpleTest()
{
	BufferManager bm("data.db", 1024);

	BufferFrame& frame = bm.getPage(1, true);

	int test[10];
	int data[10];
	bool writeback = false;

	//generate test data
	for(int i = 0; i <= 9; i++)
	{
		test[i] = i;
	}

	//write the data to the page
	memcpy(frame.getData(), &test, sizeof(test));
	bm.unfixPage(frame, true);


	//reopen page and load data from page
	BufferFrame& testFrame = bm.getPage(1, true);
	memcpy(&data, frame.getData(), sizeof(data));

	//compare data from testframe with generated test data
	int equal = memcmp(data, test, sizeof(test));

	if(equal == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
