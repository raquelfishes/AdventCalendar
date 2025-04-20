// #include "sonar_sweep.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>

#include "resources.h"

void count1s(const std::vector<std::string> &binaryNumbers, const int pos, std::vector<int> &result)
{
    const int lengthBinary = binaryNumbers[0].size();
    for (auto &bn : binaryNumbers)
    {
        for (auto i = pos; i < lengthBinary; ++i)
        {
            result[i] += bn[i] == '1' ? 1 : 0;
        }
    }
}

void binaryDiagnosticPart1()
{
    std::string resourcePath = getResourcePath(2021, 3);
    // Open numbers file
    std::ifstream myfile(resourcePath);
    if (!myfile.is_open())
    {
        std::cout << "Error, no file founded" << std::endl;
        return;
    }

    std::vector<std::string> binaryNumbers;
    std::string number;
    while (getline(myfile, number))
    { // read data from file object and put it into string.
        binaryNumbers.push_back(number);
    }
    if (binaryNumbers.empty())
    {
        std::cout << "Error, no binary numbers at file" << std::endl;
    }

    // Part 1:
    int lengthBinary = binaryNumbers[0].size();
    std::vector<int> num1s(lengthBinary);
    for (auto &bn : binaryNumbers)
    {
        for (auto i = 0; i < lengthBinary; ++i)
        {
            num1s[i] += bn[i] == '1' ? 1 : 0;
        }
    }

    int gammaRate = 0x0;
    int epsilonRate = 0x0;
    for (auto i = 0; i < num1s.size(); ++i)
    {
        if (num1s[i] > binaryNumbers.size() / 2)
        {
            gammaRate |= (1u << lengthBinary - 1 - i);
        }
        else
        {
            epsilonRate |= (1u << lengthBinary - 1 - i);
        }
    }

    long result = gammaRate * epsilonRate;
    printf("The solution for part 1 is: %i \n", result);
}

void convertToBin(std::string st, int &value)
{
    value = 0x0;
    for (int i = 0; i < st.size(); ++i)
    {
        if (st[i] == '1')
        {
            value |= (1u << st.size() - 1 - i);
        }
    }
}

void binaryDiagnosticPart2()
{
    std::string resourcePath = getResourcePath(2021, 3);
    // Open numbers file
    std::ifstream myfile(resourcePath);
    if (!myfile.is_open())
    {
        std::cout << "Error, no file founded" << std::endl;
        return;
    }

    std::vector<std::string> binaryNumbers;
    std::string number;
    while (getline(myfile, number))
    { // read data from file object and put it into string.
        binaryNumbers.push_back(number);
    }
    if (binaryNumbers.empty())
    {
        std::cout << "Error, no binary numbers at file" << std::endl;
    }

    // Part 1:
    int lengthBinary = binaryNumbers[0].size();
    std::vector<std::string> auxBinNumbers1 = binaryNumbers;
    std::vector<std::string> auxBinNumbers2 = binaryNumbers;
    std::vector<int> num1s(lengthBinary);
    for (int i = 0; i < lengthBinary; ++i)
    {
        if (auxBinNumbers1.size() > 1)
        {
            num1s.clear();
            num1s.resize(lengthBinary, 0);
            count1s(auxBinNumbers1, i, num1s);
            int halfSize = round(auxBinNumbers1.size() * 0.5);
            std::erase_if(auxBinNumbers1, [&](std::string bn)
                          {
          const char c = num1s[i] >= halfSize ? '1' : '0';
          return (bn[i] != c); });
        }

        if (auxBinNumbers2.size() > 1)
        {
            num1s.clear();
            num1s.resize(lengthBinary, 0);
            count1s(auxBinNumbers2, i, num1s);
            int halfSize = round(auxBinNumbers2.size() * 0.5);
            std::erase_if(auxBinNumbers2, [&](std::string bn)
                          {
          const char c = num1s[i] < halfSize ? '1' : '0';
          return (bn[i] != c); });
        }
    }

    int oxygenGeneratorRating = 0x0;
    int co2scrubberRating = 0x0;
    convertToBin(auxBinNumbers1.front(), oxygenGeneratorRating);
    convertToBin(auxBinNumbers2.front(), co2scrubberRating);

    long result = oxygenGeneratorRating * co2scrubberRating;
    printf("The solution for part 2 is: %i \n", result);
}
