#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <numeric>

#include "resources.h"

int binarySearch(std::string seat, int pos, int min, int max)
{
    if (min == max)
        return min;
    if (pos < seat.size())
    {
        if ((seat[pos] == 'F') || (seat[pos] == 'L'))
        {
            max -= ((max - min) / 2) + 1;
            return binarySearch(seat, ++pos, min, max);
        }
        else if ((seat[pos] == 'B') || (seat[pos] == 'R'))
        {
            min += ((max - min) / 2) + 1;
            return binarySearch(seat, ++pos, min, max);
        }
    }
}

int computeRow(std::string seat)
{
    constexpr int numberOfRows = 128;
    return binarySearch(seat, 0, 0, numberOfRows - 1);
}

int computeColumn(std::string seat)
{
    constexpr int numberOfColumns = 8;
    return binarySearch(seat, 0, 0, numberOfColumns - 1);
}

int computeSeatId(const int row, const int column)
{
    return row * 8 + column;
}

void adventDay5()
{
    std::string resourcePath = getResourcePath(2020, 1);
    // Open numbers file
    std::ifstream myfile(resourcePath);
    if (!myfile.is_open())
    {
        std::cout << "Error, no file found" << std::endl;
        return;
    }

    std::vector<std::string> seats;
    std::string line;
    std::smatch sm;
    while (getline(myfile, line))
    {
        seats.push_back(line);
    }
    if (seats.empty())
    {
        std::cout << "Error, no seats at file" << std::endl;
    }

    constexpr int numberOfRows = 128;
    constexpr int numberOfColumns = 8;

    std::vector<std::vector<bool>> plane;
    plane.resize(numberOfRows, std::vector<bool>(numberOfColumns, false));

    int highestSeatId = 0;
    std::for_each(seats.begin(), seats.end(), [&highestSeatId, &plane, &numberOfRows, &numberOfColumns](std::string &seat)
                  {
    const int row = binarySearch( seat.substr( 0, 7 ), 0, 0, numberOfRows - 1 );
    const int column = binarySearch( seat.substr( 7 ), 0, 0, numberOfColumns - 1 );
    plane[row][column] = true;
    const int seatId = computeSeatId( row, column );
    highestSeatId = highestSeatId < seatId ? seatId : highestSeatId; });
    std::cout << "Part1: The highest seat id is: " << highestSeatId << std::endl;

    int mySeatId;
    for (auto i = 0; i < plane.size(); ++i)
    {
        int used = std::accumulate(plane[i].begin(), plane[i].end(), 0);
        if (used == 7)
        {
            for (auto j = 0; j < plane[i].size(); ++j)
            {
                if (!plane[i][j])
                {
                    mySeatId = computeSeatId(i, j);
                }
            }
        }
    }
    std::cout << "Part2: My seatId is: " << mySeatId << std::endl;
}
