#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/GreetingProvider.cpp"
#include "../Project1/LoginPageProvider.cpp"
#include <regex>
#include <string>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Project1UnitTests {
	TEST_CLASS(Project1UnitTests) {
public:

	TEST_METHOD(TestMethod1) {
		GreetingProvider greetingProvider;
		std::string greeting = greetingProvider.getGretting();
		Assert::AreEqual(greeting, std::string("Hello"));
	}

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
	};
}