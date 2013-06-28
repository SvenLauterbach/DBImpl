#ifndef TABLESCAN_H_
#define TABLESCAN_H_

#include <string>
#include "Operator.h"
#include "../Parser/Schema.hpp"


namespace Operator
{

class Register;

class TableScan: public Operator
{
public:
	TableScan(std::string relation);
	virtual ~TableScan();

	virtual void open();
	virtual bool next();
	virtual std::vector<Register*> getOutput();
	virtual void close();

private:
	Schema::Relation& relation;
	std::vector<Register*> output;
	int currentPage;
	int currentSlot;
};

} /* namespace Operator */
#endif /* TABLESCAN_H_ */
