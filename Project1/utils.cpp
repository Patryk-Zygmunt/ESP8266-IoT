#include <string>
#include <arduino.h>
#include "utils.h"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

std::string toStdStr(String s)
{
    const int str_len = s.length() + 1;
    char char_array[str_len];
    s.toCharArray(char_array, str_len);
    return std::string(char_array);
}

std::chrono::system_clock::time_point timePointFromString(std::string timestamp, std::string format)
{
    struct tm tm;
    strptime(timestamp.c_str(), format.c_str(), &tm);
    time_t t = mktime(&tm);
    return std::chrono::system_clock::from_time_t(t);
}

std::string timePointToString(std::chrono::system_clock::time_point timePoint, std::string format) {
    std::time_t timePoint_c = std::chrono::system_clock::to_time_t(timePoint);
    std::tm timePoint_tm = *std::localtime(&timePoint_c);
    char s[50];
    strftime(s, 50, format.c_str(), &timePoint_tm);
    std::string timeAsString(s);
    return timeAsString;
}

void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
                return !std::isspace(ch);
            }));
}

void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
                return !std::isspace(ch);
            })
                .base(),
            s.end());
}

void trim(std::string &s)
{
    ltrim(s);
    rtrim(s);
}
