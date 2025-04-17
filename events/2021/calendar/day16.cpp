#include "sonar_sweep.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <string>
#include <numeric>

#include "resource.h"
#include "utils.h"

static const int numIterations = 100;

typedef std::pair<int, int> coord;

template<typename T>
struct Grid
{
  Grid(std::vector<std::string> strValues)
  {    
    std::string lineExpr( "(\\d+),(\\d+)" );
    sizeX = std::numeric_limits<int>::min();
    sizeY = std::numeric_limits<int>::min();
    for (auto& line : strValues)
    {
      if ( matchRegex( line, lineExpr ) )
      {
        std::vector<std::string> values;
        splitString( line, ',', values );
        sizeX = std::max( sizeX, std::stoi( values[0] )+1 );
        sizeY = std::max( sizeY, std::stoi( values[1] )+1 );
      }
    }


    const int numValues = (sizeX) * (sizeY);
    values.resize( numValues, false );
    for ( auto& line : strValues )
    {
      if ( matchRegex( line, lineExpr ) )
      {
        std::vector<std::string> coords;
        splitString( line, ',', coords );
        int index = getIndex( std::stoi( coords[0] ), std::stoi( coords[1] ) );
        values[index] = true;
      }
    }
  }

  coord getXY(const int index)
  {
    return std::pair<int,int>((index%sizeX), (index/sizeY));
  }

  int getIndex( const int x, const int y )
  {
    return x + y * sizeX;
  }

  int getIndex(const coord c)
  {
    return getIndex( c.first, c.second );
  }

  bool isValidCoord(const coord c)
  {
    bool validX = (0 <= c.first && c.first < sizeX);
    bool validY = (0 <= c.second && c.second < sizeY);

    return validX && validY;
  }

  bool isValidIndex( const int index )
  {
    return ( index >= 0 ) && ( index < ( sizeX*sizeY ) );
  }
  
  void printGrid()
  {
    for (int i = 0; i < sizeY; ++i)
    {
      for (int j = 0; j < sizeX; ++j)
      {
        int index = getIndex(coord(j, i));
        if (values[index] == 0)
          printf(".");
        else
          printf("#");
      }
      printf("\n");
    }
    printf("\n");
    printf("\n");
  }


  int sizeX;
  int sizeY;
  std::vector<T> values;
};

struct Instruction
{
  
  Instruction( const std::string s )
  {
    std::vector<std::string> values;
    std::regex exp( "fold along (\\w)=(\\d+)" );
    splitByRegex( s, exp, values );
    if ( !values.empty() )
    {
      type = values[1];
      value = std::stoi( values[2] );
    }
  }

  std::string type; // 'x' or 'y'
  int value;
};

void executeInstruction( const Instruction& inst, Grid<bool>& g )
{
  if ( inst.type == "x" )
  {
    // Fold 
    int foldIndex = g.getIndex( inst.value, 0 );
    coord p1Coord( inst.value-1, 0 );
    coord p2Coord( inst.value+1, 0 );
    int size1 = (foldIndex)*g.sizeY;
    int size2 = (g.sizeX - (foldIndex+1))*g.sizeY;
    int sizeFold = std::min( size1, size2 );
    for ( int i = 0; i < sizeFold; ++i )
    {
      int p1Index = g.getIndex( p1Coord );
      int p2Index = g.getIndex( p2Coord );
      int newIndex = p1Coord.first + p1Coord.second * inst.value;
      g.values[newIndex] = g.values[p1Index] || g.values[p2Index];
      g.values[p2Index] = false;
      --p1Coord.first;
      ++p2Coord.first;
      if ( !g.isValidCoord( p2Coord ) )
      {
        p1Coord.second += 1;
        p2Coord.second += 1;
        p1Coord.first = inst.value - 1;
        p2Coord.first = inst.value + 1;
      }
    }
    g.sizeX = inst.value;
    g.values.resize( g.sizeX*g.sizeY );

  }
  else if ( inst.type == "y" )
  {
    // Fold vertical
    int foldIndex = g.getIndex( 0, inst.value );
    coord p1Coord( 0, inst.value - 1 );
    coord p2Coord( 0, inst.value + 1 );
    int size1 = foldIndex;
    int size2 = ( g.sizeX )*(g.sizeY- (inst.value+1));
    int sizeFold = std::min( size1, size2 );
    for ( int i = 0; i < sizeFold; ++i )
    {
      int p1Index = g.getIndex( p1Coord );
      int p2Index = g.getIndex( p2Coord );
      g.values[p1Index] = g.values[p1Index] || g.values[p2Index];
      g.values[p2Index] = false;
      ++p1Coord.first;
      ++p2Coord.first;
      if ( !g.isValidCoord( p1Coord ) )
      {
        p1Coord.first = 0;
        p2Coord.first = 0;
        p1Coord.second = p1Coord.second - 1;
        p2Coord.second = p2Coord.second + 1;
      }
    }
    g.sizeY = inst.value;
    g.values.resize( g.sizeX*g.sizeY );
  }
}

void transparentOrigamiPart1()
{
  std::vector<std::string> numsStr;
  readDocument<std::string>( DAY13_PATH, numsStr );

  std::vector<Instruction> instructions;
  for ( auto& s : numsStr )
  {
    if ( matchRegex( s, "fold along (\\w)=(\\d+)" ) )
    {
      instructions.push_back( Instruction( s ) );
    }
  }
  Grid<bool> grid2d( numsStr );
  executeInstruction( instructions[0], grid2d );
  //executeInstruction( instructions[1], grid2d );

  int count = std::accumulate(grid2d.values.begin(), grid2d.values.end(), 0);

  int result = count;
  printf("The solution for part 1 is: %i \n", result);

}

void transparentOrigamiPart2()
{
  std::vector<std::string> numsStr;
  readDocument<std::string>( DAY13_PATH, numsStr );

  std::vector<Instruction> instructions;
  for ( auto& s : numsStr )
  {
    if ( matchRegex( s, "fold along (\\w)=(\\d+)" ) )
    {
      instructions.push_back( Instruction( s ) );
    }
  }
  Grid<bool> grid2d( numsStr );
  for ( auto& i : instructions )
  {
    executeInstruction( i, grid2d );
    //grid2d.printGrid();
  }

  grid2d.printGrid();
  int result = 0;

  printf("The solution for part 2 is: %lld \n", result);
}
