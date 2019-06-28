#include <string>
#include <chrono>

std::string toStdStr(String s);

std::chrono::system_clock::time_point timePointFromString(std::string timestamp, std::string format = "%Y-%m-%dT%H:%M");

std::string timePointToString(std::chrono::system_clock::time_point timePoint, std::string format = "%Y-%m-%dT%H:%M");

void ltrim(std::string &s);

void rtrim(std::string &s);

void trim(std::string &s);