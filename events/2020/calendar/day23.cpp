#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <regex>
#include <numeric>
#include <limits>

#include "resources.h"

// 418976235

#define MOVES 100
#define MILLION 1000000

struct Cup
{
    int value;
    std::shared_ptr<Cup> next;
};

auto foundItCup(const int desiredCup, const std::list<int> &cups)
{
    auto found = std::find(cups.begin(), cups.end(), desiredCup);
    if (found != cups.end())
    {
        return found;
    }
    else
    {
        if ((desiredCup - 1) > 0)
        {
            return foundItCup(desiredCup - 1, cups);
        }
        else
        {
            return foundItCup(9, cups);
        }
    }
}

void mixCups(const int count, const int max, std::list<int> &cups)
{
    for (int i = 0; i < count; ++i)
    {
        const int currentCup = cups.front();
        cups.pop_front();

        std::list<int> pick;
        auto it = cups.begin();
        std::advance(it, 3);
        pick.splice(pick.begin(), cups, cups.begin(), it);

        int desiredCup = currentCup - 1 < 1 ? max : currentCup - 1;
        while (std::find(pick.begin(), pick.end(), desiredCup) != pick.end())
        {
            desiredCup = desiredCup - 1 < 1 ? max : desiredCup - 1;
        }

        auto found = std::find(cups.begin(), cups.end(), desiredCup);
        std::advance(found, 1); // Insert back found, not before
        cups.splice(found, pick);
        cups.push_back(currentCup);
    }
}

void mixCupsPtr(const int count, const int max, const int init, std::vector<std::shared_ptr<Cup>> &index)
{
    std::shared_ptr<Cup> currentCup = index[init - 1];
    std::shared_ptr<Cup> nextCup = currentCup->next;
    std::shared_ptr<Cup> auxCup = nullptr;
    for (int i = 0; i < count; ++i)
    {
        std::list<std::shared_ptr<Cup>> pick;
        pick.push_back(nextCup);
        nextCup = nextCup->next;
        pick.push_back(nextCup);
        nextCup = nextCup->next;
        pick.push_back(nextCup);
        nextCup = nextCup->next;

        int desiredCupId = currentCup->value - 1 < 1 ? max : currentCup->value - 1;
        std::shared_ptr<Cup> desiredCup = index[desiredCupId - 1];
        while (std::find(pick.begin(), pick.end(), desiredCup) != pick.end())
        {
            desiredCupId = desiredCupId - 1 < 1 ? max : desiredCupId - 1;
            desiredCup = index[desiredCupId - 1];
        }

        auxCup = desiredCup->next;
        desiredCup->next = pick.front();
        currentCup->next = pick.back()->next;
        pick.back()->next = auxCup;
        // Update iterators
        currentCup = currentCup->next;
        nextCup = currentCup->next;
    }
}

void adventDay23()
{
    std::string resourcePath = getResourcePath(2020, 23);
    // Open numbers file
    std::ifstream myfile(resourcePath);
    if (!myfile.is_open())
    {
        std::cout << "Error, no file found" << std::endl;
        return;
    }

    std::vector<int> originalCups;

    std::string line;
    getline(myfile, line);
    for (auto i : line)
    {
        originalCups.push_back(i - '0');
    }
    if (originalCups.empty())
    {
        std::cout << "No valid file input" << std::endl;
    }

    std::list<int> cups1(originalCups.begin(), originalCups.end());
    mixCups(MOVES, 9, cups1);
    auto foundOne = std::find(cups1.begin(), cups1.end(), 1);
    std::advance(foundOne, 1);
    std::string result = std::accumulate(std::next(foundOne), cups1.end(),
                                         std::to_string(*foundOne), [](std::string a, int b)
                                         { return std::move(a) + std::to_string(b); });

    result += std::accumulate(std::next(cups1.begin()), std::prev(foundOne),
                              std::to_string(*cups1.begin()), [](std::string a, int b)
                              { return std::move(a) + std::to_string(b); });

    std::cout << "Part 1:  " << result << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    // Create new structure with pointers
    std::vector<std::shared_ptr<Cup>> index(MILLION);
    // std::list<Cup> cups2;

    for (int i = 0; i < MILLION; ++i)
    {
        Cup cup;
        std::shared_ptr<Cup> prev;
        if (i < originalCups.size())
        {
            cup.value = originalCups[i];
            prev = i - 1 < 0 ? nullptr : index[originalCups[i - 1] - 1];
        }
        else
        {
            cup.value = i + 1;
            prev = i - 1 > originalCups.size() - 1 ? index[i - 1] : index[originalCups[i - 1] - 1];
        }
        std::shared_ptr<Cup> ptrCup = std::make_shared<Cup>(cup);
        if (prev != nullptr)
        {
            prev->next = ptrCup;
        }
        index[cup.value - 1] = ptrCup;
    }
    index.back()->next = index[originalCups.front() - 1];
    // index[originalCups.back() - 1]->next = index[originalCups.front() - 1];

    mixCupsPtr(MILLION * 10, MILLION, originalCups.front(), index);

    const long long afterOne = index[0]->next->value;
    const long long afterafterOne = index[0]->next->next->value;

    long long result2 = afterOne * afterafterOne;
    std::cout << "Part 2:  " << result2 << std::endl;
    // std::cout << "Part 2:" << result << std::endl;
}
