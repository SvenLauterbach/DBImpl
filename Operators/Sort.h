#ifndef SORT_H_
#define SORT_H_

#include "Operator.h"
#include  "../PlanReader/Plan.hpp"

namespace Operator
{

class Sort : public Operator::Operator
{
public:
	Sort(Operator* input, std::vector<unsigned> attribute_ids, plan::Sort::Order sort_order);
	~Sort();

	void open();
	bool next();
	std::vector<Register*> getOutput();
	void close();

private:
	Operator* input;
	std::vector<unsigned> filter_attributes;
	plan::Sort::Order order;
	std::vector<std::vector<Register*>> storage;

};

} /* namespace Operator */
#endif /* SORT_H_ */
