#include "utils.h"

#include <iostream>
#include <sstream>
#include <fstream>


 


bool splitString(const std::string value, const char c, std::vector<std::string>& splited)
{
  splited.clear();
  std::stringstream ssRange(value);
  std::string splitValue;
  while (getline(ssRange, splitValue, c))
  {
    splited.push_back(splitValue);
  }

  return true;
}

bool splitByRegex(const std::string line, const std::regex expr, std::vector<std::string>& values)
{
  std::smatch smatch;
  if (std::regex_search(line, smatch, expr))
  {
    for (auto& sm : smatch)
    {
      values.push_back(sm);
    }
    return true;
  }
  return false;
}
