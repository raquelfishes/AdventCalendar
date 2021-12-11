#include "sonar_sweep.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <string>
#include <numeric>

#include "resource.h"
#include "utils.h"


typedef std::pair<int, int> coord;

struct Grid
{
  Grid(std::vector<std::string> strValues)
  {
    sizeX = strValues[0].size();
    sizeY = strValues.size();

    const int numValues = sizeX * sizeY;
    values.reserve(numValues);
    for (auto& line : strValues)
    {
      for(auto & col : line)
      {
        values.push_back(char2int(col));
      }
    }
  }

  coord getXY(const int index)
  {
    return std::pair<int,int>((index%sizeX), (index/sizeX));
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

  bool isHighThanValue(const coord c, const int value)
  {
    return values[getIndex(c)] > value;
  }

  bool checkAdjacentLess(const coord& orig, const int& origVal, const coord diff)
  {
    coord aux(orig.first + diff.first, orig.second + diff.second);
    if (isValidCoord(aux))
    {
      if (isHighThanValue(aux, origVal))
      {
        return true;
      }
      return false;
    }
    return true;
  }

  bool checkPosition(const int index)
  {
    std::pair<int, int> xy = getXY(index);
    const int value = values[index];
    bool up    = checkAdjacentLess(xy, value, coord(0,-1));
    bool down  = checkAdjacentLess(xy, value, coord(0,1));
    bool right = checkAdjacentLess(xy, value, coord(1,0));
    bool left  = checkAdjacentLess(xy, value, coord(-1,0));

    return up && down && right && left;
  }

  int getRiskyLevel(const int index)
  {
    return values[index] + 1;
  }

  bool checkAdjacentBasin(const coord& orig, const int& origVal, const coord diff)
  {
    coord aux(orig.first + diff.first, orig.second + diff.second);
    if (isValidCoord(aux))
    {
      if (isHighThanValue(aux, origVal))
      {
        return true;
      }
      return false;
    }
    return true;
  }

  int computeSizeBasin(const int index)
  {
    int size = 0;
    if (values[index] == 9) return 0;
    if (visited[index]) return 0;

    std::pair<int, int> xy = getXY(index);
    // Add current grid position to size and remove for avoid infinite loops
    ++size;
    visited[index] = true;

    coord up(xy.first + 0, xy.second - 1);
    coord down(xy.first + 0, xy.second + 1);
    coord left(xy.first - 1, xy.second + 0);
    coord right(xy.first + 1, xy.second + 0);
    if (isValidCoord(up))
    {
      size += computeSizeBasin(getIndex(up));
    }
    if (isValidCoord(down))
    {
      size += computeSizeBasin(getIndex(down));
    }
    if (isValidCoord(left))
    {
      size += computeSizeBasin(getIndex(left));
    }
    if (isValidCoord(right))
    {
      size += computeSizeBasin(getIndex(right));
    }

    return size;
  }


  int sizeX;
  int sizeY;
  std::vector<int> values;
  std::vector<bool> visited;
};

void smokeBasinPart1()
{
  std::vector<std::string> numsStr;
  readDocument<std::string>(DAY9_PATH, numsStr);

  Grid grid2d(numsStr);
  splitString(numsStr.front(), ',', numsStr);

  int count = 0;
  for (int i = 0; i < grid2d.values.size(); ++i)
  {
    bool isLowPoint = grid2d.checkPosition(i);
    if (isLowPoint)
      count += grid2d.getRiskyLevel(i);
  }

  int result = count;
  printf("The solution for part 1 is: %i \n", result);

}

void smokeBasinPart2()
{
 
  std::vector<std::string> numsStr;
  readDocument<std::string>(DAY9_PATH, numsStr);

  Grid grid2d(numsStr);
  splitString(numsStr.front(), ',', numsStr);

  int count = 0;
  std::vector<int> basins;
  grid2d.visited.resize(grid2d.values.size(), false);
  for (int i = 0; i < grid2d.values.size(); ++i)
  {
    bool isLowPoint = grid2d.checkPosition(i);
    if (isLowPoint)
      basins.push_back(grid2d.computeSizeBasin(i));
  }

  std::sort(basins.begin(), basins.end());
  std::reverse(basins.begin(), basins.end());

  int result = basins[0]*basins[1]*basins[2];
  printf("The solution for part 2 is: %lld \n", result);
}
