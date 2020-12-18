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

long long evaluate( std::string& operation )
{

}

void adventDay18()
{
  // Open numbers file
  std::ifstream myfile( FILE_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file found" << std::endl;
    return;
  }

  std::vector<std::string> operations;
  std::string line;
  int countX = 0;
  while ( getline( myfile, line ) )
  {
    // Remove whitespace from operation
    std::remove( line.begin(), line.end(), ' ' );
    std::string reverseLine;
    std::for_each( line.rbegin(), line.rend(), [&reverseLine]( const char& c ) 
    {
      if ( c == ')' ) reverseLine.push_back( '(' );
      else if ( c == '(' ) reverseLine.push_back( ')' );
      else reverseLine.push_back( c );
    } );
    operations.push_back( reverseLine );
  }
  if ( operations.empty() )
  {
    std::cout << "Error, no valid input file" << std::endl;
    return;
  }

  long long result = 0;
  std::for_each( operations.begin(), operations.end(), [&result]( std::string& operation )
  {
    result += evaluate( operation );
  } );

  std::cout << "Part 1:" << result << std::endl;
  
  //std::cout << "Part 2:" << result << std::endl;
  //std::cout << "Part 2:" << result << std::endl;

}



int main( int argc, char* argv[] )
{
  adventDay18();
}
