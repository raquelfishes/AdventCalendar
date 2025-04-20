#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <regex>
#include <numeric>
#include <limits>

#include "resources.h"

long long evaluate(std::string &operation);  // forward declaration
long long evaluate2(std::string &operation); // forward declaration

void popTerm(std::string &operation)
{
    operation.erase(operation.begin(), operation.begin() + 1);
}

long long getTerm(std::string &operation, const bool part2 = false)
{
    long long result = 0;
    if (isdigit(operation.front()))
    {
        result = operation[0] - '0';
        popTerm(operation);
    }
    else if (operation.front() == '(')
    {
        // '('
        popTerm(operation);
        if (part2)
        {
            result = evaluate2(operation);
        }
        else
        {
            result = evaluate(operation);
        }
        // ')'
        popTerm(operation);
    }
    return result;
}

long long evaluate(std::string &operation)
{
    long long result = getTerm(operation);
    while ((!operation.empty()) && (operation.front() == '+' || operation.front() == '*'))
    {
        if (operation.front() == '+')
        {
            popTerm(operation);
            result += getTerm(operation);
        }
        else if (operation.front() == '*')
        {
            popTerm(operation);
            result *= getTerm(operation);
        }
    }
    return result;
}

long long evaluate2(std::string &operation)
{
    long long result = getTerm(operation, true);
    while ((!operation.empty()) && (operation.front() == '+' || operation.front() == '*'))
    {
        if (operation.front() == '+')
        {
            popTerm(operation);
            result += getTerm(operation, true);
        }
        else if (operation.front() == '*')
        {
            popTerm(operation);
            result *= evaluate2(operation);
        }
    }
    return result;
}

void adventDay18()
{
    std::string resourcePath = getResourcePath(2020, 18);
    // Open numbers file
    std::ifstream myfile(resourcePath);
    if (!myfile.is_open())
    {
        std::cout << "Error, no file found" << std::endl;
        return;
    }

    std::vector<std::string> operations;
    std::string line;
    int countX = 0;
    while (getline(myfile, line))
    {
        // Remove whitespace from operation
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
        operations.push_back(line);
    }
    if (operations.empty())
    {
        std::cout << "Error, no valid input file" << std::endl;
        return;
    }

    std::vector<std::string> operationsPart1(operations);
    long long result = 0;
    std::for_each(operationsPart1.begin(), operationsPart1.end(), [&result](std::string &operation)
                  { result += evaluate(operation); });
    std::cout << "Part 1:  " << result << std::endl;

    std::vector<std::string> operationsPart2(operations);
    result = 0;
    std::for_each(operationsPart2.begin(), operationsPart2.end(), [&result](std::string &operation)
                  { result += evaluate2(operation); });
    std::cout << "Part 2:  " << result << std::endl;
    // std::cout << "Part 2:" << result << std::endl;
}
