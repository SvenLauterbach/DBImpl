#ifndef REGISTER_H_
#define REGISTER_H_

#include <string>

namespace Operator
{

enum class RegisterType { undefined, Integer, String };

class Register
{

public:
	Register();
	virtual ~Register();

	int getInteger();
	void setInteger(int i);

	const std::string& getString();
	void setString(const std::string& s);

	bool operator<(Register& other);
	bool operator==(Register& other);

	int getHashValue();

	RegisterType getType() const
	{
		return type;
	}

private:
	RegisterType type;
	void* data;
};

} /* namespace Operator */
#endif /* REGISTER_H_ */
