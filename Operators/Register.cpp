#include "Register.h"

namespace Operator
{

Register::Register()
{
	data = nullptr;
	type = register_type::undefined;
}

Register::~Register()
{
	// TODO Auto-generated destructor stub
}

int Register::getInteger()
{
	return  *(int *)data;
}

void Register::setInteger(int i)
{
	data = &i;
	type = register_type::Integer;
}

const std::string& Register::getString()
{
	return (std::string&)data;
}

void Register::setString(const std::string& s)
{
	data = (void*) &s;
	type = register_type::String;
}

bool Register::operator <(Register& other)
{
	if ( type != other.type )
		throw;
	switch (type) {
		case register_type::Integer:
			return getInteger() < other.getInteger();
		case register_type::String:
			return getString() < other.getString();
		default:
			throw;
	}
}

bool Register::operator ==(Register& other)
{
	if ( type != other.type )
		throw;
	switch (type) {
		case register_type::Integer:
			return getInteger() == other.getInteger();
		case register_type::String:
			return getString() == other.getString();
		default:
			throw;
	}
}

int Register::getHashValue()
{
	// TODO implement
}

} /* namespace Operator */
