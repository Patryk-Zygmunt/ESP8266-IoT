#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/GreetingProvider.cpp"
#include "../Project1/PinStateMock.cpp"
#include "../Project1/IPinState.cpp"


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

		TEST_METHOD(PinStateMockConstructor)
		{
			PinStateMock pinState = PinStateMock();
			int pinIn = pinState.getInPinState(0);
			int pinOut = pinState.getOutPinState(8);
			Assert::AreEqual(pinIn, 0);
			Assert::AreEqual(pinOut, 0);

		}

		TEST_METHOD(PinStateMockSetInPinState)
		{
			PinStateMock pinState = PinStateMock();
			pinState.setInPinState(0, 1);
			int pin0 = pinState.getInPinState(0);
			Assert::AreEqual(pin0, 1);

		}

		TEST_METHOD(PinStateMockSetOutPinState)
		{
			PinStateMock pinState = PinStateMock();
			pinState.setOutPinState(0, 1);
			int pin0 = pinState.getOutPinState(0);
			Assert::AreEqual(pin0, 1);

		}

		TEST_METHOD(PinStateMockSetAllInPinState)
		{
			PinStateMock pinState = PinStateMock();
			pinState.setAllInPins(1);
			int pin = 0;
			for (int i = 0; i < pinState.PIN_IN_AMOUNT; i++) {
				pin = pinState.getInPinState(i);
				Assert::AreEqual(pin, 1);
			}

		}

		TEST_METHOD(PinStateMockSetAllOutPinsState)
		{
			PinStateMock pinState = PinStateMock();
			pinState.setAllOutPins(1);
			int pin = 0;
			for (int i = 0; i < pinState.PIN_OUT_AMOUNT; i++) {
				pin = pinState.getOutPinState(i);
				Assert::AreEqual(pin, 1);
			}
		}



	};
}
