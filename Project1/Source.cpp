#include <iostream>
#include "GreetingProvider.h"

int main(int argc, char** argv) {

	GreetingProvider jan;
	std::string greeting = jan.getGretting();
	std::cout << greeting;
}