#include "LoginPageProvider.h"
#include <ctime>
#include <cstdlib>


LoginPageProvider::LoginPageProvider() {
	srand(time(0));
}


LoginPageProvider::~LoginPageProvider() {
}

std::string LoginPageProvider::getLoginPageContents() {
	return "";
}

std::string LoginPageProvider::validateUserData(std::string user, std::string password) {
	return "";
}

bool LoginPageProvider::isTokenValid(std::string token) {
	return false;
}
