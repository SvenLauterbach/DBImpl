#ifndef TABLESCAN_H_
#define TABLESCAN_H_

#include <string>
#include "Operator.h"
#include "../Parser/Schema.hpp"
#include "../Segments/SPSegment/spsegment.h"


namespace Operator
{

class Register;

class TableScan: public Operator
{
public:
	TableScan(SPSegment& segment, Schema::Relation relation);
	~TableScan();

	void open();
	bool next();
	std::vector<Register*> getOutput();
	void close();

private:
	Schema::Relation& relation;
	SPSegment segment;
	std::vector<Register*> output;
	int currentPage;
	int currentSlot;
};

} /* namespace Operator */
#endif /* TABLESCAN_H_ */
