#include "std_includes.h"
#include "resource.h"
#include "utils.h"
#include "grid.h"

enum moveDir{RIGHT=0, DOWN=1, LEFT=2, UP=3};
const std::vector<Coord> moveVector = { {1,0}, {0,1}, {-1,0}, {0,-1} };

Coord getNextPos(Coord curr, Coord move, const Grid<char>& grid)
{
  Coord result = curr;
  result.first = result.first + move.first;
  result.second = result.second + move.second;
  if (!grid.isValidCoord(result))
  {
    if (result.first < 0) result.first = grid.sizeX - 1;
    if (result.first >= grid.sizeX) result.first = 0;
    if (result.second < 0) result.second = grid.sizeY - 1;
    if (result.second >= grid.sizeY) result.second = 0;
  }
  char aux = grid.getValue(result);
  while (aux == ' ')
  {
    result = getNextPos(result, move, grid);
    aux = grid.getValue(result);
  }
  return result;
}

void day22Part1()
{
  std::vector<std::string> input;
  readDocument(DAY22_PATH, input);

  int moveIndex = 0;
  
  std::vector<int> moveX = { 1, 0, -1, 0 };
  std::vector<int> moveY = { 0, 1, 0, -1 };

  std::string instrucions = input.back();
  input.pop_back(); input.pop_back();

  size_t maxX = std::numeric_limits<size_t>::min();
  std::for_each(input.begin(), input.end(), [&maxX] (const std::string& s) { maxX = std::max(maxX, s.size()); });
  Grid<char> grid(maxX, input.size());
  grid.values.resize(maxX * input.size(), ' ');
  for (int i = 0; i < input.size(); ++i)
  {
    for (int j = 0; j < maxX; ++j)
    {
      if (j < input[i].size() ) grid.setValue(Coord(j, i), input[i][j]);
      else grid.setValue(Coord(j, i), ' ');
    }
  }
  
  Coord currPosition(0,0);
  while (grid.getValue(currPosition) == ' ')
  {
    currPosition.first++;
  }

  int instrIndex = 0;
  int countInstr = -1;
  while (instrIndex < instrucions.size())
  {
    std::string count = "";
    while (std::isdigit(instrucions[instrIndex])) { count.push_back(instrucions[instrIndex++]); }
    countInstr = std::stoi(count);

    for (int i = 0; i < countInstr; ++i)
    {
      Coord auxPosition = getNextPos(currPosition, moveVector[moveIndex], grid);
      if (grid.getValue(auxPosition) == '#')
      {
        break;
      }
      currPosition = auxPosition;
    }
    if (instrucions[instrIndex] == 'R') moveIndex = ( moveIndex + 1 ) % moveVector.size();
    else if (instrucions[instrIndex] == 'L') moveIndex = ( moveIndex - 1 ) % moveVector.size();
    instrIndex++;
  }

  long long result = (1000 * (currPosition.second+1)) + (4 * (currPosition.first+1)) + moveIndex;
  printf("The solution for part 1 is: %lli \n", result);
}

Coord getNextPosCube(const Coord& curr, const std::vector<Coord>& moveV, int& moveIndex, const Grid<char>& grid, const int sizeSide )
{
  Coord result = curr;
  result.first = result.first + moveV[moveIndex].first;
  result.second = result.second + moveV[moveIndex].second;
  if (!grid.isValidCoord(result) || grid.getValue(result) == ' ' )
  {
    if (result.first < 0)
    {
      // Could be 2 -> 1 || 3->1
    }
    if (result.first >= grid.sizeX)
    {
      // 5 -> 6
    }
    //Compute where to move
    if (result.first < 0) result.first = grid.sizeX - 1;
    if (result.first >= grid.sizeX) result.first = 0;
    if (result.second < 0) result.second = grid.sizeY - 1;
    if (result.second >= grid.sizeY) result.second = 0;
  }
  return result;
}


void day22Part2()
{
  std::vector<std::string> input;
  readDocument(DAY22_TEST_PATH, input);

  int moveIndex = 0;
  std::vector<Coord> moveVector = { {1,0}, {0,1}, {-1,0}, {0,-1} };
  std::vector<int> moveX = { 1, 0, -1, 0 };
  std::vector<int> moveY = { 0, 1, 0, -1 };

  std::string instrucions = input.back();
  input.pop_back(); input.pop_back();

  size_t maxX = std::numeric_limits<size_t>::min();
  std::for_each(input.begin(), input.end(), [&maxX] (const std::string& s) { maxX = std::max(maxX, s.size()); });
  
  Grid<char> grid(maxX, input.size());
  grid.values.resize(maxX * input.size(), ' ');
  for (int i = 0; i < input.size(); ++i)
  {
    for (int j = 0; j < maxX; ++j)
    {
      if (j < input[i].size() ) grid.setValue(Coord(j, i), input[i][j]);
      else grid.setValue(Coord(j, i), ' ');
    }
  }

  size_t sizeSide = std::max(maxX, input.size()) / 4;
  
  Coord currPosition(0,0);
  while (grid.getValue(currPosition) == ' ')
  {
    currPosition.first++;
  }

  int instrIndex = 0;
  int countInstr = -1;
  while (instrIndex < instrucions.size())
  {
    std::string count = "";
    while (std::isdigit(instrucions[instrIndex])) { count.push_back(instrucions[instrIndex++]); }
    countInstr = std::stoi(count);

    for (int i = 0; i < countInstr; ++i)
    {
      Coord auxPosition = getNextPosCube(currPosition, moveVector, moveIndex, grid, sizeSide);
      char aux = grid.getValue(auxPosition);
      while (aux == ' ')
      {
        auxPosition = getNextPosCube(auxPosition, moveVector, moveIndex, grid, sizeSide);
        aux = grid.getValue(auxPosition);
      }
      if (aux == '#')
      {
        break;
      }
      currPosition = auxPosition;
    }
    if (instrucions[instrIndex] == 'R') moveIndex = ( moveIndex + 3 ) % moveX.size();
    else if (instrucions[instrIndex] == 'L') moveIndex = ( moveIndex + 1 ) % moveX.size();
    instrIndex++;
  }


  long long result = ( 1000 * ( currPosition.second + 1 ) ) + ( 4 * ( currPosition.first + 1 ) ) + moveIndex;
  printf("The solution for part 2 is: %lli \n", result);
}

