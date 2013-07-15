#include "TableScan.h"
#include "../Segments/SchemaSegment.h"
#include "../Parser/Schema.hpp"
#include "Register.h"

namespace Operator
{

// TODO why is the relation parameter not a reference
TableScan::TableScan(SPSegment& segment, Schema::Relation relation) : relation(relation), segment(segment)
{
	currentPage = 0;
	currentSlot = 0;

	for ( auto field : relation.attributes ) {
		output.push_back(new Register());
	}
}

TableScan::~TableScan()
{
	for ( Register* r : output ) {
		delete r;
	}
}

void TableScan::open()
{
	// initialize TID pointer to next element with page 0, slot 0
	currentPage = 0;
	currentSlot = 0;
}

bool TableScan::next()
{
	// TODO implement comments
	// get record from segment and save to output variable
	const Record& record = segment.lookup(TID(currentPage, currentSlot));
	// if it fails as there are no more records:
	// return false
	// maybe TODO: delete old registers?
	const void* pointer = record.getData();
	int i = 0;

	// TODO: change form pointer+=field.len to pointer+offset
	//		 to handle size grouped order
	for ( auto field : relation.attributes )
	{
		switch( field.type ) {
		case Types::Tag::Integer: {
			int intValue = *((int *)pointer);
			output[i]->setInteger(intValue);
			break; }
		case Types::Tag::Char: {
			//std::string& string = new std::string((char*) pointer, field.len);
			std::string string((char*) pointer, field.len);
			output[i]->setString(string);
			break; }
		default:
			throw;
		}

		// TODO how to disable this warning? --Andi
		pointer += field.len;
		i++;
	}
	// increment slot and page
	currentSlot++;
	// TODO wenn currentSlot >= segment.pages[currentPage].header.slotCount
	if ( false ) {
		currentPage++; // TODO sind die pages eines Segments fortlaufend?
		currentSlot = 0;
	}
	return true;
}

std::vector<Register*> TableScan::getOutput()
{
	return output;
}

void TableScan::close()
{
	// maybe TODO delete registers?
}

} /* namespace Operator */
