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

uint64_t applyMask(const std::string &mask, const std::string value)
{
    uint64_t originalValue = std::stoull(value);
    for (auto i = 0; i < mask.size(); ++i)
    {
        uint64_t auxIndex = mask.size() - 1 - i;
        const uint64_t auxMask{static_cast<uint64_t>(1) << static_cast<uint64_t>(i)};
        if (mask[auxIndex] == '1')
        {
            originalValue |= auxMask;
        }
        else if (mask[auxIndex] == '0')
        {
            originalValue &= ~(auxMask);
        }
    }
    return originalValue;
}

void getMaskPositions(const std::string &mask, const std::string value, std::vector<uint64_t> &newValues)
{
    uint64_t originalValue = std::stoull(value);
    std::vector<uint64_t> xMask;
    for (auto i = 0; i < mask.size(); ++i)
    {
        uint64_t auxIndex = mask.size() - 1 - i;
        const uint64_t auxMask{static_cast<uint64_t>(1) << static_cast<uint64_t>(i)};
        if (mask[auxIndex] == '1')
        {
            originalValue |= auxMask;
        }
        else if (mask[auxIndex] == 'X')
        {
            xMask.push_back(auxMask);
            originalValue &= ~auxMask;
        }
    }

    newValues.clear();
    newValues.push_back(originalValue);
    // We have at originalValue the default mask without apply X
    // Num possible combi is 2**xPos.size();
    std::vector<uint64_t> auxValues;
    for (auto i = 0; i < xMask.size(); ++i)
    {
        auxValues.clear();
        for (auto &newValue : newValues)
        {
            auxValues.push_back(newValue | xMask[i]);
            auxValues.push_back(newValue & ~xMask[i]);
        }
        newValues.clear();
        newValues.resize(auxValues.size());
        std::copy(auxValues.begin(), auxValues.end(), newValues.begin());
    }
}

void adventDay14()
{
    std::string resourcePath = getResourcePath(2020, 14);
    // Open numbers file
    std::ifstream myfile(resourcePath);
    if (!myfile.is_open())
    {
        std::cout << "Error, no file found" << std::endl;
        return;
    }

    std::vector<std::string> instructions;
    std::string line;
    while (getline(myfile, line))
    {
        instructions.push_back(line);
    }

    if (instructions.empty())
    {
        std::cout << "Error, no bus lines at file" << std::endl;
        return;
    }

    // mask = 00111X0X10X0000XX00011111110000011X0
    std::regex maskExpr("mask = (\\w+)");
    // mem[43834] = 524429393
    std::regex memExpr("mem\\[(\\d+)\\] = (\\d+)");
    std::smatch sm;
    std::map<uint64_t, uint64_t> memory;
    std::string currentMask = "";
    for (auto &instr : instructions)
    {
        if (std::regex_search(instr, sm, maskExpr))
        {
            currentMask = sm[1];
        }
        else if (std::regex_search(instr, sm, memExpr))
        {
            memory[std::stoull(sm[1].str())] = applyMask(currentMask, sm[2].str());
        }
    }
    uint64_t result = 0;
    for (auto &mem : memory)
    {
        result += mem.second;
    }
    std::cout << "Part1: The result is: " << result << std::endl;

    memory.clear();
    int numX = 0;
    for (auto &instr : instructions)
    {
        if (std::regex_search(instr, sm, maskExpr))
        {
            currentMask = sm[1];
            numX = std::count(currentMask.begin(), currentMask.end(), 'X');
        }
        else if (std::regex_search(instr, sm, memExpr))
        {
            std::vector<uint64_t> positions;
            getMaskPositions(currentMask, sm[1].str(), positions);
            for (auto &pos : positions)
            {
                memory[pos] = std::stoull(sm[2].str());
            }
        }
    }
    result = 0;
    for (auto &mem : memory)
    {
        result += mem.second;
    }
    std::cout << "Par2: The result is: " << result << std::endl;
}
