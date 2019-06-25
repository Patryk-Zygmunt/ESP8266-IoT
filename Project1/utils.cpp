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