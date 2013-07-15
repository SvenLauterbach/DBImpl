#ifndef PROJECTION_H_
#define PROJECTION_H_

#include <vector>
#include "Operator.h"

namespace Operator
{
class Projection : public Operator::Operator
{
public:
	Projection(Operator* input, std::vector<unsigned> attribute_ids);
	virtual ~Projection();

	void open();
	bool next();
	std::vector<Register*> getOutput();
	void close();

private:
	Operator* input;
	std::vector<unsigned> filter_attributes;
	std::vector<Register*> output;
};

} /* namespace Operator */
#endif /* PROJECTION_H_ */
