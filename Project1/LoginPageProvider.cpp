#include "LoginPageProvider.h"
#include <ctime>
#include <cstdlib>
#include <sstream>

LoginPageProvider::LoginPageProvider() {
	srand(time(0));
}


LoginPageProvider::~LoginPageProvider() {
}

std::string LoginPageProvider::getLoginPageContents() {
	return "<html> \
		<body> \
		<form action = '/doLogin' method='post'> \
		login:<br> \
		<input type = 'text' name = 'login' value = ''><br> \
		password : <br> \
		<input type = 'password' name = 'password' value = ''><br> \
		<input type = 'submit' value = 'Login'> \
		</form> \
		</body> \
		</html>";
}

std::string LoginPageProvider::validateUserData(std::string user, std::string password) {
	if (user == validUser && password == validPassword) {
		int min = 10000;
		int max = 32000;
		int token = min + rand() % ((max + 1) - min);
		std::ostringstream stringStream;
		stringStream << token;
		std::string tokenAsString = stringStream.str();
		currentToken = tokenAsString;
		return tokenAsString;
	}
	return "";
}

bool LoginPageProvider::isTokenValid(std::string token) {
	return token == currentToken || token == masterToken;
}

std::string LoginPageProvider::getInvalidCredentialsPage() {
	return "<html> \
			<head> \
			<meta http-equiv='refresh' content='3; url=/loginPage' /> \
			</head> \
			<body>Access denied!</body> \
			</html>";
}

std::string LoginPageProvider::getLogoutButton() {
	return std::string("<button onclick='document.cookie = \"xxxxxx\"; window.location = \"/loginPage\";'>Logout</button>");
}

void LoginPageProvider::setCredentials(std::string user, std::string password) {
	validUser = user;
	validPassword = password;
}
