
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <numeric>

#include "resources.h"
#include "utils_2021.h"

std::map<char, int> syntaxError{{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
std::map<char, int> syntaxAutocomplete{{')', 1}, {']', 2}, {'}', 3}, {'>', 4}};
std::map<char, char> closePair{{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};

bool isOpeningChar(const char c)
{
    return (c == '(') || (c == '[') || (c == '{') || (c == '<');
}

bool isClosingChar(const char c)
{
    return !isOpeningChar(c);
}

void syntaxScoringPart1()
{
    std::string resourcePath = getResourcePath(2021, 10);
    std::vector<std::string> chunksStr;
    readDocument<std::string>(resourcePath, chunksStr);

    long long errorValue = 0;
    for (auto &line : chunksStr)
    {
        std::stack<char> chunkStack;
        for (auto &c : line)
        {
            if (isOpeningChar(c))
                chunkStack.push(c);
            else
            {
                if (closePair[chunkStack.top()] == c)
                    chunkStack.pop();
                else
                {
                    errorValue += syntaxError[c];
                    break;
                }
            }
        }
    }

    long long result = errorValue;
    printf("The solution for part 1 is: %i \n", result);
}

void syntaxScoringPart2()
{
    std::string resourcePath = getResourcePath(2021, 10);
    std::vector<std::string> chunksStr;
    readDocument<std::string>(resourcePath, chunksStr);

    std::vector<long long> autocompleteValues;
    for (auto &line : chunksStr)
    {
        std::stack<char> chunkStack;
        for (auto &c : line)
        {
            if (isOpeningChar(c))
                chunkStack.push(c);
            else
            {
                if (closePair[chunkStack.top()] == c)
                    chunkStack.pop();
                else
                {
                    line = "";
                    break;
                }
            }
        }
        if ((line == "") || chunkStack.empty())
            continue;

        {
            long long chunkValue = 0;
            while (!chunkStack.empty())
            {
                chunkValue *= 5;
                chunkValue += syntaxAutocomplete[closePair[chunkStack.top()]];
                chunkStack.pop();
            }
            autocompleteValues.push_back(chunkValue);
        }
    }

    std::sort(autocompleteValues.begin(), autocompleteValues.end());
    auto middle = autocompleteValues.size() / 2;

    long long result = autocompleteValues[middle];
    printf("The solution for part 2 is: %lld \n", result);
}
