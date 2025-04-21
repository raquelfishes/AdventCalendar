#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "resources.h"

void adventDay3()
{
    std::string resourcePath = getResourcePath(2020, 3);
    // Open numbers file
    std::ifstream myfile(resourcePath);
    if (!myfile.is_open())
    {
        std::cout << "Error, no file found" << std::endl;
        return;
    }

    std::vector<std::string> forest;
    std::string line;
    while (getline(myfile, line))
    { // read data from file object and put it into string.
        forest.push_back(line);
    }
    if (forest.empty())
    {
        std::cout << "Error, no numbers at file" << std::endl;
    }

    constexpr int right = 3;
    int currentColumn = 0;
    int treeCounter = 0;
    // Part 1
    for (auto line : forest)
    {
        if (currentColumn != 0)
        {
            treeCounter += line[currentColumn % line.size()] == '#';
        }
        currentColumn += right;
    }
    std::cout << "Part1: The number of trees in the path are: " << treeCounter << std::endl;

    int treeCounter11 = 0;
    int treeCounter31 = 0;
    int treeCounter51 = 0;
    int treeCounter71 = 0;
    int treeCounter12 = 0;
    int currentRow = 0;

    // Part 2
    for (auto line : forest)
    {
        if (currentRow != 0)
        {
            treeCounter11 += line[(currentRow + currentRow * 0) % line.size()] == '#';
            treeCounter31 += line[(currentRow + currentRow * 2) % line.size()] == '#';
            treeCounter51 += line[(currentRow + currentRow * 4) % line.size()] == '#';
            treeCounter71 += line[(currentRow + currentRow * 6) % line.size()] == '#';
            treeCounter12 += !(currentRow % 2) && line[(currentRow - currentRow / 2) % line.size()] == '#';
        }
        currentRow++;
    }

    // Results:
    // treeCounter11: 63
    // treeCounter31: 254
    // treeCounter51: 62
    // treeCounter71: 56

    const int result = treeCounter11 * treeCounter31 * treeCounter51 * treeCounter71 * treeCounter12;
    std::cout << "Part1: The number of trees multiplication are: " << result << std::endl;
}
