/*
 * SchemaSegment.cpp
 *
 *  Created on: Jun 24, 2013
 *      Author: sven
 */

#include "SchemaSegment.h"

SchemaSegment::SchemaSegment(SegmentInformation info, BufferManager& bm) : SPSegment(info, bm) {
	// TODO Auto-generated constructor stub

}

SchemaSegment::~SchemaSegment() {
	// TODO Auto-generated destructor stub
}

void SchemaSegment::AddRelation(Schema::Relation r)
{
	Record record(sizeof(r), (char*)&r);
	this->insert(record);
}

Schema::Relation SchemaSegment::GetRelation(std::string& name)
{
}

void SchemaSegment::DeleteRelation(Schema::Relation r)
{
}

void SchemaSegment::UpdateRelation(Schema::Relation r)
{
}

void SchemaSegment::getIndexes(Schema::Relation R)
{
}

Types::Tag SchemaSegment::getType(std::string& name, std::string& relationname)
{
}

void* SchemaSegment::getAttribute(TID tid, std::string& attribute)
{
}
