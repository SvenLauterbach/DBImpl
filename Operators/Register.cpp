#include "Register.h"

namespace Operator
{

Register::Register()
{
	data = nullptr;
	type = RegisterType::undefined;
}

Register::~Register()
{
	// TODO Auto-generated destructor stub
}

int Register::getInteger()
{
	return *(int *)data;
}

void Register::setInteger(int i)
{
	data = &i;
	type = RegisterType::Integer;
}

const std::string& Register::getString()
{
	return (std::string&)data;
}

void Register::setString(const std::string& s)
{
	data = (void*) &s;
	type = RegisterType::String;
}

bool Register::operator <(Register& other)
{
	if ( type != other.type )
		throw;
	switch (type) {
		case RegisterType::Integer:
			return getInteger() < other.getInteger();
		case RegisterType::String:
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
		case RegisterType::Integer:
			return getInteger() == other.getInteger();
		case RegisterType::String:
			return getString() == other.getString();
		default:
			throw;
	}
}

int Register::getHashValue()
{
	// TODO implement
	throw;
	return 0;
}

} /* namespace Operator */
