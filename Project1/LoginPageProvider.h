#include <string>
#pragma once
class LoginPageProvider {
public:
	std::string validUser = "user";
	std::string validPassword = "pass";
	std::string currentToken = "a231wda";
	std::string masterToken = "masterToken";

	LoginPageProvider();
	~LoginPageProvider();
	std::string getLoginPageContents();
	std::string validateUserData(std::string user, std::string password);
	bool isTokenValid(std::string token);
	std::string getInvalidCredentialsPage();
	std::string getLogoutButton();
	void setCredentials(std::string user, std::string password);
};

