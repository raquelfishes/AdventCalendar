#include "std_includes.h"
#include "resource.h"
#include "utils.h"
#include "grid.h"

struct Line
{
  Line() = default;
  Line( const std::string& s )
  {
    std::vector<std::string> aux;
    splitStringByString( s, " -> ", aux );
    for ( auto& p : aux )
    {
      std::vector<std::string> aux2;
      splitStringByChar( p, ',', aux2 );
      if ( aux2.size() != 2 ) return;
      Coord c( std::stoi( aux2.front() ), std::stoi( aux2.back() ) );
      points.push_back( c );
    }
  }



  std::vector<Coord> points;
};


void day14Part1()
{
  std::vector<Line> input;
  readDocument<Line>( DAY14_PATH, input );

  int minX = std::numeric_limits<int>::max();
  int minY = std::numeric_limits<int>::max(); 
  int maxX = std::numeric_limits<int>::min();
  int maxY = std::numeric_limits<int>::min();
  minY = 0;
  for ( auto& l : input )
  {
    for ( auto& p : l.points )
    {
      minX = std::min( minX, p.first );
      maxX = std::max( maxX, p.first );
      maxY = std::max( maxY, p.second );
    }
  }

  GridI grid( maxX - minX + 1, maxY + 1 );
  grid.values.resize( grid.visited.size(), 0 );

  for ( auto& l : input )
  {
    Coord prevC( -1, -1 );
    for ( auto& p : l.points )
    {
      p.first = p.first - minX;
      if ( prevC != Coord( -1, -1 ) )
      {
        Coord vector = Coord( p.first - prevC.first, p.second - prevC.second );
        int modV = std::sqrt( std::pow( vector.first, 2 ) + std::pow( vector.second, 2 ) );
        vector = Coord( vector.first / modV, vector.second / modV );
        while ( prevC != p )
        {
          grid.values[grid.getIndex( prevC )] = 1;
          //grid.printGrid();
          prevC.first += vector.first;
          prevC.second += vector.second;
        }
        grid.values[grid.getIndex( p )] = 1;
      }
      prevC = p;
    }
  }
  //grid.printGrid();

  const Coord initCoord( 500, 0 );
  const Coord newInitCoord( initCoord.first - minX, 0 );

  long long countSand = 0;
  Coord sandCoord = newInitCoord;
  while ( grid.isValidCoord( sandCoord ) )
  {
    int sandIndex = grid.getIndex( sandCoord );
    Coord nextCoord = Coord( sandCoord.first, sandCoord.second + 1 );
    if ( !grid.isValidCoord( nextCoord ) ) break;
    if ( grid.getValue( nextCoord ) == 0 )
    {
      sandCoord = nextCoord;
    }
    else
    {
      // Check isFree Left
      Coord leftCoord = Coord( nextCoord.first - 1, nextCoord.second );
      if ( grid.getValue( leftCoord ) == 0 )
      {
        sandCoord = leftCoord;
        continue;
      }
      // Check isFree right
      Coord rightCoord = Coord( nextCoord.first + 1, nextCoord.second );
      if ( grid.getValue( rightCoord ) == 0 )
      {
        sandCoord = rightCoord;
        continue;
      }
      // No free, left the sand here
      grid.setValue( sandCoord, 2 );
      countSand++;
      sandCoord = newInitCoord;
      continue;
    }
  }


  long long result = countSand;
  printf("The solution for part 1 is: %lli \n", result);
}


void day14Part2()
{
  std::vector<Line> input;
  readDocument<Line>( DAY14_PATH, input );

  int minX = std::numeric_limits<int>::max();
  int minY = std::numeric_limits<int>::max();
  int maxX = std::numeric_limits<int>::min();
  int maxY = std::numeric_limits<int>::min();
  minY = 0;
  for ( auto& l : input )
  {
    for ( auto& p : l.points )
    {
      minX = std::min( minX, p.first );
      maxX = std::max( maxX, p.first );
      maxY = std::max( maxY, p.second );
    }
  }

  maxY = maxY + 2;
  minX = 500 - maxY;
  maxX = 500 + maxY;

  GridI grid( maxX - minX + 1, maxY + 1 );
  grid.values.resize( grid.visited.size(), 0 );
  Line endLine;
  endLine.points.push_back( Coord( minX, maxY ) );
  endLine.points.push_back( Coord( maxX, maxY ) );
  input.push_back( endLine );

  for ( auto& l : input )
  {
    Coord prevC( -1, -1 );
    for ( auto& p : l.points )
    {
      p.first = p.first - minX;
      if ( prevC != Coord( -1, -1 ) )
      {
        Coord vector = Coord( p.first - prevC.first, p.second - prevC.second );
        int modV = std::sqrt( std::pow( vector.first, 2 ) + std::pow( vector.second, 2 ) );
        vector = Coord( vector.first / modV, vector.second / modV );
        while ( prevC != p )
        {
          grid.values[grid.getIndex( prevC )] = 1;
          //grid.printGrid();
          prevC.first += vector.first;
          prevC.second += vector.second;
        }
        grid.values[grid.getIndex( p )] = 1;
      }
      prevC = p;
    }
  }
  //grid.printGrid();

  const Coord initCoord( 500, 0 );
  const Coord newInitCoord( initCoord.first - minX, 0 );

  long long countSand = 0;
  Coord sandCoord = newInitCoord;
  while ( grid.isValidCoord( sandCoord ) )
  {
    if ( grid.getValue( sandCoord ) != 0 ) break;
    int sandIndex = grid.getIndex( sandCoord );
    Coord nextCoord = Coord( sandCoord.first, sandCoord.second + 1 );
    if ( !grid.isValidCoord( nextCoord ) ) break;
    if ( grid.getValue( nextCoord ) == 0 )
    {
      sandCoord = nextCoord;
    }
    else
    {
      // Check isFree Left
      Coord leftCoord = Coord( nextCoord.first - 1, nextCoord.second );
      if ( grid.getValue( leftCoord ) == 0 )
      {
        sandCoord = leftCoord;
        continue;
      }
      // Check isFree right
      Coord rightCoord = Coord( nextCoord.first + 1, nextCoord.second );
      if ( grid.getValue( rightCoord ) == 0 )
      {
        sandCoord = rightCoord;
        continue;
      }
      // No free, left the sand here
      grid.setValue( sandCoord, 2 );
      countSand++;
      sandCoord = newInitCoord;
      continue;
    }
  }


  long long result = countSand;
  printf("The solution for part 2 is: %lli \n", result);
}
