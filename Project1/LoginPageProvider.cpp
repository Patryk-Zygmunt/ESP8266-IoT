#include "LoginPageProvider.h"
#include <ctime>
#include <cstdlib>


LoginPageProvider::LoginPageProvider() {
	srand(time(0));
}


LoginPageProvider::~LoginPageProvider() {
}

std::string LoginPageProvider::getLoginPageContents() {
	return "<html> \
		<body> \
		<form action = '/doLogin'> \
		login:<br> \
		<input type = 'text' name = 'login' value = ''><br> \
		password : <br> \
		<input type = 'password' name = 'password' value = ''><br> \
		<input type = 'submit' value = 'Login'> \
		< / form> \
		< / body> \
		< / html >";
}

std::string LoginPageProvider::validateUserData(std::string user, std::string password) {
	if (user == validUser && password == validPassword) {
		int min = 10000;
		int max = 32000;
		int token = min + rand() % ((max + 1) - min);
		std::string tokenAsString = std::to_string(token);
		currentToken = tokenAsString;
		return tokenAsString;
	}
	return "";
}

bool LoginPageProvider::isTokenValid(std::string token) {
	return token == currentToken;
}
