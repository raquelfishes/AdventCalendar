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

uint64_t applyMask( const std::string& mask, const std::string value )
{
  uint64_t originalValue = std::stoull( value );
  for ( auto i = 0; i < mask.size(); ++i )
  {
    uint64_t auxIndex = mask.size()-1 - i;
    const uint64_t auxMask{ static_cast<uint64_t>(1) << static_cast<uint64_t>( i ) };
    if ( mask[auxIndex] == '1' )
    {
      originalValue |= auxMask;
    }
    else if ( mask[auxIndex] == '0' )
    {
      originalValue &= ~(auxMask);
    }
  }
  return originalValue;
}


void adventDay14()
{
  // Open numbers file
  std::ifstream myfile( FILE_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file found" << std::endl;
    return;
  }

  std::vector<std::string> instructions;
  std::string line;
  while ( getline( myfile, line ) )
  {
    instructions.push_back( line );
  }
  
  if ( instructions.empty() )
  {
    std::cout << "Error, no bus lines at file" << std::endl;
    return;
  }
  

  //mask = 00111X0X10X0000XX00011111110000011X0
  std::regex maskExpr( "mask = (\\w+)" );
  //mem[43834] = 524429393
  std::regex memExpr( "mem\\[(\\d+)\\] = (\\d+)" );
  std::smatch sm;
  std::map<uint64_t, uint64_t> memory;
  std::string currentMask = "";
  for ( auto& instr : instructions )
  {
    if ( std::regex_search( instr, sm, maskExpr ) )
    {
      currentMask = sm[1];
    }
    else if ( std::regex_search( instr, sm, memExpr ) )
    {
      memory[std::stoull( sm[1].str() )] = applyMask( currentMask, sm[2].str() );
    }
  }
  uint64_t result = 0;
  for ( auto& mem : memory )
  {
    result += mem.second;
  }
  std::cout << "Part1: The result is: " << result << std::endl;

  
  std::cout << "Par2: The result is: " << result << std::endl;

}



int main( int argc, char* argv[] )
{
  adventDay14();
}
