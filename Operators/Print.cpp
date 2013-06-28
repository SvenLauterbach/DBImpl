#include "Print.h"
#include "Register.h"
#include <iostream>

namespace Operator
{

Print::Print(Operator* in)
{
	input = in;
}

Print::~Print()
{
	// TODO Auto-generated destructor stub
}

void Print::open()
{
	input->open();
}

bool Print::next()
{
	if ( !input->next() ) {
		return false;
	}
	using std::cout;
	output = input->getOutput();
	for ( Register* reg : output )
	{
		switch ( reg->getType() ) {
			case RegisterType::Integer:
				cout << reg->getInteger();
				break;
			case RegisterType::String:
				cout << reg->getString();
				break;
			default:
				throw;
		}
		cout << "\t";
	}
	cout << std::endl;
	return true;
}

std::vector<Register*> Print::getOutput()
{
	return output;
}

void Print::close()
{
	input->close();
}

} /* namespace Operator */
