#ifndef OPERATOR_H_
#define OPERATOR_H_

#include <vector>

namespace Operators
{

class Register;

class Operator
{
public:
	Operator();
	virtual ~Operator();

	virtual void open() = 0;
	virtual bool next() = 0;
	virtual std::vector<Register*> getOutput() = 0;
	virtual void close() = 0;
};

} /* namespace Operator */
#endif /* OPERATOR_H_ */
