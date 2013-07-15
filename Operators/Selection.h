#ifndef SELECTION_H_
#define SELECTION_H_

#include "Operator.h"

namespace Operator
{

class Selection : public Operator::Operator
{
public:
	Selection(Operator* input, std::vector<unsigned> attribute_ids, std::vector<Register*> constants);
	virtual ~Selection();

	void open();
	bool next();
	std::vector<Register*> getOutput();
	void close();
private:
	Operator* input;
	std::vector<unsigned> attribute_ids;
	std::vector<Register*> constants;
	std::vector<Register*> tuple;
};

} /* namespace Operator */
#endif /* SELECTION_H_ */
