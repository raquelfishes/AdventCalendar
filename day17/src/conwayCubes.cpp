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

static constexpr char freeChar = '.';
static constexpr char busyChar = '#';

struct Point
{
  int x;
  int y;
  int z;
  int w;
  char value;

  Point() {};
  Point( int x, int y, int z, char v ) : x( x ), y( y ), z( z ), w(0), value( v ){}
  Point( int x, int y, int z ) : x( x ), y( y ), z( z ), w(0), value( freeChar ) {}
  Point( int x, int y, int z, int w, char v ) : x( x ), y( y ), z( z ), w( w ), value( v ) {}
  Point( int x, int y, int z, int w ) : x( x ), y( y ), z( z ), w( w ), value( freeChar ) {}
  Point( const Point& p ) : x(p.x), y(p.y), z(p.z), w(p.w), value(p.value) {}

  bool isNeighbour( const int i, const int j, const int k, const int l )
  {
    const int absDiff = std::abs( x - i ) + std::abs( y - j ) + std::abs( z - k ) + std::abs( w - l );
    return absDiff > 0 && ( std::abs( x - i ) <= 1 ) && ( std::abs( y - j ) <= 1 ) && ( std::abs( z - k ) <= 1 ) && ( std::abs( w - l ) <= 1 );
  }

  bool isFree() const { return value == freeChar; }
  bool isBusy() const { return !isFree(); }
  std::string toString() const { return std::to_string( x ) + '_' + std::to_string( y ) + '_' + std::to_string( z ) + '_' + std::to_string( w ); }

  void getNeighbours( std::vector<std::string>& neis, bool in4d )
  {
    neis.clear();

    for ( auto i = -1; i <= 1; ++i )
    {
      for ( auto j = -1; j <= 1; ++j )
      {
        for ( auto k = -1; k <= 1; ++k )
        {
          if ( in4d )
          {
            for ( auto l = -1; l <= 1; ++l )
            {
              if ( isNeighbour( x + i, y + j, z + k, w + l ) )
                neis.push_back( Point( x + i, y + j, z + k, w + l ).toString() );
            }
          }
          else
          {
            if ( isNeighbour( x + i, y + j, z + k, w ) )
              neis.push_back( Point( x + i, y + j, z + k, w ).toString() );
          }
        }
      }
    }
  }

  void modifyByNeighbours( const std::vector<Point>& neis )
  {
    int countBusy = 0;
    for ( auto& p : neis )
    {
      countBusy += p.isBusy();
    }
    value = countBusy == 3 ? busyChar : isBusy() && countBusy == 2 ? busyChar : freeChar;
  }
};

void addNeighboursToPoints( std::map<std::string, Point>& points, const bool in4d )
{
  std::map<std::string, Point> auxPoints( points );
  for ( auto& p : points )
  {
    std::vector<std::string> neisId;
    p.second.getNeighbours( neisId, in4d );
    std::for_each( neisId.begin(), neisId.end(), [&auxPoints] ( std::string& s )
    {
      auto poIt = auxPoints.find( s );
      if ( poIt == auxPoints.end() )
      {
        std::regex pExpr( "(\-?\\d+)_(\-?\\d+)_(\-?\\d+)_(\-?\\d+)" );
        std::smatch sm;
        std::regex_search( s, sm, pExpr );
        Point po( std::stoi( sm[1].str() ), std::stoi( sm[2].str() ), std::stoi( sm[3].str() ), std::stoi( sm[4].str() ), freeChar );
        auxPoints.insert( { s, po } );
      }
    } );
  }
  points = auxPoints;
}


void adventDay17()
{
  // Open numbers file
  std::ifstream myfile( FILE_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file found" << std::endl;
    return;
  }

  std::map<std::string, Point> initialPoints;
  std::string line;
  int countX = 0;
  while ( getline( myfile, line ) )
  {
    for ( int i=0; i<line.size(); ++i )
    {
      Point p( countX, i, 0, line[i] );
      std::string id = p.toString();
      initialPoints.insert( { id, p } );
    }
    countX++;
  }
  if ( initialPoints.empty() )
  {
    std::cout << "Error, no points at file" << std::endl;
    return;
  }

  //{
  //  std::map<std::string, Point> part1Points( initialPoints );
  //  for ( int i = 0; i < 6; ++i )
  //  {
  //    std::map<std::string, Point> auxPoints( part1Points );
  //    addNeighboursToPoints( part1Points, false );
  //    for ( auto& p : part1Points )
  //    {
  //      std::vector<std::string> neisId;
  //      p.second.getNeighbours( neisId, false );
  //      std::vector<Point> neisP;
  //      std::for_each( neisId.begin(), neisId.end(), [&neisP, &part1Points] ( std::string& s )
  //      {
  //        auto poIt = part1Points.find( s );
  //        if ( poIt != part1Points.end() )
  //        {
  //          neisP.push_back( poIt->second );
  //        }
  //      } );
  //
  //      Point auxP( p.second );
  //      auxP.modifyByNeighbours( neisP );
  //      auxPoints[p.first] = auxP;
  //    }
  //    part1Points = auxPoints;
  //    int busyCount = 0;
  //    std::for_each( part1Points.begin(), part1Points.end(), [&busyCount] ( const auto& p )
  //    {
  //      busyCount += p.second.isBusy();
  //    } );
  //    std::cout << "Loop: " << i << " BusyCount: " << busyCount << std::endl;
  //  }
  //
  //  int busyCount = 0;
  //  std::for_each( part1Points.begin(), part1Points.end(), [&busyCount] ( const auto& p )
  //  {
  //    busyCount += p.second.isBusy();
  //  } );
  //  std::cout << "Par1: The result is: " << busyCount << std::endl;
  //  part1Points.clear();
  //}  

  {
    std::map<std::string, Point> part2Points( initialPoints );
    for ( int i = 0; i < 6; ++i )
    {
      std::map<std::string, Point> auxPoints( part2Points );
      addNeighboursToPoints( part2Points, true );
      for ( auto& p : part2Points )
      {
        std::vector<std::string> neisId;
        p.second.getNeighbours( neisId, true );
        std::vector<Point> neisP;
        std::for_each( neisId.begin(), neisId.end(), [&neisP, &part2Points] ( std::string& s )
        {
          auto poIt = part2Points.find( s );
          if ( poIt != part2Points.end() )
          {
            neisP.push_back( poIt->second );
          }
        } );

        Point auxP( p.second );
        auxP.modifyByNeighbours( neisP );
        auxPoints[p.first] = auxP;
      }
      part2Points = auxPoints;
      int busyCount = 0;
      std::for_each( part2Points.begin(), part2Points.end(), [&busyCount] ( const auto& p )
      {
        busyCount += p.second.isBusy();
      } );
      std::cout << "Loop: " << i << " BusyCount: " << busyCount << std::endl;
    }

    int busyCount = 0;
    std::for_each( part2Points.begin(), part2Points.end(), [&busyCount] ( const auto& p )
    {
      busyCount += p.second.isBusy();
    } );
    std::cout << "Par2: The result is: " << busyCount << std::endl;
  }

}



int main( int argc, char* argv[] )
{
  adventDay17();
}
