#include "std_includes.h"
#include "resource.h"
#include "utils.h"
#include "grid.h"

int backSearchPath( GridI& grid, Coord currPosition, int oldHeigh, Coord targetPosition, int steps )
{
  if ( !grid.isValidCoord( currPosition ) )
    return -1;

  int coordId = grid.getIndex( currPosition );
  if ( ( grid.values[coordId] - oldHeigh ) > 1 )
    return -1;

  if ( grid.visitedSteps[coordId] >= 0 && grid.visitedSteps[coordId] < steps )
    return -1;

  if ( currPosition == targetPosition )
  {
    grid.visitedSteps[coordId] = steps;
    return 1;
  }

  grid.visitedSteps[coordId] = steps;

  Coord newCoord = currPosition;

  int minSteps = std::numeric_limits<int>::max();

  newCoord = Coord( currPosition.first - 1, currPosition.second );
  int left = backSearchPath( grid, newCoord, grid.values[coordId], targetPosition, steps+1 );
  if ( left != -1 ) minSteps = std::min( minSteps, left );

  newCoord = Coord( currPosition.first + 1, currPosition.second );
  int right = backSearchPath( grid, newCoord, grid.values[coordId], targetPosition, steps+1 );
  if ( right != -1 ) minSteps = std::min( minSteps, right );

  newCoord = Coord( currPosition.first, currPosition.second - 1 );
  int up = backSearchPath( grid, newCoord, grid.values[coordId], targetPosition, steps+1 );
  if ( up != -1 ) minSteps = std::min( minSteps, up );

  newCoord = Coord( currPosition.first, currPosition.second + 1 );
  int down = backSearchPath( grid, newCoord, grid.values[coordId], targetPosition, steps+1 );
  if ( down != -1 ) minSteps = std::min( minSteps, down );



  return (minSteps != std::numeric_limits<int>::max() ? 1 + minSteps : -1);

}

void dijstraCompute( GridI& grid, std::vector<Coord> initPositions )
{
  std::vector<int> diffX = { 1,-1,0,0 };
  std::vector<int> diffY = { 0,0,-1,1 };
  std::queue<Coord> toVisited;

  for ( auto& init : initPositions )
  {
    grid.visitedSteps[grid.getIndex( init )] = 0;
    grid.visited[grid.getIndex( init )] = true;
    toVisited.push( init );
  }

  while ( !toVisited.empty() )
  {
    Coord curr = toVisited.front();
    int currId = grid.getIndex( curr );
    toVisited.pop();

    for ( int i = 0; i < 4; ++i )
    {
      Coord next( curr.first + diffX[i], curr.second + diffY[i] );
      if ( !grid.isValidCoord( next ) ) continue;
      int nextId = grid.getIndex( next );
      if ( grid.visited[nextId] ) continue;

      if ( grid.values[nextId] - grid.values[currId] < 2 )
      {
        grid.visitedSteps[nextId] = grid.visitedSteps[currId] + 1;
        grid.visited[nextId] = true;

        toVisited.push( next );
      }
    }
  }

}


void day12Part1()
{
  std::vector<std::string> input;
  readDocument( DAY12_PATH, input );

  std::vector<Coord> initPositions;
  Coord endPosition;

  for ( int i = 0; i < input.size(); ++i )
  {
    for ( int j = 0; j < input.front().length(); ++j )
    {
      if ( input[i][j] == 'S' )
      {
        Coord c( j, i );
        initPositions.push_back( c );
        input[i][j] = 'a';
      }
      if ( input[i][j] == 'E' )
      {
        endPosition.first = j;
        endPosition.second = i;
        input[i][j] = 'z';
      }
    }
  }

  GridI grid;
  grid.initializeToChar( input );
  dijstraCompute( grid, initPositions );

  long long result = grid.visitedSteps[grid.getIndex(endPosition)];
  printf("The solution for part 1 is: %lli \n", result);
}


void day12Part2()
{
  std::vector<std::string> input;
  readDocument( DAY12_PATH, input );

  std::vector<Coord> initPositions;
  Coord endPosition;

  for ( int i = 0; i < input.size(); ++i )
  {
    for ( int j = 0; j < input.front().length(); ++j )
    {
      if ( input[i][j] == 'S' || input[i][j] == 'a' )
      {
        Coord c( j, i );
        initPositions.push_back( c );
        input[i][j] = 'a';
      }
      if ( input[i][j] == 'E' )
      {
        endPosition.first = j;
        endPosition.second = i;
        input[i][j] = 'z';
      }
    }
  }

  GridI grid;
  grid.initializeToChar( input );
  dijstraCompute( grid, initPositions );

  long long result = grid.visitedSteps[grid.getIndex( endPosition )];
  printf("The solution for part 2 is: %lli \n", result);
}
