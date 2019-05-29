#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/GreetingProvider.cpp"
#include "../Project1/Alarm.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Project1UnitTests
{
	TEST_CLASS(Project1UnitTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{

			Alarm alarm; 
			int sensorState = 0;
			int alarmState = 0;
			
			alarmState = alarm.setAlarm(sensorState);
			Assert::AreEqual(alarmState, 0);

			sensorState = 1;

			alarmState = alarm.setAlarm(sensorState);
			Assert::AreEqual(alarmState, 1);
			
			// GreetingProvider greetingProvider;
			// std::string greeting = greetingProvider.getGretting();
			// Assert::AreEqual(greeting, std::string("Hello"));

		}
	};
}
