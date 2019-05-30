#include <string>
#pragma once
class LoginPageProvider {
public:
	std::string validUser = "user";
	std::string validPassword = "pass";
	std::string currentToken = "a231wda";

	LoginPageProvider();
	~LoginPageProvider();
	std::string getLoginPageContents();
	std::string validateUserData(std::string user, std::string password);
	bool isTokenValid(std::string token);
	std::string getInvalidCredentialsPage();
	std::string getLogoutButton();
};

