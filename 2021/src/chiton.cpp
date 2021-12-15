#include "adventdays_fwd.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <numeric>
#include <memory>

#include "resource.h"
#include "utils.h"
#include "grid.h"


struct Node
{
  Node() = default;
  Node( int x, int y )
    :x(x), y(y)
  {}

  int x;
  int y;
  int parentX=-1;
  int parentY=-1;
  double gCost=0;
  double hCost=0;
  double fCost=0;
};

inline bool operator < ( const Node& lhs, const Node& rhs )
{//We need to overload "<" to put our struct into a set
  return lhs.fCost < rhs.fCost;
}

void initializeGrid( GridI& grid, const std::vector<std::string>& str )
{
  grid.sizeX = str[0].size();
  grid.sizeY = str.size();

  const int numValues = grid.sizeX * grid.sizeY;
  grid.values.reserve( numValues );
  grid.visited.resize( numValues, false );
  for ( auto& line : str )
  {
    for ( auto & col : line )
    {
      grid.values.push_back( char2int( col ) );
    }
  }
}

float calculateH( const int x, const int y, const GridI& grid )
{
  // Compute as Euclidean distance
  return std::sqrt( std::pow( x - ( grid.sizeX - 1 ), 2 ) + 
                    std::pow( y - ( grid.sizeY - 1 ), 2 ) );
}

bool isDestination( const int x, const int y, GridI& grid )
{
  return ( x == grid.sizeX - 1 ) && ( y == grid.sizeY - 1 );
}

void aStarPathFinding( GridI& grid )
{
  int initIndex = 0;
  coord initCoord = grid.getXY( initIndex );
  int finalIndex = grid.values.size() - 1;
  coord finalCoord = grid.getXY( finalIndex );

  std::vector<Node> openList;
  std::vector<Node> closedList;
  Node n(initCoord.first, initCoord.second);
  openList.push_back( n );

  while ( !openList.empty() )
  {
    auto qValue = std::min_element( openList.begin(), openList.end() );
    int qIndex = grid.getIndex( qValue->x, qValue->y );
    Node auxNode = *qValue;
    openList.erase( qValue );
    closedList.push_back( auxNode );
    grid.visited[qIndex] = true;
    
    // Check descendents
    for ( int diffX = -1; diffX <= 1; diffX++ )
    {
      for ( int diffY = -1; diffY <= 1; diffY++ )
      {
        const int newX = auxNode.x + diffX;
        const int newY = auxNode.y + diffY;
        const int newIndex = grid.getIndex( newX, newY );
        if ( grid.isValidCoord( newX, newY ) )
        {
          if ( isDestination( newX, newX, grid ) )
          {
            Node newNode( newX, newY );
            newNode.gCost = auxNode.gCost + grid.values[newIndex];;
            newNode.hCost = calculateH( newX, newY, grid );
            newNode.fCost = newNode.gCost + newNode.hCost;
            newNode.parentX = auxNode.x;
            newNode.parentY = auxNode.y;
            closedList.push_back( newNode );
            grid.visited[newIndex] = true;
            return;
          }
          if ( !grid.visited[newIndex] )
          {
            float gNew = auxNode.gCost + grid.values[newIndex];
            float hNew = calculateH( newX, newY, grid );
            float fNew = gNew + hNew;

            auto nextOpen = std::min_element( openList.begin(), openList.end() );
            if ( nextOpen != openList.end() && nextOpen->fCost < fNew )
            {
              continue;
            }
              
            Node newNode( newX, newY );
            newNode.gCost = gNew;
            newNode.hCost = hNew;
            newNode.fCost = fNew;
            newNode.parentX = auxNode.x;
            newNode.parentY = auxNode.y;

            openList.push_back( newNode );
            
          }
        }
      }
    }
  }
}

long long computePathValue( const GridI& grid )
{
  long long value = 0;
  for ( int i = 0; i < grid.values.size(); ++i )
  {
    value += grid.visited[i] ? grid.values[i] : 0;
  }
  return value;
}

void chitonPart1()
{
  std::vector<std::string> docuStr;
  readDocument<std::string>(DAY15_TEST_PATH, docuStr );

  GridI grid;
  initializeGrid( grid, docuStr );
  aStarPathFinding( grid );
  long long aux = computePathValue( grid );
  
  long long result = aux;
  printf("The solution for part 1 is: %i \n", result);

}

void chitonPart2()
{
  
  long long result = 0;
  printf("The solution for part 2 is: %lld \n", result);
}
