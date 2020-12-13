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

  int time = 0;
  std::vector<int> busDiffTime;
  std::vector<int> busIds;
  while ( getline( ss, value, ',' ) )
  {
    if ( value != "x" )
    {
      busIds.push_back( std::stoi( value ) );
      busDiffTime.push_back( time );
    }
    time++;
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

  //// Yes, I tried to make it by force
  //auto maxBus = std::max_element( busIds.begin(), busIds.end() );
  //auto maxBusId = std::distance( busIds.begin(), maxBus );
  //currentTime = busIds[maxBusId]-busDiffTime[maxBusId];
  //bool sequenceNotFound = false;
  //while ( !sequenceNotFound )
  //{
  //  for ( auto i=0; i< busIds.size(); ++i )
  //  {
  //    sequenceNotFound = true;
  //    if (( currentTime + busDiffTime[i]) % busIds[i] != 0 )
  //    {
  //      sequenceNotFound &= false;
  //      break;
  //    }
  //  }
  //  if ( !sequenceNotFound )
  //  {
  //    currentTime+= busIds[maxBusId];
  //  }
  //  
  //}

  long long step = busIds[0];
  currentTime = 0;
  for ( auto i=1; i< busIds.size(); ++i )
  {
    while ( ( currentTime + busDiffTime[i] ) % busIds[i] != 0 )
    {
      currentTime += step;
    }
    step *= busIds[i];
  }
  std::cout << "Par2: The result is: " << currentTime << std::endl;

}



int main( int argc, char* argv[] )
{
  adventDay13();
}
