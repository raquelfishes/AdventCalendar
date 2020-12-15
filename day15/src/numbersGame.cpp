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

#include "resource.h"


void adventDay15()
{
  // Open numbers file
  std::ifstream myfile( FILE_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file found" << std::endl;
    return;
  }

  std::vector<int> numbers;
  std::string line;
  getline( myfile, line );

  std::stringstream ss( line );
  std::string value;
  std::vector<std::string> values;
  while ( getline( ss, value, ',' ) )
  {
    numbers.push_back( std::stoi( value ) );
  }
  if ( numbers.empty() )
  {
    std::cout << "Error, no bus lines at file" << std::endl;
    return;
  }


  // Optimization using a map
  std::map<int, std::pair<int,int>> numbersMap; // number, <lastIndex, count>
  int counter = 1;
  std::for_each( numbers.begin(), numbers.end(), [&numbersMap, &counter] ( int& number )
  {
    numbersMap[number] = std::pair<int,int>(counter++,1);
  } );


  //for ( auto i = numbers.size(); i < 2020; ++i )
  //{
  //  const int lastNumber = numbers[numbers.size() - 1];
  //  auto found = std::find( numbers.rbegin() + 1, numbers.rend(), lastNumber );
  //  if ( found == numbers.rend() )
  //  {
  //    numbers.push_back( 0 );
  //  }
  //  else
  //  {
  //    auto index = ( numbers.rend() - found );
  //    numbers.push_back( i - index );
  //  }
  //}  
  //std::cout << "Par1: The result is: " << numbers[2019] << std::endl;

  constexpr int part1Index = 2020;
  constexpr int part2Index = 30000000;

  for ( auto i = numbers.size(); i < part2Index; ++i )
  {
    const int lastNumber = numbers[numbers.size() - 1];
    auto found = numbersMap.find( lastNumber );
    if ( found->second.second <= 1 )
    {
      numbers.push_back( 0 );
      ++numbersMap[0].second;
    }
    else
    {
      auto index = numbersMap[lastNumber].first;
      numbers.push_back( i - index );
      ++numbersMap[i - index].second;
    }
    numbersMap[lastNumber].first = i;
  }

  std::cout << "Par1: The result is: " << numbers[part1Index-1] << std::endl;
  std::cout << "Par2: The result is: " << numbers[part2Index-1] << std::endl;

}



int main( int argc, char* argv[] )
{
  adventDay15();
}
