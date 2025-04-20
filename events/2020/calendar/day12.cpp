#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <numeric>
#include <limits>

#include "resources.h"

void addToDirection(const char dir, const int value, std::pair<int, int> &pos)
{
    switch (dir)
    {
    case 'E':
        pos.first += value;
        break;
    case 'S':
        pos.second -= value;
        break;
    case 'W':
        pos.first -= value;
        break;
    case 'N':
        pos.second += value;
        break;
    default:
        break;
    }
}

void rotatePoint(const char dir, const int value, std::pair<int, int> &pos)
{
    const int nRotate = value / 90;
    const bool isR = dir == 'R';

    for (auto i = 0; i < nRotate; ++i)
    {
        if (dir == 'R')
        {
            //(10, 4) -> (4, -10) -> (-10, -4) -> (-4, 10 ) -> (10, 4)
            const int aux = pos.first;
            pos.first = pos.second;
            pos.second = -1 * aux;
        }
        else if (dir == 'L')
        {
            //(10, 4) -> (-4, 10) -> (-10, -4) -> (4, -10 ) -> (10, 4)
            const int aux = pos.first;
            pos.first = -1 * pos.second;
            pos.second = aux;
        }
    }
}

void adventDay12()
{
    std::string resourcePath = getResourcePath(2020, 12);
    // Open numbers file
    std::ifstream myfile(resourcePath);
    if (!myfile.is_open())
    {
        std::cout << "Error, no file found" << std::endl;
        return;
    }

    std::vector<std::pair<char, int>> directions;
    std::string line;
    std::regex expr("(\\w)(\\d+)");
    std::smatch sm;
    while (getline(myfile, line))
    {
        if (std::regex_search(line, sm, expr))
        {
            std::pair<char, int> myPair(sm[1].str().c_str()[0], std::stoi(sm[2].str()));
            directions.push_back(myPair);
        }
    }
    if (directions.empty())
    {
        std::cout << "Error, no numbers at file" << std::endl;
        return;
    }

    const std::vector<char> cardinalDirections = {'E', 'S', 'W', 'N'};

    // Add final adapter
    int currentDir = 0;                   // 0 is the East index at cardinalDirections
    std::pair<int, int> currentPos(0, 0); // Positive values E,N
    for (auto &dir : directions)
    {
        if (std::find(cardinalDirections.begin(), cardinalDirections.end(), dir.first) != cardinalDirections.end())
        {
            addToDirection(dir.first, dir.second, currentPos);
        }
        if (dir.first == 'F')
        {
            addToDirection(cardinalDirections[currentDir], dir.second, currentPos);
        }
        else if (dir.first == 'R')
        {
            currentDir = (currentDir + dir.second / 90) % cardinalDirections.size();
        }
        else if (dir.first == 'L')
        {
            currentDir = (currentDir - dir.second / 90) % cardinalDirections.size();
        }
    }

    int result = std::abs(currentPos.first) + std::abs(currentPos.second);
    std::cout << "Part1: The result is: " << result << std::endl;

    std::pair<int, int> waypoint(10, 1); // E, N
    std::pair<int, int> ship(0, 0);      // Positive values E,N

    for (auto &dir : directions)
    {
        if (std::find(cardinalDirections.begin(), cardinalDirections.end(), dir.first) != cardinalDirections.end())
        {
            addToDirection(dir.first, dir.second, waypoint);
        }
        if (dir.first == 'F')
        {
            ship.first += waypoint.first * dir.second;
            ship.second += waypoint.second * dir.second;
        }
        else if (dir.first == 'R' || dir.first == 'L')
        {
            rotatePoint(dir.first, dir.second, waypoint);
        }
    }

    result = std::abs(ship.first) + std::abs(ship.second);
    std::cout << "Par2: The result is: " << result << std::endl;
}
