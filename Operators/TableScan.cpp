#include "TableScan.h"
#include "../Segments/SchemaSegment.h"
#include "../Parser/Schema.hpp"
#include "Register.h"

namespace Operators
{

TableScan::TableScan(std::string relation_name)
{
	SchemaSegment& schema = SchemaSegment::getInstance();
	// TODO? replace with reference?
	relation = schema.GetRelation(relation_name);
	currentPage = 0;
	currentSlot = 0;
}

TableScan::~TableScan()
{
	// TODO Auto-generated destructor stub
}

void TableScan::open()
{
	// initialize TID pointer to next element with page 0, slot 0
	currentPage = 0;
	currentSlot = 0;
	output.clear();
}

bool TableScan::next()
{
	// TODO implement comments
	// get record from segment and save to output variable
	SPSegment& segment = relation.getSegment();
	Record& record = segment.lookup(TID(currentPage, currentSlot));
	// if it fails as there are no more records:
	// return false
	output.clear();
	// maybe TODO: delete old registers?
	void* pointer = record.getData();
	for ( auto field : relation.attributes ) {
		Register* reg = new Register();
		switch( field.type ) {
		case Types::Tag::Integer: {
			int intValue = *((int *)pointer);
			reg->setInteger(intValue);
			break; }
		case Types::Tag::Char: {
			//std::string& string = new std::string((char*) pointer, field.len);
			std::string string((char*) pointer, field.len);
			reg->setString(string);
			// Keine Ahnung wie das hier mit der Speicherverwaltung genau lŠuft,
			// aber mich wŸrde es wundern wenn das wirklich funktioniert... --Andi
			break; }
		default:
			throw;
		}
		output.push_back(reg);

		pointer += field.len;
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
	output.clear();
	// maybe TODO delete registers?
}

} /* namespace Operator */
