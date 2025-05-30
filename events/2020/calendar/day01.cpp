#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "resources.h"

void adventDay1()
{
    std::string resourcePath = getResourcePath(2020, 1);
    // Open numbers file
    std::ifstream myfile(resourcePath);
    if (!myfile.is_open())
    {
        std::cout << "Error, no file founded" << std::endl;
        return;
    }

    std::vector<int> numbers;
    std::string number;
    while (getline(myfile, number))
    { // read data from file object and put it into string.
        numbers.push_back(std::stoi(number));
    }
    if (numbers.empty())
    {
        std::cout << "Error, no numbers at file" << std::endl;
    }

    // Part 1:
    for (auto i = 0; i < numbers.size(); ++i)
    {
        for (auto j = i + 1; j < numbers.size(); ++j)
        {
            auto sum = numbers[i] + numbers[j];
            if (sum == 2020)
            {
                std::cout << "Part1: Success!!! Numbers found: " << numbers[i] << "  " << numbers[j] << std::endl;
                auto mult = numbers[i] * numbers[j];
                std::cout << "Result Part1: " << mult << std::endl;
            }
        }
    }

    // Part 2:
    for (auto i = 0; i < numbers.size(); ++i)
    {
        for (auto j = i + 1; j < numbers.size(); ++j)
        {
            for (auto k = j + 1; k < numbers.size(); ++k)
            {
                auto sum = numbers[i] + numbers[j] + numbers[k];
                if (sum == 2020)
                {
                    std::cout << "Part2: Success!!! Numbers found: " << numbers[i] << "  " << numbers[j] << "  " << numbers[k] << std::endl;
                    auto mult = numbers[i] * numbers[j] * numbers[k];
                    std::cout << "Result: " << mult << std::endl;
                }
            }
        }
    }
}