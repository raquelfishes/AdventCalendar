#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <numeric>
#include <limits>

#include "resource.h"


bool validSum( std::vector<long long>& numbers, const long long value )
{
  for ( auto i = 0; i < numbers.size(); ++i )
  {
    for ( auto j = 0; j < numbers.size(); ++j )
    {
      if ( numbers[i] + numbers[j] == value )
        return true;
    }
  }
  return false;
}

void adventDay9()
{
  // Open numbers file
  std::ifstream myfile( FILE_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file found" << std::endl;
    return;
  }

  
  std::vector<long long> numbers;
  std::string line;
  std::smatch sm;
  auto aux = std::numeric_limits<long long>::max();
  while ( getline( myfile, line ) )
  { 
    numbers.push_back( std::stoll(line) );
  }
  if ( numbers.empty() )
  {
    std::cout << "Error, no numbers at file" << std::endl;
  }
  
  constexpr int preamble = 25;
  int wrongNumber;
  
  for ( auto i = preamble; i < numbers.size(); ++i )
  {
    std::vector<long long> subNumbers( numbers.begin() + i - preamble, numbers.begin() + i );
    if ( !validSum( subNumbers, numbers[i] ) )
    {
      wrongNumber = numbers[i];
      break;
    }
  }

  std::cout << "Part1: The first incorrect number is: " << wrongNumber << std::endl;


  long long encrypWeakness = 0;
  for ( auto i = 0; i < numbers.size(); ++i )
  {
    long long minWeak = std::numeric_limits<long long>::max();
    long long maxWeak = std::numeric_limits<long long>::min();
    long long sum = 0;
    for ( auto j = i; j < numbers.size(); ++j )
    {
      sum += numbers[j];
      minWeak = std::min( minWeak, numbers[j] );
      maxWeak = std::max( maxWeak, numbers[j] );
      if ( sum >= wrongNumber)
      {
        break;
      }
    }
    if ( sum == wrongNumber )
    {
      encrypWeakness = minWeak + maxWeak;
      break;
    }
  }
  
  std::cout << "Part2: The encryption weakness is: " << encrypWeakness << std::endl;


}



int main( int argc, char* argv[] )
{
  adventDay9();
}
