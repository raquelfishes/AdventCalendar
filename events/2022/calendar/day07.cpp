#include "std_includes.h"
#include "resources.h"
#include "utils_2022.h"

void day7Part1()
{
    std::string resourcePath = getResourcePath(2022, 7);
    std::vector<std::string> input;
    readDocument(resourcePath, input);

    std::string currentDir = "";
    std::vector<std::string> dirVector;
    std::map<std::string, long long> dirMap;

    for (auto &line : input)
    {
        std::vector<std::string> simbolsLine;
        splitStringByChar(line, ' ', simbolsLine);

        if (simbolsLine.front() == "$" && simbolsLine[1] == "cd")
        {
            if (simbolsLine[2] == "..")
            {
                dirVector.pop_back();
                currentDir = dirVector.back();
            }
            else
            {
                currentDir.append("/");
                currentDir.append(simbolsLine[2]);
                dirVector.push_back(currentDir);
                dirMap[currentDir] = 0;
            }
        }
        else if (simbolsLine.front() != "$" && simbolsLine.front().find_first_not_of("0123456789") == std::string::npos)
        {
            for (auto &dir : dirVector)
            {
                dirMap[dir] += std::stoll(simbolsLine.front());
            }
        }
    }

    const long long maxSize = 100000;
    long long count = 0;
    for (auto &dir : dirMap)
    {
        if (dir.second < maxSize)
        {
            count += dir.second;
        }
    }

    long long result = count;
    printf("The solution for part 1 is: %lli \n", result);
}

void day7Part2()
{

    std::vector<std::string> dirVector;
    std::map<std::string, long long int> dirMap;

    std::string currentDir = "";

    std::string resourcePath = getResourcePath(2022, 7);
    std::vector<std::string> input;
    readDocument(resourcePath, input);

    long long int usedSpace = std::numeric_limits<long long int>::min();

    for (auto &line : input)
    {
        std::vector<std::string> simbolsLine;
        splitStringByChar(line, ' ', simbolsLine);

        if (simbolsLine.front() == "$" && simbolsLine[1] == "cd")
        {
            if (simbolsLine[2] == "..")
            {
                dirVector.pop_back();
                currentDir = dirVector.back();
            }
            else
            {
                currentDir.append("/");
                currentDir.append(simbolsLine[2]);
                dirVector.push_back(currentDir);
                dirMap[currentDir] = 0;
            }
        }
        else if (simbolsLine.front() != "$" && simbolsLine.front().find_first_not_of("0123456789") == std::string::npos)
        {
            for (auto &dir : dirVector)
            {
                dirMap[dir] += std::stoll(simbolsLine.front());
                usedSpace = std::max(usedSpace, dirMap[dir]);
            }
        }
    }

    const long long int totalDiskSize = 70000000;
    const long long int totalNeedSpace = 30000000;
    const long long int needToRemove = usedSpace - (totalDiskSize - totalNeedSpace);

    long long int removedDisk = std::numeric_limits<long long int>::max();

    if (needToRemove > 0)
    {
        for (auto &dir : dirMap)
        {
            if (dir.second >= needToRemove)
            {
                removedDisk = std::min(removedDisk, dir.second);
            }
        }
    }

    printf("The solution for part 2 is: %lli \n", removedDisk);
}
