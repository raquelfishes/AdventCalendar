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


void adventDay13()
{
  // Open numbers file
  std::ifstream myfile( FILE_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file found" << std::endl;
    return;
  }

  std::string line;
  getline( myfile, line );
  const long long originalTime = std::stoll(line);

  getline( myfile, line );
  std::stringstream ss( line );
  std::string value;

  std::vector<std::string> busLine;
  std::vector<int> busIds;
  while ( getline( ss, value, ',' ) )
  {
    if ( value != "x" )
    {
      busIds.push_back( std::stoi( value ) );
    }
    busLine.push_back( value );
  }
  
  if ( busIds.empty() )
  {
    std::cout << "Error, no bus lines at file" << std::endl;
    return;
  }
  
  bool busNotFound = true;
  long long currentTime = originalTime;
  int usedBus = -1;
  while ( busNotFound )
  {
    for ( auto& busId : busIds )
    {
      if ( currentTime % busId == 0 )
      {
        busNotFound = false;
        usedBus = busId;
        break;
      }
    }
    if ( busNotFound )
    {
      currentTime++;
    }
  }

  if ( usedBus == -1 )
  {
    std::cout << "Error, no bus found" << std::endl;
  }
  const int result = ( currentTime - originalTime ) * usedBus;
  std::cout << "Part1: The result is: " << result << std::endl;


  std::cout << "Par2: The result is: " << result << std::endl;

}



int main( int argc, char* argv[] )
{
  adventDay13();
}
