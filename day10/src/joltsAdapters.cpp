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


bool validAdapters( const std::vector<int>&adapters, int initialJolt, const int finalJolt )
{
  for ( auto i = 0; i < adapters.size(); ++i )
  {
    if ( adapters[i] - initialJolt <= 3 )
      initialJolt = adapters[i];
    else
      return false;
  }

  if ( finalJolt - initialJolt <= 3 )
    return true;

  return false;
}


void adventDay10()
{
  // Open numbers file
  std::ifstream myfile( FILE_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file found" << std::endl;
    return;
  }

  
  std::vector<int> adapters;
  std::string line;
  while ( getline( myfile, line ) )
  { 
    adapters.push_back( std::stoll(line) );
  }
  if ( adapters.empty() )
  {
    std::cout << "Error, no numbers at file" << std::endl;
    return;
  }
  
  std::sort( adapters.begin(), adapters.end() );
  if ( adapters[0] > 3 )
  {
    std::cout << "Error, the lowest adapter is higher than 3" << std::endl;
    return;
  }

  // Add final adapter
  const int finalAdapter = adapters[adapters.size() - 1] + 3;
  adapters.push_back( finalAdapter );
  int currentJolt = 0;
  std::vector<int>difference(adapters.size());
  for ( auto i = 0; i < adapters.size(); ++i )
  {
    difference[i] = adapters[i] - currentJolt;
    currentJolt = adapters[i];
  }

  int result = std::count(difference.begin(), difference.end(), 1 ) * std::count( difference.begin(), difference.end(), 3 );
  std::cout << "Part1: The result is: " << result << std::endl;

  
  currentJolt = 0;
  long long validCombination = 1; // At least we have the original valid combination

  // We need to check the length of 1's 
  // Valid combination is sum(0:1s lengths - 1) + 1
  // e. 313 = 1valid combi | 3113 = 2 valid combi | 31113 = 4 valid combi | 311113 = 7 valid combi
  for ( auto i = 0; i < difference.size(); ++i )
  {
    if ( difference[i] == 1 )
    {
      int numberOf1s = 0;
      for ( auto j = i; j < difference.size(); ++j )
      {
        if ( difference[j] == 1 )
          numberOf1s++;
        else
          break;
      }

      int sumOf1s = 0;
      for ( auto aux = 1; aux < numberOf1s; ++aux )
      {
        sumOf1s += aux;
      }
      sumOf1s++;

      validCombination *= sumOf1s;
      i += numberOf1s - 1;
    }
  }
  //int combinations = validCombination( adapters, 0, 0, finalAdapter );
  std::cout << "Part2: The number of valid adapter combinations are: " << validCombination << std::endl;


}



int main( int argc, char* argv[] )
{
  adventDay10();
}
