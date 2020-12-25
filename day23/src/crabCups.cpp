#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <regex>
#include <numeric>
#include <limits>

#include "resource.h"

// 418976235

#define MOVES 100

auto foundItCup( const int desiredCup, const std::list<int>& cups )
{
  auto found = std::find( cups.begin(), cups.end(), desiredCup );
  if ( found != cups.end() )
  {
    return found;
  }
  else
  {
    if ( (desiredCup - 1) > 0 )
    {
      return foundItCup( desiredCup - 1, cups );
    }
    else
    {
      return foundItCup( 9, cups );
    }
  }
}

void adventDay23()
{
  // Open numbers file
  std::ifstream myfile( FILE_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file found" << std::endl;
    return;
  }


  std::list<int> cups;

  std::string line;
  getline( myfile, line );
  for ( auto i : line )
  {
    cups.push_back( i-'0' );
  }
  if ( cups.empty() )
  {
    std::cout << "No valid file input" << std::endl;
  }
  
  for ( int i = 0; i < MOVES; ++i )
  {
    std::cout << "--move " << i << " --" << std::endl;
    const int currentCup = cups.front();
    cups.pop_front();

    std::list<int> pick;
    auto it = cups.begin();
    std::advance( it, 3 );
    pick.splice( pick.begin(), cups, cups.begin(), it );

    auto found = foundItCup( currentCup-1, cups );
    std::advance( found, 1 ); // Insert back found, not before
    cups.splice( found, pick );
    cups.push_back( currentCup );    
  }

  auto foundOne = std::find( cups.begin(), cups.end(), 1 );
  std::advance( foundOne, 1 );
  std::string result = std::accumulate( std::next( foundOne ), cups.end(),
                                        std::to_string( *foundOne ), []( std::string a, int b ) {
    return std::move( a ) + std::to_string( b );
  } );
  
  result += std::accumulate( std::next( cups.begin() ), std::prev(foundOne),
                             std::to_string( *cups.begin() ), []( std::string a, int b ) {
    return std::move( a ) + std::to_string( b );
  } );



  std::cout << "Part 1:  " << result << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  
  

  //std::cout << "Part 2:  " << result << std::endl;
  //std::cout << "Part 2:" << result << std::endl;

}



int main( int argc, char* argv[] )
{
  adventDay23();
}
