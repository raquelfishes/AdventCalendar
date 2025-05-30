#include "utils_2022.h"

#include <iostream>
#include <sstream>
#include <fstream>

bool splitStringByChar(const std::string value, const char c, std::vector<std::string> &splited)
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

bool splitStringByString(const std::string &value, const std::string &deli, std::vector<std::string> &splited)
{
    splited.clear();
    int start = 0;
    int end = value.find(deli);
    while (end != -1)
    {
        splited.push_back(value.substr(start, end - start));
        start = end + deli.length();
        end = value.find(deli, start);
    }
    splited.push_back(value.substr(start, end - start));

    return true;
}

bool splitByRegex(const std::string line, const std::string expr, std::vector<std::string> &values)
{
    values.clear();
    return splitByRegex(line, std::regex(expr), values);
}

bool splitByRegex(const std::string line, const std::regex expr, std::vector<std::string> &values)
{
    values.clear();
    std::smatch smatch;
    if (std::regex_search(line, smatch, expr))
    {
        for (auto &sm : smatch)
        {
            values.push_back(sm);
        }
        return true;
    }
    return false;
}

bool matchRegex(const std::string line, const std::string expr)
{
    std::regex exp(expr);
    std::smatch smatch;
    if (std::regex_search(line, smatch, exp))
    {
        return true;
    }
    return false;
}

int char2int(const char c)
{
    return (c - '0');
}

char int2char(const int i)
{
    return '0' + i;
}

int charLowerCase2int(const char c)
{
    return (c - 'a');
}

int charUpperCase2int(const char c)
{
    return (c - 'A');
}

bool isUpperCase(const std::string &s)
{
    return std::all_of(s.begin(), s.end(), [](const char c)
                       { return std::isupper(c); });
    // return true;
}

bool isLowerCase(const std::string &s)
{
    return std::all_of(s.begin(), s.end(), [](const char c)
                       { return std::islower(c); });
    // return true;
}

bool isAllDigits(const std::string &s)
{
    return std::all_of(s.begin(), s.end(), [](const char c)
                       { return std::isdigit(c); });
    // return true;
}

bool isCharLowerCase(const char c)
{
    if ((c - 'a') >= 0 && (c - 'a') <= ('z' - 'a'))
        return true;
    return false;
}

bool isCharUpperCase(const char c)
{
    if ((c - 'A') >= 0 && (c - 'A') <= ('Z' - 'A'))
        return true;
    return false;
}
