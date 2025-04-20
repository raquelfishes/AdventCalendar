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

#define SUBJECT_NUMBER 7
#define DIVIDING_NUMBER 20201227

void transform(long long &resultKey, const int subjectNumber)
{
    resultKey *= subjectNumber;
    resultKey = resultKey % DIVIDING_NUMBER;
}

int getLoopSize(const int publicKey)
{
    long long auxKey = 1;
    int loopSize = 0;
    while (auxKey != publicKey)
    {
        transform(auxKey, SUBJECT_NUMBER);
        loopSize++;
    }
    return loopSize;
}

int transformKey(long long publicKey, const int loopSize)
{
    long long auxKey = 1;
    for (int i = 0; i < loopSize; ++i)
    {
        transform(auxKey, publicKey);
    }
    return auxKey;
}

void adventDay22()
{
    std::string fileName = getResourcePath(2020, 25);
    // Open numbers file
    std::ifstream myfile(fileName);
    if (!myfile.is_open())
    {
        std::cout << "Error, no file found" << std::endl;
        return;
    }

    std::string line;
    getline(myfile, line);
    const int cardKey = std::stoi(line);
    getline(myfile, line);
    const int doorKey = std::stoi(line);

    if (!cardKey || !doorKey)
    {
        std::cout << "No valid input file" << std::endl;
    }

    const int cardLoopSize = getLoopSize(cardKey);
    const int doorLoopSize = getLoopSize(doorKey);

    const int cardEncrypt = transformKey(doorKey, cardLoopSize);
    const int doorEncrypt = transformKey(cardKey, doorLoopSize);

    int encription;
    std::cout << "Part 1:  " << cardEncrypt << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Part 2:  " << encription << std::endl;
}
