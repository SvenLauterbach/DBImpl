/*
 * Print.h
 *
 *  Created on: 27.06.2013
 *      Author: andi
 */

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
	virtual ~Print();

	virtual void open();
	virtual bool next();
	virtual std::vector<Register*> getOutput();
	virtual void close();

private:
	Operator* input;
	std::vector<Register*> output;
};

} /* namespace Operator */
#endif /* PRINT_H_ */
