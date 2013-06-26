#include "TableScan.h"

namespace Operators
{

TableScan::TableScan(std::string relation_name)
{
	SchemaSegment schema = SchemaSegment::getInstance();
	// TODO? replace with reference?
	relation = schema.GetRelation(relation_name)

}

TableScan::~TableScan()
{
	// TODO Auto-generated destructor stub
}

void TableScan::open()
{
	// initialize TID pointer to next element with page 0, slot 0
	current = TID(0,0);


}

bool TableScan::next()
{
	// get record from segment and save to output variable
	relation.
	// if it fails as there are no more records: return false
	//output =
	// increment pointer
	return true;
}

std::vector<Register*> TableScan::getOutput()
{
	return output;
}

void TableScan::close()
{
}

} /* namespace Operator */
