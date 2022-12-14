#pragma once


#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>


typedef std::pair<int, int> Coord;


template<typename T>
class Grid 
{

public: 
  Grid() = default;

  //Grid( std::vector<std::string> strValues )
  //{
  //  sizeX = strValues[0].size();
  //  sizeY = strValues.size();
  //
  //  const int numValues = sizeX * sizeY;
  //  values.reserve( numValues );
  //  visited.resize( numValues, false );
  //  for ( auto& line : strValues )
  //  {
  //    for ( auto & col : line )
  //    {
  //      values.push_back( char2int( col ) );
  //    }
  //  }
  //}

  Grid( const int sX, const int sY )
  {
    sizeX = sX;
    sizeY = sY;
    const int numValues = sizeX * sizeY;
    values.resize( numValues );
    visited.resize( numValues, false );
    visitedSteps.resize( numValues, -1 );
  }

  void initializeToInt( std::vector<std::string>& strValues )
  {
    sizeX = strValues[0].size();
    sizeY = strValues.size();

    const int numValues = sizeX * sizeY;
    values.reserve( numValues );
    visited.resize( numValues, false );
    visitedSteps.resize( numValues, -1 );
    for ( auto& line : strValues )
    {
      for ( auto & col : line )
      {
        values.push_back( char2int( col ) );
      }
    }
  }

  void initializeToChar( std::vector<std::string>& strValues )
  {
    sizeX = strValues[0].size();
    sizeY = strValues.size();

    const int numValues = sizeX * sizeY;
    values.reserve( numValues );
    visited.resize( numValues, false );
    visitedSteps.resize( numValues, -1 );
    for ( auto& line : strValues )
    {
      for ( auto & col : line )
      {
        values.push_back( charLowerCase2int(col) );
      }
    }
  }

  Coord getXY( const int index )
  {
    return std::pair<int, int>( ( index%sizeX ), ( index / sizeX ) );
  }

  int getIndex( const Coord c )
  {
    return getIndex( c.first, c.second );
  }

  int getIndex( const int x, const int y )
  {
    return x + y * sizeX;
  }

  bool isValidCoord( const Coord c )
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

  bool isDiagonal( const Coord p1, const Coord p2 )
  {
    return isDiagonal( p1.first, p1.second, p2.first, p2.second );
  }

  bool isDiagonal( const int x1, const int y1, const int x2, const int y2 )
  {
    return ( std::abs( x1 - x2 ) && std::abs( y1 - y2 ) );
  }

  T getValue( const Coord p )
  {
    return values[getIndex( p )];
  }

  T getValue( const int id )
  {
    return values[id];
  }

  void setValue( const Coord p, const T v)
  {
    values[getIndex( p )] = v;
  }

  void getValue( const int id, const T v )
  {
    values[id] = v;
  }

  void printGrid()
  {
    for ( int i = 0; i < sizeY; ++i )
    {
      for ( int j = 0; j < sizeX; ++j )
      {
        int index = getIndex( Coord( j, i ) );
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
  std::vector<int> visitedSteps;
};


typedef Grid<int> GridI;
typedef Grid<int> GridI;


