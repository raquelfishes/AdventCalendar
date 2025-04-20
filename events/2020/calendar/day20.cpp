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

struct Tile
{
    int tileId;
    std::vector<std::string> tileInfo;
    typedef std::pair<std::string, int> side;

    side left;
    side right;
    side up;
    side down;

    Tile() {};
    Tile(int tileId) : tileId(tileId)
    {
        left = std::make_pair<std::string, int>("", -1);
        right = std::make_pair<std::string, int>("", -1);
        up = std::make_pair<std::string, int>("", -1);
        down = std::make_pair<std::string, int>("", -1);
    };

    bool isCorner() const
    {
        int countSides = 0;
        countSides += left.second != -1;
        countSides += right.second != -1;
        countSides += up.second != -1;
        countSides += down.second != -1;

        return countSides == 2;
    }

    void computeSides()
    {
        up.first = tileInfo[0];
        down.first = tileInfo[tileInfo.size() - 1];
        for (auto &row : tileInfo)
        {
            left.first.push_back(row[0]);
            right.first.push_back(row[row.size() - 1]);
        }
    }

    bool checkSide(side &side, Tile &tile)
    {
        if (side.second == -1)
        {
            std::string reverse = side.first;
            std::reverse(reverse.begin(), reverse.end());
            if ((tile.left.second == -1) && ((side.first == tile.left.first) || (reverse == tile.left.first)))
            {
                side.second = tile.tileId;
                tile.left.second = tileId;
                return true;
            }
            if ((tile.right.second == -1) && ((side.first == tile.right.first) || (reverse == tile.right.first)))
            {
                side.second = tile.tileId;
                tile.right.second = tileId;
                return true;
            }
            if ((tile.up.second == -1) && ((side.first == tile.up.first) || (reverse == tile.up.first)))
            {
                side.second = tile.tileId;
                tile.up.second = tileId;
                return true;
            }
            if ((tile.down.second == -1) && ((side.first == tile.down.first) || (reverse == tile.down.first)))
            {
                side.second = tile.tileId;
                tile.down.second = tileId;
                return true;
            }
        }
        return false;
    }

    void matchTile(Tile &tile)
    {
        bool matched = false;
        matched = checkSide(left, tile);
        matched = checkSide(right, tile);
        matched = checkSide(up, tile);
        matched = checkSide(down, tile);
    }
};

void adventDay20()
{
    std::string resourcePath = getResourcePath(2020, 20);
    // Open numbers file
    std::ifstream myfile(resourcePath);
    if (!myfile.is_open())
    {
        std::cout << "Error, no file found" << std::endl;
        return;
    }

    std::map<int, Tile> mapTiles;
    std::string line;
    std::regex expr("Tile (\\d+):");
    std::smatch sm;
    int tileId = -1;
    while (getline(myfile, line))
    {
        if (std::regex_search(line, sm, expr))
        {
            tileId = std::stoi(sm[1].str());
            mapTiles[tileId] = Tile(tileId);
        }
        else if (line != "")
        {
            mapTiles[tileId].tileInfo.push_back(line);
        }
    }
    if (mapTiles.empty())
    {
        std::cout << "Error, no valid input file" << std::endl;
        return;
    }

    for (auto &tile : mapTiles)
    {
        tile.second.computeSides();
    }

    for (auto &tile1 : mapTiles)
    {
        for (auto &tile2 : mapTiles)
        {
            if (tile1.first == tile2.first)
            {
                continue;
            }
            tile1.second.matchTile(tile2.second);
        }
    }

    long long result = 1;
    for (auto &tile : mapTiles)
    {
        if (tile.second.isCorner())
        {
            result *= tile.second.tileId;
        }
    }

    std::cout << "Part 1:  " << result << std::endl;

    std::cout << "Part 2:  " << result << std::endl;
    // std::cout << "Part 2:" << result << std::endl;
}
