#ifndef PRINT_H_
#define PRINT_H_

#include <vector>
#include "Operator.h"

namespace Operator
{
class Register;

class Print: public Operator::Operator
{
public:
	Print(Operator* input);
	~Print();

	void open();
	bool next();
	std::vector<Register*> getOutput();
	void close();

private:
	Operator* input;
	std::vector<Register*> output;
};

} /* namespace Operator */
#endif /* PRINT_H_ */
