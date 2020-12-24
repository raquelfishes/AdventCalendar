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


std::pair<int, int> getCoord( std::string coord )
{
  std::pair<int, int> result( 0, 0 );
  while ( !coord.empty() )
  {
    if ( coord.front() == 's' )
    {
      result.second -= 1;
      coord.erase( coord.begin() );
      if ( coord.front() == 'e' )
      {
        result.first += 1;
        coord.erase( coord.begin() );
      }
      else if ( coord.front() == 'w' )
      {
        result.first -= 1;
        coord.erase( coord.begin() );
      }
    }
    else if ( coord.front() == 'n' )
    {
      result.second += 1;
      coord.erase( coord.begin() );
      if ( coord.front() == 'e' )
      {
        result.first += 1;
        coord.erase( coord.begin() );
      }
      else if ( coord.front() == 'w' )
      {
        result.first -= 1;
        coord.erase( coord.begin() );
      }
    }
    else if ( coord.front() == 'e' )
    {
      result.first += 2;
      coord.erase( coord.begin() );
    }
    else if ( coord.front() == 'w' )
    {
      result.first -= 2;
      coord.erase( coord.begin() );
    }
  }
  return result;
}


int checkBlackNeis( const std::pair<int, int>& coord, std::map<std::pair<int, int>, bool>& field )
{
  int result = 0;
  if ( field.find( std::pair<int, int>( coord.first + 2, coord.second ) ) != field.end() )
  {
    result += field.at( std::pair<int, int>( coord.first + 2, coord.second ) );
  }
  if ( field.find( std::pair<int, int>( coord.first - 2, coord.second ) ) != field.end() )
  {
    result += field.at( std::pair<int, int>( coord.first - 2, coord.second ) );
  }
  if ( field.find( std::pair<int, int>( coord.first + 1, coord.second + 1 ) ) != field.end() )
  {
    result += field.at( std::pair<int, int>( coord.first + 1, coord.second + 1 ) );
  }
  if ( field.find( std::pair<int, int>( coord.first + 1, coord.second - 1 ) ) != field.end() )
  {
    result += field.at( std::pair<int, int>( coord.first + 1, coord.second - 1 ) );
  }
  if ( field.find( std::pair<int, int>( coord.first - 1, coord.second + 1 ) ) != field.end() )
  {
    result += field.at( std::pair<int, int>( coord.first - 1, coord.second + 1 ) );
  }
  if ( field.find( std::pair<int, int>( coord.first - 1, coord.second - 1 ) ) != field.end() )
  {
    result += field.at( std::pair<int, int>( coord.first - 1, coord.second - 1 ) );
  }
  return result;
}

void addAllNeis( std::map<std::pair<int, int>, bool>& field )
{
  std::map<std::pair<int, int>, bool> auxMap( field );
  for ( auto& tile : field )
  {
    if ( field.find( std::pair<int, int>( tile.first.first + 2, tile.first.second ) ) == field.end() )
    {
      auxMap[std::pair<int, int>( tile.first.first + 2, tile.first.second )] = false;
    }
    if ( field.find( std::pair<int, int>( tile.first.first - 2, tile.first.second ) ) == field.end() )
    {
      auxMap[std::pair<int, int>( tile.first.first - 2, tile.first.second )] = false;
    }
    if ( field.find( std::pair<int, int>( tile.first.first + 1, tile.first.second+1 ) ) == field.end() )
    {
      auxMap[std::pair<int, int>( tile.first.first + 1, tile.first.second+1 )] = false;
    }
    if ( field.find( std::pair<int, int>( tile.first.first + 1, tile.first.second-1 ) ) == field.end() )
    {
      auxMap[std::pair<int, int>( tile.first.first + 1, tile.first.second-1 )] = false;
    }
    if ( field.find( std::pair<int, int>( tile.first.first -1, tile.first.second+1 ) ) == field.end() )
    {
      auxMap[std::pair<int, int>( tile.first.first -1, tile.first.second+1 )] = false;
    }
    if ( field.find( std::pair<int, int>( tile.first.first - 1, tile.first.second -1) ) == field.end() )
    {
      auxMap[std::pair<int, int>( tile.first.first - 1, tile.first.second-1 )] = false;
    }
  }
  field = auxMap;
}

void adventDay22()
{
  // Open numbers file
  std::ifstream myfile( FILE_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file found" << std::endl;
    return;
  }

  std::vector<std::string> tiles;
  std::string line;
  std::regex expr( "Player (\\d+):" );
  std::smatch sm;
  int playerId = -1;
  while ( getline( myfile, line ) )
  {
    tiles.push_back( line );
  }
  if ( tiles.empty() )
  {
    std::cout << "No valid input file" << std::endl;
  }
  
  std::map<std::pair<int, int>, bool> tileField; // pair is 0,0 , bool = false(white), bool = true(black)

  for ( auto& tile : tiles )
  {
    std::pair<int, int> tileCoord = getCoord( tile );
    if ( tileField.find( tileCoord ) != tileField.end() )
    {
      tileField[tileCoord] = !tileField[tileCoord];
    }
    else
    {
      tileField[tileCoord] = true;
    }
  }

  int result = 0;
  for ( auto& tile : tileField )
  {
    if ( tile.second )
    {
      result++;
    }
  }
  std::cout << "Part 1:  " << result << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  
  for ( int i = 0; i < 100; ++i )
  {
    addAllNeis( tileField );
    std::map<std::pair<int, int>, bool> auxMap( tileField );
    for ( auto& tile : tileField )
    {
      int blackNeis = checkBlackNeis( tile.first, tileField );
      if ( tile.second && ( blackNeis == 0 || blackNeis > 2 ) )
      {
        auxMap[tile.first] = false;
      }
      if ( !tile.second && blackNeis == 2 )
      {
        auxMap[tile.first] = true;
      }
    }
    tileField = auxMap;
  }

  result = 0;
  for ( auto& tile : tileField )
  {
    if ( tile.second )
    {
      result++;
    }
  }
  std::cout << "Part 2:  " << result << std::endl;
  //std::cout << "Part 2:" << result << std::endl;

}



int main( int argc, char* argv[] )
{
  adventDay22();
}
