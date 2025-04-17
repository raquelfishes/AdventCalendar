#include "sonar_sweep.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <regex>

#include "resource.h"

static const int boardSize = 5;

struct board
{
  int value[5][5];
};

bool checkHasLine(const board& b, const int x, const int y)
{
  int count = 0;
  // Check row
  for (int i = 0; i < boardSize; ++i)
  {
    if (b.value[x][i] != -1)
    {
      break;
    }
    ++count;
  }
  if (count == 5)
    return true;

  // Check col
  count = 0;
  for (int i = 0; i < boardSize; ++i)
  {
    if (b.value[i][y] != -1)
    {
      break;
    }
    ++count;
  }
  return count == 5;
}

bool hasWinBoard(const int num, board& b)
{
  for (int i = 0; i < boardSize; ++i)
  {
    for (int j = 0; j < boardSize; ++j)
    {
      if (b.value[i][j] == num)
      {
        b.value[i][j] = -1;
        return checkHasLine(b, i, j);
      }
    }
  }
  return false;
}

int sumNoFoundNumbers(const board& b)
{
  int result = 0;
  for (int i = 0; i < boardSize; ++i)
  {
    for (int j = 0; j < boardSize; ++j)
    {
      if (b.value[i][j] != -1)
        result += b.value[i][j];
    }
  }
  return result;
}


void giantSquidPart1()
{
  // Open numbers file
  std::ifstream myfile( DAY4_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file founded" << std::endl;
    return;
  }

  std::vector<int> bingoNumbers;
  std::vector<board> bingoBoards;
  std::string line;
  bool firstLine = true;
  board newBoard;
  int boardLine = 0;
  while ( getline( myfile, line ) )
  {  //read data from file object and put it into string.
    if (firstLine)
    {
      std::stringstream ssRange(line);
      std::string number;
      while (getline(ssRange, number, ','))
      {
        bingoNumbers.push_back(std::stoi(number));
      }
      firstLine = false;
      continue;
    }
    
    
    std::regex expr("\\s*(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)");
    std::smatch sm;
    if (std::regex_search(line, sm, expr))
    {
      newBoard.value[boardLine][0] = std::stoi(sm[1]);
      newBoard.value[boardLine][1] = std::stoi(sm[2]);
      newBoard.value[boardLine][2] = std::stoi(sm[3]);
      newBoard.value[boardLine][3] = std::stoi(sm[4]);
      newBoard.value[boardLine][4] = std::stoi(sm[5]);
      ++boardLine;
    }
    
    if (boardLine == 5)
    {
      boardLine = 0;
      bingoBoards.push_back(newBoard);

    }
  }
  if (bingoBoards.empty() )
  {
    std::cout << "Error, no binary numbers at file" << std::endl;
  }

  // Part 1:
  
  for (auto& num : bingoNumbers)
  {
    for (auto& board : bingoBoards)
    {
      if (hasWinBoard(num, board))
      {
        int boardNumber = sumNoFoundNumbers(board);
        long result = boardNumber * num;
        printf("The solution for part 1 is: %i \n", result);
        return;

      }
    }
  }
}


void giantSquidPart2()
{
  // Open numbers file
  std::ifstream myfile(DAY4_PATH);
  if (!myfile.is_open())
  {
    std::cout << "Error, no file founded" << std::endl;
    return;
  }

  std::vector<int> bingoNumbers;
  std::vector<board> bingoBoards;
  std::string line;
  bool firstLine = true;
  board newBoard;
  int boardLine = 0;
  while (getline(myfile, line))
  {  //read data from file object and put it into string.
    if (firstLine)
    {
      std::stringstream ssRange(line);
      std::string number;
      while (getline(ssRange, number, ','))
      {
        bingoNumbers.push_back(std::stoi(number));
      }
      firstLine = false;
      continue;
    }


    std::regex expr("\\s*(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)");
    std::smatch sm;
    if (std::regex_search(line, sm, expr))
    {
      newBoard.value[boardLine][0] = std::stoi(sm[1]);
      newBoard.value[boardLine][1] = std::stoi(sm[2]);
      newBoard.value[boardLine][2] = std::stoi(sm[3]);
      newBoard.value[boardLine][3] = std::stoi(sm[4]);
      newBoard.value[boardLine][4] = std::stoi(sm[5]);
      ++boardLine;
    }

    if (boardLine == 5)
    {
      boardLine = 0;
      bingoBoards.push_back(newBoard);

    }
  }
  if (bingoBoards.empty())
  {
    std::cout << "Error, no binary numbers at file" << std::endl;
  }

  // Part 1:

  for (auto& num : bingoNumbers)
  {
    for (int i=0; i<bingoBoards.size(); ++i)
    {
      if (hasWinBoard(num, bingoBoards[i]))
      {
        if (bingoBoards.size() == 1)
        {
          int boardNumber = sumNoFoundNumbers(bingoBoards.front());
          long result = boardNumber * num;
          printf("The solution for part 2 is: %i \n", result);
          return;
        }
        bingoBoards.erase(bingoBoards.begin() + i);
        i -= 1;
      }
    }
  }
}
