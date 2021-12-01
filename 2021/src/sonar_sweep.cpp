#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "resource.h"


void sonarSweepPart1()
{
  // Open numbers file
  std::ifstream myfile( FILE_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file founded" << std::endl;
    return;
  }

  std::vector<int> numbers;
  std::string number;
  while ( getline( myfile, number ) )
  {  //read data from file object and put it into string.
    numbers.push_back( std::stoi(number) );
  }
  if ( numbers.empty() )
  {
    std::cout << "Error, no numbers at file" << std::endl;
  }

  // Part 1:
  int count = 0;
  for ( auto i = 0; i < numbers.size(); ++i )
  {
    if (i == 0)
      continue;
    if (numbers[i - 1] < numbers[i])
    {
      ++count;
    }
  }
  printf("The solution for part 1 is: %i \n", count);

}

void sonarSweepPart2()
{
  // Open numbers file
  std::ifstream myfile(FILE_PATH);
  if (!myfile.is_open())
  {
    std::cout << "Error, no file founded" << std::endl;
    return;
  }

  std::vector<int> numbers;
  std::string number;
  while (getline(myfile, number))
  {  //read data from file object and put it into string.
    numbers.push_back(std::stoi(number));
  }
  if (numbers.empty())
  {
    std::cout << "Error, no numbers at file" << std::endl;
  }

  // Part 2:
  int count = 0;
  int prevSum = 0;
  int currentSum = 0;
  for (auto i = 0; i < numbers.size(); ++i)
  {
    if (i < 3)
    {
      continue;
    }
    
    prevSum = numbers[i - 3] + numbers[i - 2] + numbers[i-1];
    currentSum = numbers[i - 2] + numbers[i - 1] + numbers[i];
    if (prevSum < currentSum)
    {
      ++count;
    }

  }
  printf("The solution for part 2 is: %i \n", count);
}
