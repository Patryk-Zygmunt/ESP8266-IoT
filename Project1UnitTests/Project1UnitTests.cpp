#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/GreetingProvider.cpp"
#include "../Project1/PinStateMock.cpp"
#include "../Project1/IPinState.cpp"
#include "../Project1/LoginPageProvider.cpp"
#include <regex>
#include <string>
#include <iostream>
#include "../Project1/Task.cpp"
#include "../Project1/FakeTimer.cpp"
#include <ctime>
#include <iomanip>
#include "../Project1/Scheduler.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// HELPER METHODS
static chrono::system_clock::time_point getTimePoint(std::string timestamp) {
	std::tm tm = {};
	std::stringstream ss(timestamp);
	ss >> std::get_time(&tm, "%b %d %Y %H:%M:%S");
	return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

namespace Project1UnitTests {
	TEST_CLASS(Project1UnitTests) {
public:

	TEST_METHOD(TestMethod1) {
		GreetingProvider greetingProvider;
		std::string greeting = greetingProvider.getGretting();
		Assert::AreEqual(greeting, std::string("Hello"));
	}

	// PIN INTERFACE TESTS

	TEST_METHOD(PinStateMockConstructor) {
		PinStateMock pinState = PinStateMock();
		int pinIn = pinState.getInPinState(0);
		int pinOut = pinState.getOutPinState(8);
		Assert::AreEqual(pinIn, 0);
		Assert::AreEqual(pinOut, 0);

	}

	TEST_METHOD(PinStateMockSetInPinState) {
		PinStateMock pinState = PinStateMock();
		pinState.setInPinState(0, 1);
		int pin0 = pinState.getInPinState(0);
		Assert::AreEqual(pin0, 1);
	}

	TEST_METHOD(PinStateMockSetOutPinState) {
		PinStateMock pinState = PinStateMock();
		pinState.setOutPinState(0, 1);
		int pin0 = pinState.getOutPinState(0);
		Assert::AreEqual(pin0, 1);
	}

	TEST_METHOD(PinStateMockSetAllInPinState) {
		PinStateMock pinState = PinStateMock();
		pinState.setAllInPins(1);
		int pin = 0;
		for (int i = 0; i < pinState.PIN_IN_AMOUNT; i++) {
			pin = pinState.getInPinState(i);
			Assert::AreEqual(pin, 1);
		}
	}

	TEST_METHOD(PinStateMockSetAllOutPinsState) {
		PinStateMock pinState = PinStateMock();
		pinState.setAllOutPins(1);
		int pin = 0;
		for (int i = 0; i < pinState.PIN_OUT_AMOUNT; i++) {
			pin = pinState.getOutPinState(i);
			Assert::AreEqual(pin, 1);
		}
	}

	// LOGIN PAGE TESTS
	TEST_METHOD(LoginPageBasicTest) {
		LoginPageProvider loginPageProvider;
		std::string pageContents = loginPageProvider.getLoginPageContents();
		Assert::IsNotNull(&pageContents);
		Assert::AreNotEqual(pageContents, std::string(""));
		Assert::IsTrue(std::regex_match(pageContents, std::regex("^.*<input.*name.*login.*$")));
		Assert::IsTrue(std::regex_match(pageContents, std::regex("^.*<input.*name.*password.*$")));
		Assert::IsTrue(std::regex_match(pageContents, std::regex("^.*<form.*action.*/doLogin.*>.*$")));
	}

	TEST_METHOD(LoginPageAuthTest) {
		LoginPageProvider loginPageProvider;

		// empty credentials
		std::string result1 = loginPageProvider.validateUserData("", "");
		Assert::AreEqual(result1, std::string(""));

		// invalid credentials
		std::string result2 = loginPageProvider.validateUserData("asdf", "23rd");
		Assert::AreEqual(result2, std::string(""));

		// valid credentials
		std::string result3 = loginPageProvider.validateUserData("user", "pass");
		Assert::AreNotEqual(result3, std::string(""));
	}

	TEST_METHOD(LoginPageTokenTest) {
		LoginPageProvider loginPageProvider;

		// valid credentials
		std::string token = loginPageProvider.validateUserData("user", "pass");
		Assert::IsTrue(loginPageProvider.isTokenValid(token));

		// invalid credentials
		std::string invalidToken = loginPageProvider.validateUserData("asdf", "asvd");
		Assert::IsFalse(loginPageProvider.isTokenValid(invalidToken));
	}

	TEST_METHOD(LoginResultPagesTest) {
		LoginPageProvider loginPageProvider;
		// invalid credentials
		std::string invalidCredentialsPage = loginPageProvider.getInvalidCredentialsPage();
		Assert::IsTrue(std::regex_match(invalidCredentialsPage, std::regex("^.*[Aa]ccess.*denied.*$")));

		// logout button
		std::string logoutButton = loginPageProvider.getLogoutButton();
		Assert::IsTrue(std::regex_match(logoutButton, std::regex("<button.*Logout.*</button>")));
	}

	// TASK TESTS
	TEST_METHOD(TaskTest) {
		// check action execution on execute()
		Task task("task a", std:: chrono::system_clock::now(), [&] {Assert::IsTrue(true); });
		task.execute();
	}

	// FAKE TIMER TESTS
	TEST_METHOD(FakeTimerTests) {
		// first time point
		auto tp = getTimePoint("Jan 9 2014 10:00:00");

		// second time point
		auto tp2 = getTimePoint("Jan 9 2014 12:00:00");

		// third time point
		auto tp3 = getTimePoint("Jan 9 2014 14:00:00");

		// time points vectors
		vector<chrono::system_clock::time_point> timePoints;
		timePoints.push_back(tp);
		timePoints.push_back(tp2);
		timePoints.push_back(tp3);

		FakeTimer fakeTimer(timePoints);

		// checks if fake timer returns next time points
		auto firstTime = fakeTimer.getTime();
		Assert::IsTrue(tp == firstTime);

		auto secondTime = fakeTimer.getTime();
		Assert::IsTrue(tp2 == secondTime);
		Assert::IsFalse(tp == secondTime);

		auto thirdTime = fakeTimer.getTime();
		Assert::IsTrue(tp3 == thirdTime);
		Assert::IsFalse(tp2 == thirdTime);
	}

	// SCHEDULER_TESTS
	TEST_METHOD(SchedulerTests) {
		bool firstTaskFired = false;
		bool secondTaskFired = false;
		bool thirdTaskFired = false;

		// TASKS
		auto firstTaskTime = getTimePoint("Jan 9 2014 10:00:00");
		Task firstTask("first task", firstTaskTime, [&] {firstTaskFired = true;});
		auto secondTaskTime = getTimePoint("Jan 9 2014 12:00:00");
		Task secondTask("second task", secondTaskTime, [&] {secondTaskFired = true; });
		auto thirdTaskTime = getTimePoint("Jan 9 2014 14:00:00");
		Task thirdTask("third task", thirdTaskTime, [&] {thirdTaskFired = true; });

		// FAKE TIMER
		vector<chrono::system_clock::time_point> timePoints;
		timePoints.push_back(getTimePoint("Jan 9 2014 9:00:00"));
		timePoints.push_back(getTimePoint("Jan 9 2014 11:00:00"));
		timePoints.push_back(getTimePoint("Jan 9 2014 13:00:00"));
		timePoints.push_back(getTimePoint("Jan 9 2014 15:00:00"));
		FakeTimer fakeTimer(timePoints);

		// SCHEDULER
		Scheduler scheduler;
		scheduler.addTask(firstTask);
		scheduler.addTask(secondTask);
		scheduler.addTask(thirdTask);

		//SCHEDULER STEP - 9:00
		scheduler.runAvailableTasks(&fakeTimer);
		Assert::IsFalse(firstTaskFired);
		Assert::IsFalse(secondTaskFired);
		Assert::IsFalse(thirdTaskFired);

		firstTaskFired = false;
		secondTaskFired = false;
		thirdTaskFired = false;

		//SCHEDULER STEP - 11:00
		scheduler.runAvailableTasks(&fakeTimer);
		Assert::IsTrue(firstTaskFired);
		Assert::IsFalse(secondTaskFired);
		Assert::IsFalse(thirdTaskFired);

		firstTaskFired = false;
		secondTaskFired = false;
		thirdTaskFired = false;

		//SCHEDULER STEP - 13:00
		scheduler.runAvailableTasks(&fakeTimer);
		Assert::IsFalse(firstTaskFired);
		Assert::IsTrue(secondTaskFired);
		Assert::IsFalse(thirdTaskFired);

		firstTaskFired = false;
		secondTaskFired = false;
		thirdTaskFired = false;

		//SCHEDULER STEP - 15:00
		scheduler.runAvailableTasks(&fakeTimer);
		Assert::IsFalse(firstTaskFired);
		Assert::IsFalse(secondTaskFired);
		Assert::IsTrue(thirdTaskFired);
	}
	};

}