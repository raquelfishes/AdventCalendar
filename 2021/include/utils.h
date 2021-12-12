#pragma once


#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>


bool splitString(const std::string value, const char c, std::vector<std::string>& splited );


bool splitByRegex(const std::string line, const std::regex regex, std::vector<std::string>& values);

template<typename T>
bool readDocument(const std::string path, std::vector<T>& values)
{
  // Open numbers file
  std::ifstream myfile(path);
  if (!myfile.is_open())
  {
    fprintf(stderr, "readDocument: Error, no file founded %s\n", path.c_str());
    return false;
  }

  std::string line;
  while (getline(myfile, line))
  {
    values.push_back(T(line));
  }
}

int char2int(const char c);

bool isUppercase(const std::string& s);
bool isLowercase(const std::string& s);