/*
 * SchemaSegment.h
 *
 *  Created on: Jun 24, 2013
 *      Author: sven
 */

#ifndef SCHEMASEGMENT_H_
#define SCHEMASEGMENT_H_

#include <string>
#include "../Parser/Schema.hpp"
#include "../Parser/Types.hpp"
#include "../Segments/tid.h"
#include "../Segments/record.hpp"
#include "../Segments/SPSegment/spsegment.h"
#include "segmentinformation.h"
#include "../BufferManager/buffermanager.h"

class SchemaSegment : public SPSegment {
public:
	SchemaSegment(SegmentInformation info, BufferManager& bm);
	virtual ~SchemaSegment();

	// TODO: change first char to lower case
	void AddRelation(Schema::Relation r);
	Schema::Relation GetRelation(std::string& name);
	void DeleteRelation(Schema::Relation r);
	void UpdateRelation(Schema::Relation r);

	void getIndexes(Schema::Relation R);

	Types::Tag getType(std::string& name, std::string& relationname);
	void* getAttribute(TID tid, std::string& attribute);

};

#endif /* SCHEMASEGMENT_H_ */
