#include "std_includes.h"
#include "resource.h"
#include "utils.h"


int countVisibles( const std::vector<std::vector<int>>& grid, const int row, const int col, int sumRow, int sumCol, int value )
{
  if( row < 0 || row >= grid.size() || col < 0 || col >= grid.front().size() )
  {
    return 1;
  }

  if ( grid[row][col] >= value )
    return 0;
  
  int visible = countVisibles(grid, row+sumRow, col+sumCol, sumRow, sumCol, value );
  return visible;
  
}

int countDistance( const std::vector<std::vector<int>>& grid, const int row, const int col, int sumRow, int sumCol, int value, int distance )
{
  if( row < 0 || row >= grid.size() || col < 0 || col >= grid.front().size() )
  {
    return distance-1;
  }

  if( grid[row][col] >= value )
    return distance;

  int newDistance = countDistance( grid, row + sumRow, col + sumCol, sumRow, sumCol, value, distance+1 );
  return newDistance;

}


void day8Part1()
{
  std::vector<std::string> input;
  readDocument( DAY8_PATH, input );
  
  int x = input.front().length();
  int y = input.size();

  int count = (x * 2 + y * 2) - 4;

  std::vector<std::vector<int>> inputInt( input.size(), std::vector<int>( input.front().size(), 0 ) );
  for( int i = 0; i < input.size(); ++i )
  {
    for( int j = 0; j < input[i].size(); ++j )
    {
      inputInt[i][j] = input[i][j] - '0';
    }
  }

  for( int i = 1; i < input.size()-1; ++i )
  {
    for( int j = 1; j < input[i].size()-1; ++j )
    {
      int aux = countVisibles( inputInt, i + 1, j, 1, 0, inputInt[i][j] );
      if( aux > 0 ) { count += 1; continue; }
      aux = countVisibles( inputInt, i - 1, j, -1, 0, inputInt[i][j] );
      if( aux > 0 ) { count += 1; continue; }
      aux = countVisibles( inputInt, i, j + 1, 0, 1, inputInt[i][j] );
      if( aux > 0 ) { count += 1; continue; }
      aux = countVisibles( inputInt, i, j - 1, 0, -1, inputInt[i][j] );
      if( aux > 0 ) { count += 1; continue; }

    }
  }


  long long result = count;
  printf("The solution for part 1 is: %lli \n", result);
}


void day8Part2()
{
  std::vector<std::string> input;
  readDocument( DAY8_PATH, input );

  int x = input.front().length();
  int y = input.size();

  int count = ( x * 2 + y * 2 ) - 4;

  std::vector<std::vector<int>> inputInt( input.size(), std::vector<int>( input.front().size(), 0 ) );
  for( int i = 0; i < input.size(); ++i )
  {
    for( int j = 0; j < input[i].size(); ++j )
    {
      inputInt[i][j] = input[i][j] - '0';
    }
  }

  int maxDis = std::numeric_limits<int>::min();


  for( int i = 1; i < input.size() - 1; ++i )
  {
    for( int j = 1; j < input[i].size() - 1; ++j )
    {
      int aux1 = countDistance( inputInt, i + 1, j, 1, 0, inputInt[i][j], 1 );
      int aux2 = countDistance( inputInt, i - 1, j, -1, 0, inputInt[i][j], 1 );
      int aux3 = countDistance( inputInt, i, j + 1, 0, 1, inputInt[i][j], 1 );
      int aux4 = countDistance( inputInt, i, j - 1, 0, -1, inputInt[i][j], 1 );
      int currDistance = aux1 * aux2 * aux3 * aux4;
      
      maxDis = std::max( maxDis, currDistance );

    }
  }

  long long result = maxDis;
  printf("The solution for part 2 is: %lli \n", result);
}
