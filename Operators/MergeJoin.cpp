/*
 * MergeJoin.cpp
 *
 *  Created on: 15.07.2013
 *      Author: andi
 */

#include "MergeJoin.h"
#include <assert.h>

namespace Operator
{

MergeJoin::MergeJoin(Operator* inputLeft, Operator* inputRight,
		std::vector<unsigned> attributeIdsLeft,
		std::vector<unsigned> attributeIdsRight)
{
	input_left = inputLeft;
	input_right = inputRight;
	attribute_ids_left = attributeIdsLeft;
	attribute_ids_right = attributeIdsRight;
	assert(attribute_ids_left.size() == attribute_ids_right.size());

	not_done = true;
}

MergeJoin::~MergeJoin()
{
	// TODO Auto-generated destructor stub
}

void MergeJoin::open()
{
	input_left->open();
	not_done = input_left->next();
	input_right->open();
}

bool MergeJoin::next()
{

	// TODO: add n:m case
	unsigned i;
	bool all_equal;
	while ( not_done )
	{
		left_tuple = input_left->getOutput();
		while ( not_done )
		{
			right_tuple = input_right->getOutput();

			// check if join partners are all equal
			for ( i = 0; i < attribute_ids_left.size(); i++ ) {
				if ( !(right_tuple[attribute_ids_right[i]] == left_tuple[attribute_ids_left[i]]) ) {
					break;
				}
			}
			all_equal = (attribute_ids_left.size() == i);

			if (all_equal)
			{
				// TODO Optimization idea: only copy left if needed
				output_tuple.clear();
				// append left and right tuple to output
				output_tuple.insert(output_tuple.end(), left_tuple.begin(), left_tuple.end());
				output_tuple.insert(output_tuple.end(), right_tuple.begin(), right_tuple.end());
				not_done = input_right->next();
				return true;
			}
			else if ( right_tuple[attribute_ids_right[i]] < left_tuple[attribute_ids_left[i]] )
			{
				// right tuple is smaller then left tuple (input sorted)
				// skip this right tuple and compare next
				not_done = input_right->next();
			}
			else {
				// right tuple bigger then left tuple:
				// we need a new left tuple ;
				not_done = input_left->next();
				// to get the new left tuple we have to go out of the inner loop
				break;
			}
		}
	}
	return false;
}

/*
// compares left with right tuple (both member variables)
bool MergeJoin::cmp() {
	bool all_true = false;
	// iterate over all join attributes
	unsigned i = 0;
	do {
		// == calls operator==() of Register class
		all_true = (left_tuple[attribute_ids_left[i]] == right_tuple[attribute_ids_right[i]]);
		i++;
		// if condition returns false stop iterating over conditions
	} while ( all_true && i < attribute_ids_left.size() );
	return all_true;
}
*/

std::vector<Register*> MergeJoin::getOutput()
{
	return output_tuple;
}

void MergeJoin::close()
{
	input_left->open();
	input_left->next();
	input_right->open();
}

} /* namespace Operator */
