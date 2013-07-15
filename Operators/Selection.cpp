/*
 * Selection.cpp
 *
 *  Created on: 09.07.2013
 *      Author: andi
 */

#include "Selection.h"
#include <assert.h>

namespace Operator
{

Selection::Selection(Operator* in, std::vector<unsigned> _attribute_ids, std::vector<Register*> _constants)
{
	input = in;
	attribute_ids = _attribute_ids;
	constants = _constants;
	assert(attribute_ids.size() == constants.size());
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
	bool all_true = false;
	// repeat until we find an tuple which all conditions fit
	while (!all_true && input->next() )
	{
		tuple = input->getOutput();
		// compare current tuple with constants
		all_true = cmp();
	}
	return all_true;
}

bool Selection::cmp() {
	bool all_true = false;
	// iterate over conditions
	unsigned i = 0;
	do {
		// == calls operator==() of Register class
		all_true = (tuple[attribute_ids[i]] == constants[i]);
		i++;
		// if condition returns false stop iterating over conditions
	} while ( all_true && i < attribute_ids.size() );
	return all_true;
}

std::vector<Register*> Selection::getOutput()
{
	return tuple;
}

void Selection::close()
{
	input->close();
}

} /* namespace Operator */
