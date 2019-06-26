#include <string>
#include <arduino.h>
#include "utils.h"

std::string toStdStr(String s)
{
  const int str_len = s.length() + 1;
  char char_array[str_len];
  s.toCharArray(char_array, str_len);
  return std::string(char_array);
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
