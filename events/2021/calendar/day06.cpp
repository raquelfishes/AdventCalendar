
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <string>
#include <numeric>

#include "resources.h"
#include "utils_2021.h"

static const int iterationP1 = 80;
static const int iterationP2 = 256;
static const int valueNewFish = 8;

void lanternfishPart1()
{
    std::string resourcePath = getResourcePath(2021, 6);
    std::vector<std::string> numsStr;
    readDocument<std::string>(resourcePath, numsStr);

    splitString(numsStr.front(), ',', numsStr);

    std::vector<int> numsFish;
    std::for_each(numsStr.begin(), numsStr.end(), [&numsFish](std::string s)
                  { numsFish.push_back(std::stoi(s)); });

    // sort by value
    std::sort(numsFish.begin(), numsFish.end());

    for (int i = 0; i < iterationP1; ++i)
    {
        std::for_each(numsFish.begin(), numsFish.end(), [](int &i)
                      { --i; });
        if (numsFish.front() == -1)
        {
            std::vector<int> zeroV{-1};
            std::vector<int> sixV{6};
            auto result = std::find_end(numsFish.begin(), numsFish.end(), zeroV.begin(), zeroV.end()) + 1;
            int numZeros = (int)std::distance(numsFish.begin(), result);
            numsFish.erase(numsFish.begin(), result);
            std::fill_n(std::back_inserter(numsFish), numZeros, valueNewFish);
            result = std::upper_bound(numsFish.begin(), numsFish.end(), sixV.front());
            sixV.resize(numZeros, 6);
            numsFish.insert(result, sixV.begin(), sixV.end());
        }
    }

    int result = (int)numsFish.size();
    printf("The solution for part 1 is: %i \n", result);
}

void lanternfishPart2()
{
    std::string resourcePath = getResourcePath(2021, 6);
    std::vector<std::string> numsStr;
    readDocument<std::string>(resourcePath, numsStr);

    splitString(numsStr.front(), ',', numsStr);

    std::vector<int> numsFish;
    std::for_each(numsStr.begin(), numsStr.end(), [&numsFish](std::string s)
                  { numsFish.push_back(std::stoi(s)); });

    std::deque<int64_t> fishesCount(9, 0);

    for (auto &num : numsFish)
    {
        ++fishesCount[num];
    }

    for (int days = 256 - 1; days >= 0; days--)
    {
        const int64_t parent = fishesCount.front();
        fishesCount.pop_front();
        fishesCount[6] += parent;
        fishesCount.push_back(parent);
    }

    long long result = std::accumulate(fishesCount.begin(), fishesCount.end(), int64_t{0});
    printf("The solution for part 2 is: %lld \n", result);
}
