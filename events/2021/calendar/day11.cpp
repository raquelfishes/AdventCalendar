
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <string>
#include <numeric>

#include "resources.h"
#include "utils_2021.h"

static const int numIterations = 100;

typedef std::pair<int, int> coord;

struct Grid
{
    Grid(std::vector<std::string> strValues)
    {
        sizeX = strValues[0].size();
        sizeY = strValues.size();

        const int numValues = sizeX * sizeY;
        values.reserve(numValues);
        visited.resize(numValues, false);
        for (auto &line : strValues)
        {
            for (auto &col : line)
            {
                values.push_back(char2int(col));
            }
        }
    }

    coord getXY(const int index)
    {
        return std::pair<int, int>((index % sizeX), (index / sizeX));
    }

    int getIndex(const coord c)
    {
        return c.first + c.second * sizeX;
    }

    bool isValidCoord(const coord c)
    {
        bool validX = (0 <= c.first && c.first <= sizeX - 1);
        bool validY = (0 <= c.second && c.second <= sizeY - 1);

        return validX && validY;
    }

    int checkAdjacent(coord orig, coord diff)
    {
        coord aux(orig.first + diff.first, orig.second + diff.second);
        if (!isValidCoord(aux))
            return 0;

        const int auxIndex = getIndex(aux);
        if (!visited[auxIndex])
            values[auxIndex] += 1;

        return updatePosition(auxIndex);
    }

    int updatePosition(const int index)
    {
        int count = 0;
        std::pair<int, int> xy = getXY(index);
        const int value = values[index];

        if ((value > 9) && (!visited[index]))
        {
            visited[index] = true;
            ++count;
            count += checkAdjacent(xy, coord(0, -1));
            count += checkAdjacent(xy, coord(-1, -1));
            count += checkAdjacent(xy, coord(0, 1));
            count += checkAdjacent(xy, coord(1, -1));
            count += checkAdjacent(xy, coord(1, 0));
            count += checkAdjacent(xy, coord(1, 1));
            count += checkAdjacent(xy, coord(-1, 0));
            count += checkAdjacent(xy, coord(-1, 1));
            values[index] = 0;
        }
        return count;
    }

    int update()
    {
        int count = 0;
        visited.clear();
        visited.resize(values.size(), false);
        std::for_each(values.begin(), values.end(), [](int &v)
                      { ++v; });
        for (int i = 0; i < values.size(); ++i)
        {
            count += updatePosition(i);
        }
        return count;
    }

    bool checkIfAllReset()
    {
        int value = std::accumulate(values.begin(), values.end(), 0);
        return value == 0;
    }

    void printGrid()
    {
        for (int i = 0; i < sizeX; ++i)
        {
            for (int j = 0; j < sizeY; ++j)
            {
                int index = getIndex(coord(j, i));
                if (values[index] == 0)
                    printf(".");
                else
                    printf("%d", values[index]);
            }
            printf("\n");
        }
        printf("\n");
        printf("\n");
    }

    int sizeX;
    int sizeY;
    std::vector<int> values;
    std::vector<bool> visited;
};

void dumboOctopusPart1()
{
    std::string resourcePath = getResourcePath(2021, 11);
    std::vector<std::string> numsStr;
    readDocument<std::string>(resourcePath, numsStr);

    Grid grid2d(numsStr);
    splitString(numsStr.front(), ',', numsStr);

    int count = 0;
    for (int i = 0; i < numIterations; ++i)
    {
        count += grid2d.update();
        // grid2d.printGrid();
    }

    int result = count;
    printf("The solution for part 1 is: %i \n", result);
}

void dumboOctopusPart2()
{
    std::string resourcePath = getResourcePath(2021, 11);
    std::vector<std::string> numsStr;
    readDocument<std::string>(resourcePath, numsStr);

    Grid grid2d(numsStr);
    splitString(numsStr.front(), ',', numsStr);

    bool allFlashes = false;
    int index = 0;
    while (!allFlashes)
    {
        grid2d.update();
        allFlashes = grid2d.checkIfAllReset();
        grid2d.printGrid();
        ++index;
    }

    int result = index;
    printf("The solution for part 2 is: %lld \n", result);
}
