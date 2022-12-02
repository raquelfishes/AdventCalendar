#include "std_includes.h"
#include "resource.h"


void day1Part1()
{
  // Open numbers file
  std::ifstream myfile( DAY1_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file founded" << std::endl;
    return;
  }

  std::vector<long long> nums;
  std::string number;
  long long auxNumber = 0;
  while ( getline( myfile, number ) )
  {  //read data from file object and put it into string.
    if ( number.empty() )
    {
      nums.push_back( auxNumber );
      auxNumber = 0;
      continue;
    }
    auxNumber += std::stoi( number );
  }
  if ( auxNumber != 0 )
    nums.push_back( auxNumber );

  if ( nums.empty() )
  {
    std::cout << "Error, no binary numbers at file" << std::endl;
  }

  // Part 1:
  std::vector<long long> higher = {nums.front()};
  int maxSize = 1;
  for ( auto& num : nums )
  {
    if ( num > higher.back() )
    {
      higher.pop_back();
      higher.push_back( num );
    }
  }
 
  
  long long result = higher.back();
  printf("The solution for part 1 is: %i \n", result);
}


void day1Part2()
{
  // Open numbers file
  std::ifstream myfile( DAY1_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file founded" << std::endl;
    return;
  }

  std::vector<long long> nums;
  std::string number;
  long long auxNumber = 0;
  while ( getline( myfile, number ) )
  {  //read data from file object and put it into string.
    if ( number.empty() )
    {
      nums.push_back( auxNumber );
      auxNumber = 0;
      continue;
    }
    auxNumber += std::stoi( number );
  }
  if ( auxNumber != 0 )
    nums.push_back( auxNumber );

  if ( nums.empty() )
  {
    std::cout << "Error, no binary numbers at file" << std::endl;
    return;
  }

  if ( nums.size() < 3 )
  {
    std::cout << "Error, no enough inputs at file" << std::endl;
    return;
  }

  // Part 1:
  std::vector<long long> higher;
  int maxSize = 3;
  for ( auto& num : nums )
  {
    if ( higher.size() < maxSize || num > higher.back() )
    {
      if (higher.size() == maxSize )
        higher.pop_back();

      higher.push_back( num );
      std::sort( higher.begin(), higher.end(), std::greater<int>() );
    }
  }

  
  long long result = std::accumulate(higher.begin(), higher.end(), 0 );
  printf("The solution for part 2 is: %i \n", result);
}
