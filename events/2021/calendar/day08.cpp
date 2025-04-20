
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <numeric>

#include "resources.h"
#include "utils_2021.h"

struct digitalNumbers
{
    digitalNumbers(std::string s)
    {
        std::vector<std::string> splitedSystem;
        splitString(s, '|', splitedSystem);

        splitString(splitedSystem.front(), ' ', numbersSystem);
        splitString(splitedSystem.back(), ' ', selectedNumbers);
    }

    int countEasyNums()
    {
        int count = 0;
        for (auto &num : selectedNumbers)
        {
            count += (num.size() == 2) || (num.size() == 3) || (num.size() == 4) || (num.size() == 7);
        }
        return count;
    }

    std::string getOne()
    {
        for (auto &num : numbersSystem)
        {
            if (num.size() == 2)
            {
                return num;
            }
        }
        return "";
    }

    std::string getSeven()
    {
        for (auto &num : numbersSystem)
        {
            if (num.size() == 3)
            {
                // std::vector<char> v;
                // auto it = std::set_difference(num.begin(), num.end(), numberMap[1].begin(), numberMap[1].end(), v.begin());
                // charPosition[v.front()] = 0;
                return num;
            }
        }
        return "";
    }

    std::string getFour()
    {
        for (auto &num : numbersSystem)
        {
            if (num.size() == 4)
                return num;
        }
        return "";
    }

    std::string getEight()
    {
        for (auto &num : numbersSystem)
        {
            if (num.size() == 7)
                return num;
        }
        return "";
    }

    std::string getNine()
    {
        std::string join47 = numberMap[4];
        join47.insert(join47.begin(), numberMap[7].begin(), numberMap[7].end());
        std::sort(join47.begin(), join47.end());
        join47.erase(std::unique(join47.begin(), join47.end()), join47.end());

        for (auto &num : numbersSystem)
        {
            std::string auxNum = num;
            std::sort(auxNum.begin(), auxNum.end());
            if (num.size() == 6)
            {
                std::vector<int> v(7);
                auto it = std::set_difference(auxNum.begin(), auxNum.end(), join47.begin(), join47.end(), v.begin());
                v.resize(it - v.begin());
                if (v.size() == 1)
                    return num;
            }
        }
    }

    std::string getSix()
    {
        for (auto &num : numbersSystem)
        {
            if (num.size() == 6)
            {
                std::string join7Num = numberMap[7];
                join7Num.insert(join7Num.begin(), num.begin(), num.end());
                std::sort(join7Num.begin(), join7Num.end());
                join7Num.erase(std::unique(join7Num.begin(), join7Num.end()), join7Num.end());
                if (join7Num == numberMap[8])
                    return num;
            }
        }
    }

    std::string getZero()
    {
        for (auto &num : numbersSystem)
        {
            if (num.size() == 6 && (num != numberMap[6] && num != numberMap[9]))
            {
                return num;
            }
        }
    }

    std::string getThree()
    {
        for (auto &num : numbersSystem)
        {
            std::string auxNum = num;
            if (num.size() == 5)
            {
                std::string join1Num = numberMap[1];
                std::vector<int> v(5);
                auto it = std::set_difference(auxNum.begin(), auxNum.end(), join1Num.begin(), join1Num.end(), v.begin());
                v.resize(it - v.begin());
                if (v.size() == 3)
                    return num;
            }
        }
    }

    std::string getFive()
    {
        for (auto &num : numbersSystem)
        {
            std::string auxNum = num;
            if (num.size() == 5)
            {
                std::string join8Num = numberMap[8];
                std::vector<char> v(5);
                auto it = std::set_intersection(numberMap[6].begin(), numberMap[6].end(), numberMap[9].begin(), numberMap[9].end(), v.begin());
                v.resize(it - v.begin());
                auto result = std::string(v.begin(), v.end());
                if (result == num)
                    return num;
            }
        }
    }

    std::string getTwo()
    {
        for (auto &num : numbersSystem)
        {
            std::string auxNum = num;
            if (num.size() == 5 && (num != numberMap[3] && num != numberMap[5]))
            {
                return num;
            }
        }
    }

    void translateNumbers()
    {
        std::for_each(numbersSystem.begin(), numbersSystem.end(), [](std::string &s)
                      { std::sort(s.begin(), s.end()); });
        std::for_each(selectedNumbers.begin(), selectedNumbers.end(), [](std::string &s)
                      { std::sort(s.begin(), s.end()); });
        numberMap[1] = getOne();
        numberMap[7] = getSeven();
        numberMap[4] = getFour();
        numberMap[8] = getEight();
        numberMap[9] = getNine();
        numberMap[6] = getSix();
        numberMap[0] = getZero();
        numberMap[3] = getThree();
        numberMap[5] = getFive();
        numberMap[2] = getTwo();

        numberMap2[numberMap[0]] = 0;
        numberMap2[numberMap[1]] = 1;
        numberMap2[numberMap[2]] = 2;
        numberMap2[numberMap[3]] = 3;
        numberMap2[numberMap[4]] = 4;
        numberMap2[numberMap[5]] = 5;
        numberMap2[numberMap[6]] = 6;
        numberMap2[numberMap[7]] = 7;
        numberMap2[numberMap[8]] = 8;
        numberMap2[numberMap[9]] = 9;
    }

    int getResultNumber()
    {
        int result = 0;
        for (int i = 0; i < selectedNumbers.size(); ++i)
        {
            if (selectedNumbers[i] != "")
            {
                result += numberMap2[selectedNumbers[i]] * std::pow(10, selectedNumbers.size() - i - 1);
            }
        }
        return result;
    }

    std::vector<std::string> numbersSystem;
    std::vector<std::string> selectedNumbers;

    std::map<int, std::string> numberMap;
    std::map<std::string, int> numberMap2;
};

void sevenSegmentSearchPart1()
{
    std::string resourcePath = getResourcePath(2021, 8);
    std::vector<digitalNumbers> allNumberSystems;
    readDocument<digitalNumbers>(resourcePath, allNumberSystems);

    int countEasyNums = 0;
    for (auto &sys : allNumberSystems)
    {
        countEasyNums += sys.countEasyNums();
    }

    int result = countEasyNums;
    printf("The solution for part 1 is: %i \n", result);
}

void sevenSegmentSearchPart2()
{
    std::string resourcePath = getResourcePath(2021, 8);
    std::vector<digitalNumbers> allNumberSystems;
    readDocument<digitalNumbers>(resourcePath, allNumberSystems);

    long long value = 0;
    for (auto &sys : allNumberSystems)
    {
        sys.translateNumbers();
        value += sys.getResultNumber();
    }

    long long result = value;
    printf("The solution for part 2 is: %lld \n", result);
}
