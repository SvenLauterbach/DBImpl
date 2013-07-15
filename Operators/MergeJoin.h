/*
 * MergeJoin.h
 *
 *  Created on: 15.07.2013
 *      Author: andi
 */

#ifndef MERGEJOIN_H_
#define MERGEJOIN_H_

#include "Operator.h"

namespace Operator
{

class MergeJoin: public Operator::Operator
{
public:
	MergeJoin(Operator* inputLeft, Operator* inputRight,
		std::vector<unsigned> attributeIdsLeft,
		std::vector<unsigned> attributeIdsRight
	);
	virtual ~MergeJoin();

	void open();
	bool next();
	std::vector<Register*> getOutput();
	void close();

private:
	bool cmp();

	Operator* input_left;
	std::vector<unsigned> attribute_ids_left;
	Operator* input_right;
	std::vector<unsigned> attribute_ids_right;
	std::vector<Register*> left_tuple;
	std::vector<Register*> right_tuple;
	std::vector<Register*> output_tuple;

	bool not_done;
};

} /* namespace Operator */
#endif /* MERGEJOIN_H_ */
