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
	virtual ~TableScan();

	virtual void open();
	virtual bool next();
	virtual std::vector<Register*> getOutput();
	virtual void close();

private:
	Schema::Relation& relation;
	SPSegment segment;
	std::vector<Register*> output;
	int currentPage;
	int currentSlot;
};

} /* namespace Operator */
#endif /* TABLESCAN_H_ */
