#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <numeric>
#include <limits>

#include "resource.h"


bool busyDirection( const std::vector<std::string>& seats, int i, int j, const int x, const int y, const int count )
{
  constexpr int minIndex = 0;
  const int maxLength = seats[i].size();
  const int maxSize = seats.size();
  int auxCount = 0;
  i += y;
  j += x;

  while ( i >= minIndex && j >= minIndex && i < maxSize && j < maxLength && auxCount < count )
  {
    if ( seats[i][j] == '#' )
      return true;
    if ( seats[i][j] == 'L' )
      return false;
    auxCount++;
    i += y;
    j += x;
  }

  return false;
}

int busyAround( const std::vector<std::string>& seats, const int i, const int j, const int count )
{
  int result = 0;
  //result += ( i - 1 >= 0 && j - 1 >= 0 ) ? seats[i - 1][j - 1] == '#' : 0;
  //result += ( i - 1 >= 0 ) ? seats[i - 1][j] == '#' : 0;
  //result += ( i - 1 >= 0 && j + 1 < seats[i].size() ) ? seats[i - 1][j + 1] == '#' : 0;
  //
  //result += ( j - 1 >= 0 ) ? seats[i][j-1] == '#' : 0;
  //result += ( j + 1 < seats[i].size() ) ? seats[i][j+1] == '#' : 0;
  //
  //result += ( i + 1 < seats.size() && j - 1 >= 0 ) ? seats[i + 1][j - 1] == '#' : 0;
  //result += ( i + 1 < seats.size() ) ? seats[i + 1][j] == '#' : 0;
  //result += ( i + 1 < seats.size() && j + 1 < seats[i].size() ) ? seats[i + 1][j + 1] == '#' : 0;
  result += busyDirection( seats, i, j, -1, -1, count );
  result += busyDirection( seats, i, j,  0, -1, count );
  result += busyDirection( seats, i, j,  1, -1, count );
                                                
  result += busyDirection( seats, i, j, -1,  0, count );
  result += busyDirection( seats, i, j,  1,  0, count );
                                                
  result += busyDirection( seats, i, j, -1,  1, count );
  result += busyDirection( seats, i, j,  0,  1, count );
  result += busyDirection( seats, i, j,  1,  1, count );
  return result;
}




void adventDay11()
{
  // Open numbers file
  std::ifstream myfile( FILE_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file found" << std::endl;
    return;
  }

  
  std::vector<std::string> seats;
  std::string line;
  while ( getline( myfile, line ) )
  { 
    seats.push_back( line );
  }
  if ( seats.empty() )
  {
    std::cout << "Error, no numbers at file" << std::endl;
    return;
  }
  

  std::vector<std::string> auxSeats(seats.size());
  std::copy( seats.begin(), seats.end(), auxSeats.begin() );
  std::vector<std::string> auxSeats2( seats.size() );
  bool hasChanged = false;
  int countBusy = 0;
  do
  {
    std::copy( auxSeats.begin(), auxSeats.end(), auxSeats2.begin() );
    hasChanged = false;
    countBusy = 0;
    for ( auto i = 0; i < auxSeats.size(); ++i )
    {
      for ( auto j = 0; j < auxSeats[i].size(); ++j )
      {
        if ( auxSeats[i][j] == '.' )
        {
          continue;
        }
        if ( auxSeats[i][j] == 'L' )
        {
          const int count = busyAround( auxSeats, i, j, 1 );
          if ( count == 0 )
          {
            auxSeats2[i][j] = '#';
            countBusy++;
            hasChanged = true;
          }
        }
        if ( auxSeats[i][j] == '#' )
        {
          countBusy++;
          const int count = busyAround( auxSeats, i, j, 1 );
          if ( count >= 4 )
          {
            auxSeats2[i][j] = 'L';
            countBusy--;
            hasChanged = true;
          }
        }
      }
    }
    std::copy( auxSeats2.begin(), auxSeats2.end(), auxSeats.begin() );
  }
  while ( hasChanged );
  std::cout << "Part1: The number of busy seats are: " << countBusy << std::endl;


  
  std::copy( seats.begin(), seats.end(), auxSeats.begin() );
  do
  {
    std::copy( auxSeats.begin(), auxSeats.end(), auxSeats2.begin() );
    hasChanged = false;
    countBusy = 0;
    for ( auto i = 0; i < auxSeats.size(); ++i )
    {
      for ( auto j = 0; j < auxSeats[i].size(); ++j )
      {
        if ( auxSeats[i][j] == '.' )
        {
          continue;
        }
        if ( auxSeats[i][j] == 'L' )
        {
          const int count = busyAround( auxSeats, i, j, std::numeric_limits<int>::max() );
          if ( count == 0 )
          {
            auxSeats2[i][j] = '#';
            countBusy++;
            hasChanged = true;
          }
        }
        if ( auxSeats[i][j] == '#' )
        {
          countBusy++;
          const int count = busyAround( auxSeats, i, j, std::numeric_limits<int>::max() );
          if ( count >= 5 )
          {
            auxSeats2[i][j] = 'L';
            countBusy--;
            hasChanged = true;
          }
        }
      }
    }
    std::copy( auxSeats2.begin(), auxSeats2.end(), auxSeats.begin() );
  }
  while ( hasChanged );
  std::cout << "Part2: The number of busy seats are: " << countBusy << std::endl;
  


}



int main( int argc, char* argv[] )
{
  adventDay11();
}
