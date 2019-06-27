#include <string>
#include <chrono>

std::string toStdStr(String s);

std::chrono::system_clock::time_point timePointFromString(std::string timestamp, std::string format = "%b %d %Y %H:%M:%S");

std::string timePointToString(std::chrono::system_clock::time_point timePoint, std::string format = "%b %d %Y %H:%M:%S");

void ltrim(std::string &s);

void rtrim(std::string &s);

void trim(std::string &s);
