#ifndef REGISTER_H_
#define REGISTER_H_

#include <string>

namespace Operators
{

enum class register_type { Integer, String };

class Register
{

public:
	Register();
	virtual ~Register();

	int getInteger() {
		return  *(int *)data;
	}
	void setInteger(int i) {
		data = &i;
	}

	const std::string& getString() {
		return (std::string&)data;
	}
	void setString(const std::string& s) {
		data = (void*) &s;
	}

	bool operator<(Register& other);
	bool operator==(Register& other);

	int getHashValue();

private:
	register_type type;
	void* data;
};

} /* namespace Operator */
#endif /* REGISTER_H_ */
