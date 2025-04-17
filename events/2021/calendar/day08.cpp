#include "sonar_sweep.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

#include "resource.h"
#include "utils.h"


struct Line
{
  Line(int x1, int y1, int x2, int y2) :
    x1(x1), y1(y1), x2(x2), y2(y2)
  { 
    lineVector = std::pair<int, int>(x2 - x1, y2 - y1);
  };

  Line(std::string s)
  {
    std::vector<std::string> values;
    std::regex exp("(\\d+),(\\d+) -> (\\d+),(\\d+)");
    splitByRegex(s, exp, values);
    x1 = std::stoi(values[1]);
    y1 = std::stoi(values[2]);
    x2 = std::stoi(values[3]);
    y2 = std::stoi(values[4]);

    lineVector = std::pair<int, int>(x2 - x1, y2 - y1);
    lineVector.first /= lineVector.first != 0 ? std::abs(lineVector.first) : 1;
    lineVector.second /= lineVector.second != 0 ? std::abs(lineVector.second) : 1;
  }

  bool isStraight()
  {
    return x1 == x2 || y1 == y2;
  }

  bool isDiagonal()
  {
    return std::abs(lineVector.first) && std::abs(lineVector.second);
  }

  int x1;
  int y1;
  int x2;
  int y2;

  std::pair<int, int> lineVector;
};

struct BBox
{
  int minX = std::numeric_limits<int>::max();
  int minY = std::numeric_limits<int>::max();

  int maxX = std::numeric_limits<int>::min();
  int maxY = std::numeric_limits<int>::min();
};

int compute2dPosition(const int x, const int y, const int sizeX, const int sizeY)
{
  return x + y * sizeX;
}

void markAsVisited(const Line& line, std::vector<int>& grid2d, const int sizeX, const int sizeY)
{
  std::pair<int, int> aux = line.lineVector;
  
  std::pair<int, int> currentPoint(line.x1, line.y1);
  std::pair<int, int> endPoint(line.x2, line.y2);
  
  do
  {
    int d_position = compute2dPosition(currentPoint.first, currentPoint.second, sizeX, sizeY);
    grid2d[d_position] += 1;
    currentPoint.first += line.lineVector.first;
    currentPoint.second += line.lineVector.second;
  } while (currentPoint != endPoint);

  // Add last point
  int d_position = compute2dPosition(currentPoint.first, currentPoint.second, sizeX, sizeY);
  grid2d[d_position] += 1;
}

void printGrid(const std::vector<int>& grid, const int sizeX, const int sizeY)
{
  for (int i = 0; i < sizeX; ++i)
  {
    for (int j = 0; j < sizeY; ++j)
    {
      int index = compute2dPosition(j, i, sizeX, sizeY);
      if (grid[index] == 0)
        printf(".");
      else
        printf("%d", grid[index]);
    }
    printf("\n");
  }
  printf("\n");
  printf("\n");
}

void hydrothermalVenturePart1()
{
  std::vector<Line> lines;
  readDocument<Line>(DAY5_PATH, lines);

  // Compute de limits of 2D grid
  BBox bbox;
  for ( auto& line : lines)
  {
    bbox.minX = std::min(bbox.minX, std::min(line.x1, line.x2));
    bbox.minY = std::min(bbox.minY, std::min(line.y1, line.y2));

    bbox.maxX = std::max(bbox.maxX, std::max(line.x1, line.x2));
    bbox.maxY = std::max(bbox.maxY, std::max(line.y1, line.y2));
  }

  int length = bbox.maxX+1;//std::abs(bbox.maxX - bbox.minX)+1;
  int height = bbox.maxY+1;//std::abs(bbox.maxY - bbox.minY)+1;
  int size = length * height;

  std::vector<int> grid2d(size, 0);

  // Fill 2D with lines
  for (auto& line : lines)
  {
    if ( line.isStraight())
      markAsVisited(line, grid2d, length, height);
    //printGrid(grid2d, length, height);
  }

  int result = 0;
  std::for_each(grid2d.begin(), grid2d.end(), [&result](int& n) { result += (n>1); });
  

  printf("The solution for part 1 is: %i \n", result);

}

void hydrothermalVenturePart2()
{
  std::vector<Line> lines;
  readDocument<Line>(DAY5_PATH, lines);

  // Compute de limits of 2D grid
  BBox bbox;
  for (auto& line : lines)
  {
    bbox.minX = std::min(bbox.minX, std::min(line.x1, line.x2));
    bbox.minY = std::min(bbox.minY, std::min(line.y1, line.y2));

    bbox.maxX = std::max(bbox.maxX, std::max(line.x1, line.x2));
    bbox.maxY = std::max(bbox.maxY, std::max(line.y1, line.y2));
  }

  int length = bbox.maxX+1;//std::abs(bbox.maxX - bbox.minX)+1;
  int height = bbox.maxY+1;//std::abs(bbox.maxY - bbox.minY)+1;
  int size = length * height;

  std::vector<int> grid2d(size, 0);

  // Fill 2D with lines
  for (auto& line : lines)
  {
    if (line.isStraight() || line.isDiagonal())
      markAsVisited(line, grid2d, length, height);
    //printGrid(grid2d, length, height);
  }

  int result = 0;
  std::for_each(grid2d.begin(), grid2d.end(), [&result](int& n) { result += (n > 1); });

  printf("The solution for part 2 is: %i \n", result);
}
