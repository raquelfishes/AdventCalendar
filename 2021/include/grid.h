#pragma once


#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>


typedef std::pair<int, int> coord;


template<typename T>
class Grid 
{

public: 
  Grid() = default;
  Grid( std::vector<std::string> strValues )
  {
    sizeX = strValues[0].size();
    sizeY = strValues.size();

    const int numValues = sizeX * sizeY;
    values.reserve( numValues );
    visited.resize( numValues, false );
    for ( auto& line : strValues )
    {
      for ( auto & col : line )
      {
        values.push_back( char2int( col ) );
      }
    }
  }

  coord getXY( const int index )
  {
    return std::pair<int, int>( ( index%sizeX ), ( index / sizeX ) );
  }

  int getIndex( const coord c )
  {
    return getIndex( c.first, c.second );
  }

  int getIndex( const int x, const int y )
  {
    return x + y * sizeX;
  }

  bool isValidCoord( const coord c )
  {
    return isValidCoord(c.first, c.second);
  }

  bool isValidCoord( const int x, const int y )
  {
    bool validX = ( 0 <= x && x <= sizeX - 1 );
    bool validY = ( 0 <= y && y <= sizeY - 1 );

    return validX && validY;
  }

  bool isValidIndex( const int index )
  {
    return ( index >= 0 ) && ( index < ( sizeX*sizeY ) );
  }

  void printGrid()
  {
    for ( int i = 0; i < sizeX; ++i )
    {
      for ( int j = 0; j < sizeY; ++j )
      {
        int index = getIndex( coord( j, i ) );
        if ( values[index] == 0 )
          printf( "." );
        else
          printf( "%d", values[index] );
      }
      printf( "\n" );
    }
    printf( "\n" );
    printf( "\n" );
  }

public:

  int sizeX;
  int sizeY;
  std::vector<T> values;
  std::vector<bool> visited;
};


typedef Grid<int> GridI;


