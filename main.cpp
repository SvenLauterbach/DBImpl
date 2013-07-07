#include "main_segments.h"
#include "Segments/segmentmanager.h"
#include "BufferManager/buffermanager.h"
#include "BTree/btree.h"
#include "BTree/btreenode.h"
#include "Segments/segmentinformation.h"
#include "Segments/SchemaSegment.h"
#include "Parser/Parser.hpp"
#include <iostream>
#include <map>

bool BufferManagerSimpleTest();
bool BTreeNodeSimpleTest();
bool SISegmentSimpleTest();
bool test();
bool BufferManagerPageNotFoundTest();
bool CreateSlotReferenceTest();
bool test2();

int main(int argc, char** argv)
{
	/*
	BufferManager bm("/tmp/db", 8096);
	SegmentManager* sm = new SegmentManager(bm);

	SPSegment& segment = static_cast<SPSegment&>(sm->getSegment(52));

	segment.Dump(TID(3,3));
	*/

	main_segments(PAGE_SIZE);

	if(CreateSlotReferenceTest() == true)
	{
		std::cout << "[passed] - CreateSlotReferenceTests" << std::endl;
	}
	else
	{
		std::cout << "[failed] - CreateSlotReferenceTest" << std::endl;
	}

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

	if(SISegmentSimpleTest() == true)
	{
		std::cout << "[passed] - SISegmentSimpleTest" << std::endl;
	}
	else
	{
		std::cout << "[failed] - SISegmentSimpleTest" << std::endl;
	}

	if(BufferManagerPageNotFoundTest())
	{
		std::cout << "[passed] - BufferManagerPageNotFoundTest" << std::endl;
	}
	else
	{
		std::cout << "[failed] - BufferManagerPageNotFoundTest" << std::endl;
	}
}

bool test2()
{
	int i = 0;
	BufferManager bm("/tmp/db", 10ul*1024ul*1024ul);
	SegmentManager* manager = new SegmentManager(bm);

	SPSegment& sp = static_cast<SPSegment&>(manager->getSegment(45));

	for(SPSegment::iterator it = sp.begin(); it != sp.end(); ++it)
	{
		i++;
		TID tid = (*it);
		const Record& record = sp.lookup(tid);
		std::string text(record.getData(), record.getLen());
		std::cout << tid.getPageId() << ", " << tid.getSlotId() << ": " << record.getLen() << " - " << text << std::endl;
	}

	std::cout << i;
}

bool CreateSlotReferenceTest()
{
	bool result1 = false;
	bool result2 = false;

	SlottedPageSlot slot;

	TID tid(42,32);
	slot.createTIDReferenceSlot(tid);

	TID tidtest = slot.isSlotReference();

	if(tidtest != TID::NULLTID() && tid == tidtest)
	{
		result1 = true;
	}
	else
	{
		result1 = false;
	}


	SlottedPageSlot slot2;

	slot2.isFree = false;
	slot2.length = 22;
	slot2.offset = 787; //&slot;

	TID tidtest2 = slot2.isSlotReference();

	if(tidtest2 == TID::NULLTID())
	{
		result2 = true;
	}
	else
	{
		result2 = false;
	}

	return result1 && result2;
}

bool BufferManagerPageNotFoundTest()
{
	BufferManager bm("data.db", 1024);

	BufferFrame& frame = bm.getPage(1213213123, bm.getMasterFile(), true);

	if(BufferFrame::IsInvalidFrame(frame))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool test()
{
	BufferManager bm("data.db", 1024);

	std::vector<int> ints;

	for(int i = 0; i < 100; i++)
	{
		ints.push_back(i);
	}

	BufferFrame& frame = bm.getPage(3, bm.getMasterFile(), true);

	//(*(frame.getData())) = ints;
	memcpy(&ints, frame.getData(), sizeof(ints));

	bm.unfixPage(frame, true);

	BufferFrame& frame_test = bm.getPage(3, bm.getMasterFile(), true);

	std::vector<int> ints_test;

	memcpy(frame.getData(), &ints_test, sizeof(ints));
	//ints_test = (*(frame.getData()));

	for(int i = 0; i < 100; i++)
	{
		if(ints.at(i) != ints_test.at(i))
		{
			return false;
		}
	}

	return true;
}

bool SchemaSegmentSimpleTest()
{
	BufferManager bm("data.db", 1024);

	/*
	SchemaSegment segment;

	Parser p("");


	std::unique_ptr<Schema> schema = p.parse();

	for(auto relation : schema->relations)
	{
		//segment.AddRelation(relation);
	}
	*/
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
					return (s1.getFileName().compare(s2.getFileName()) == 0 &&
						   s1.nrOfPages == s2.nrOfPages &&
						   s1.segmentId == s2.segmentId &&
						   s1.type == s2.type);
		         };


	BufferManager bm("data.db", 1024);

	BufferFrame& frame = bm.getPage(0, bm.getMasterFile(), true);

	SISegment* sisegment = (SISegment*) frame.getData();

	SegmentInformation id1 = sisegment->CreateSegment(SegmentType::BT, 1);
	SegmentInformation id2 = sisegment->CreateSegment(SegmentType::SP, 2);

	SegmentInformation segInfos1 = sisegment->GetSegment(id1.segmentId);
	SegmentInformation segInfos2 = sisegment->GetSegment(id2.segmentId);

	bm.unfixPage(frame, true);

	BufferFrame& frame_test = bm.getPage(0, bm.getMasterFile(), true);

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

	BufferFrame& frame = bm.getPage(0, bm.getMasterFile(), true);

	if(BufferFrame::IsInvalidFrame(frame))
	{
		return false;
	}

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
	BufferFrame& testFrame = bm.getPage(0, bm.getMasterFile(), true);

	if(BufferFrame::IsInvalidFrame(testFrame))
	{
		return false;
	}
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
