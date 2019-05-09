#include <string>

#ifndef GREETING
#define GREETING

class GreetingProvider {
public:
	GreetingProvider();
	~GreetingProvider();
	std::string getGretting();
};

#endif

