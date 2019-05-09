#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/GreetingProvider.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Project1UnitTests
{
	TEST_CLASS(Project1UnitTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			GreetingProvider greetingProvider;
			std::string greeting = greetingProvider.getGretting();
			Assert::AreEqual(greeting, std::string("Hello"));

		}
	};
}
