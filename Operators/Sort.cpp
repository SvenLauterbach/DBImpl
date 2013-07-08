/*
 * Sort.cpp
 *
 *  Created on: 08.07.2013
 *      Author: andi
 */

#include "Sort.h"

namespace Operator
{


Sort::Sort(Operator* in, std::vector<unsigned> attribute_ids, plan::Sort::Order sort_order)
{
	input = in;
	filter_attributes = attribute_ids;
	order = sort_order;
}

Sort::~Sort()
{
	// TODO Auto-generated destructor stub
}

void Sort::open()
{
	input->open();
	while(input->next())
	{
		// TODO irgendwo hin speichern und sortieren (vgl. Assignment 1)
		// Sortiertes Erebnis kommt nach storage
	}
	input->close();

}

bool Sort::next()
{
	storage.pop_back();
	return !storage.empty();
}

std::vector<Register*> Sort::getOutput()
{
	return storage.back();
}

void Sort::close()
{
}


} /* namespace Operator */
