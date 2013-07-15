/*
 * Selection.cpp
 *
 *  Created on: 09.07.2013
 *      Author: andi
 */

#include "Selection.h"

namespace Operator
{

Selection::Selection(Operator* in, std::vector<unsigned> _attribute_ids, std::vector<Register*> _constants)
{
	input = in;
	attribute_ids = _attribute_ids;
	constants = _constants;
	std::vector<Register*> output;
}

Selection::~Selection()
{
	// TODO Auto-generated destructor stub
}

void Selection::open()
{
	input->open();
}

bool Selection::next()
{
}

std::vector<Register*> Selection::getOutput()
{
}

void Selection::close()
{
}

} /* namespace Operator */
