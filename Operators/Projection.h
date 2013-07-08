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

	virtual void open();
	virtual bool next();
	virtual std::vector<Register*> getOutput();
	virtual void close();

private:
	Operator* input;
	std::vector<unsigned> filter_attributes;
	std::vector<Register*> output;
};

} /* namespace Operator */
#endif /* PROJECTION_H_ */
