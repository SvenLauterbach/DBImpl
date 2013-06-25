#ifndef TABLESCAN_H_
#define TABLESCAN_H_

#include "Operator.h"
#include <string>

namespace Operators
{

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
	std::vector<Register*> output;

};

} /* namespace Operator */
#endif /* TABLESCAN_H_ */
