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
  //std::cout << " (" << curr.second+1 << ", " << curr.first+1 << ") || ";
  Coord result = Coord(curr.first, curr.second);
  result.first = result.first + moveV[moveIndex].first;
  result.second = result.second + moveV[moveIndex].second;
  if (!grid.isValidCoord(result) || grid.getValue(result) == ' ' )
  {
    //std::cout << "From: " << curr.first << ", " << curr.second;
    int cubeX = curr.first / sizeSide;
    int cubeY = curr.second / sizeSide;

    int x = curr.first % sizeSide;
    int y = curr.second % sizeSide;

    if( cubeY == 0 && cubeX == 1 )
    {
      if( moveIndex == moveDir::UP )
      {
        result.second = (sizeSide*3) + x;
      }
      else
      {
        result.second = ( sizeSide * 3 ) - 1 - y;
      }
      moveIndex = moveDir::RIGHT;
      result.first = 0;
    }
    else if( cubeY == 0 && cubeX == 2 )
    {
      if( moveIndex == moveDir::UP )
      {
        // moveIndex doesn't change
        result.first = x ;
        result.second = grid.sizeY - 1;
      }
      else if( moveIndex == moveDir::RIGHT )
      {
        moveIndex = moveDir::LEFT;
        result.first = (sizeSide * 2) - 1;
        result.second = (sizeSide*3) - 1 - y ;
      }
      else
      {
        moveIndex = moveDir::LEFT;
        result.first = ( sizeSide * 2 ) - 1;
        result.second = sizeSide + x;
      }
    }
    else if( cubeX == 1 && cubeY == 1 )
    {
      if( moveIndex == moveDir::RIGHT )
      {
        moveIndex = moveDir::UP;
        result.first = (sizeSide * 2) + y;
        result.second = sizeSide - 1;
      }
      else
      {
        moveIndex = moveDir::DOWN;
        result.first = y;
        result.second = (sizeSide * 2);
      }
    }
    else if( cubeY == 2 && cubeX == 0 )
    {
      if( moveIndex == moveDir::LEFT )
      {
        result.second = sizeSide - 1 - y;
      }
      else
      {
        result.second = sizeSide + x;
      }
      moveIndex = moveDir::RIGHT;
      result.first = sizeSide;
    }
    else if( cubeY == 2 && cubeX == 1 )
    {
      if( moveIndex == moveDir::RIGHT )
      {
        // moveIndex doesn't change
        result.first = grid.sizeX - 1;
        result.second = sizeSide - 1 - y;
      }
      else
      {
        result.first = sizeSide-1;
        result.second = ( sizeSide * 3 ) + x;
      }
      moveIndex = moveDir::LEFT;
    }
    else if( cubeX == 0 && cubeY == 3 )
    {
      if( moveIndex == moveDir::LEFT )
      {
        moveIndex = moveDir::DOWN;
        result.second = 0;
        result.first = sizeSide + y;
      }
      else if( moveIndex == moveDir::RIGHT )
      {
        moveIndex = moveDir::UP;
        result.second = ( sizeSide * 3 ) - 1;
        result.first = sizeSide + y;
      }
      else
      {
        result.second = 0;
        result.first = (sizeSide*2) + x;
      }
    }
    //std::cout << " || To: " << result.first << ", " << result.second << std::endl;
  }
  return result;
}

void day22Part2()
{
  std::vector<std::string> input;
  readDocument(DAY22_PATH, input);

  int moveIndex = 0;

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
      int auxMoveIndex = moveIndex;
      Coord auxPosition = getNextPosCube(currPosition, moveVector, auxMoveIndex, grid, sizeSide);
      if( grid.getValue( auxPosition ) == '#' )
      {
        break;
      }
      currPosition = auxPosition;
      moveIndex = auxMoveIndex;
    }
    if (instrucions[instrIndex] == 'R') moveIndex = ( moveIndex + 1 ) % moveVector.size();
    else if (instrucions[instrIndex] == 'L') moveIndex = ( moveIndex - 1 ) % moveVector.size();
    instrIndex++;
  }


  long long result = ( 1000 * ( currPosition.second + 1 ) ) + ( 4 * ( currPosition.first + 1 ) ) + moveIndex;
  printf("The solution for part 2 is: %lli \n", result);
}
