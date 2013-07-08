#include "Projection.h"
#include "Register.h"
#include <iostream>

namespace Operator
{

Projection::Projection(Operator* in, std::vector<unsigned> attribute_ids)
{
	input = in;
	filter_attributes = attribute_ids;
}

Projection::~Projection()
{
	// TODO Auto-generated destructor stub
}

void Projection::open()
{
	input->open();
}

bool Projection::next()
{
	if ( !input->next() ) {
		return false;
	}
	output.clear();
	for ( int field : filter_attributes )
	{
		output.push_back(input->getOutput().at(field));
	}
	return true;
}

std::vector<Register*> Projection::getOutput()
{
	return output;
}

void Projection::close()
{
	input->close();
}

} /* namespace Operator */
