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

void addToDirection( const char dir, const int value, std::pair<int, int>& pos )
{
  switch ( dir )
  {
  case 'E':
    pos.first += value;
    break;
  case 'S':
    pos.second -= value;
    break;
  case 'W':
    pos.first -= value;
    break;
  case 'N':
    pos.second += value;
    break;
  default:
    break;
  }
}

void adventDay12()
{
  // Open numbers file
  std::ifstream myfile( FILE_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file found" << std::endl;
    return;
  }

  
  std::vector<std::pair<char,int>> directions;
  std::string line;
  std::regex expr( "(\\w)(\\d+)" );
  std::smatch sm;
  while ( getline( myfile, line ) )
  { 
    if ( std::regex_search( line, sm, expr ) )
    {
      std::pair<char, int> myPair( sm[1].str().c_str()[0], std::stoi(sm[2].str()) );
      directions.push_back( myPair );
    }
  }
  if ( directions.empty() )
  {
    std::cout << "Error, no numbers at file" << std::endl;
    return;
  }
  
  const std::vector<char> cardinalDirections = { 'E', 'S', 'W', 'N' };

  // Add final adapter
  int currentDir = 0; // 0 is the East index at cardinalDirections
  std::pair<int, int> currentPos( 0, 0 ); // Positive values E,N
  for ( auto& dir : directions )
  {
    if ( std::find( cardinalDirections.begin(), cardinalDirections.end(), dir.first ) != cardinalDirections.end() )
    {
      addToDirection( dir.first, dir.second, currentPos );
    }
    if ( dir.first == 'F' )
    {
      addToDirection( cardinalDirections[currentDir], dir.second, currentPos );
    }
    else if ( dir.first == 'R' )
    {
      currentDir = ( currentDir + dir.second / 90 ) % cardinalDirections.size();
    }
    else if ( dir.first == 'L' )
    {
      currentDir = ( currentDir - dir.second / 90 ) % cardinalDirections.size();
    }
  }

  const int result = std::abs( currentPos.first ) + std::abs( currentPos.second );
  std::cout << "Part1: The result is: " << result << std::endl;

 

  // We need to check the length of 1's 
  // Valid combination is sum(0:1s lengths - 1) + 1
  // 1 = sum (0:1-1) +1 = sum(0:0) + 1 = 0+1 = 1
  // 2 = sum(0:2-1)+1 = sum(0:1)+1 = 1+1 =2
  // 3 = sum(0:3-1)+1 = sum(0:2)+1 = 1+2+1 = 4
  // 4 = sum(0:4-1)+1 = sum(0:3)+1 = 1+2+3+1 = 7
  // .....
  // e. 313 = 1 valid combi | 3113 = 2 valid combi | 31113 = 4 valid combi | 311113 = 7 valid combi
  // 1 * 2 * 4 * 1 * ... 

}



int main( int argc, char* argv[] )
{
  adventDay12();
}
