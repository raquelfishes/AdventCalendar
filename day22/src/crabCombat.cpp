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



struct Tile
{
  int tileId;
  std::vector<std::string> tileInfo;
  typedef std::pair<std::string, int> side;

  side left;
  side right;
  side up;
  side down;

  Tile() {};
  Tile( int tileId ) : tileId( tileId )
  {
    left = std::make_pair<std::string, int>( "", -1 );
    right = std::make_pair<std::string, int>( "", -1 );
    up = std::make_pair<std::string, int>( "", -1 );
    down = std::make_pair<std::string, int>( "", -1 );
  };

  void rotate(const int l, const int r)
  {
    std::vector<std::string> newTileInfo(tileInfo);
    if ( l == 1 || r == 3 )
    {
      for ( auto i = 0; i < tileInfo.size(); ++i )
      {
        for ( auto j = 0; j < tileInfo[i].size(); ++j )
        {
          newTileInfo[i][tileInfo.size() - 1 - j] = tileInfo[i][j];
        }
      }
      left.second = up.second;
      down.second = left.second;
      right.second = down.second;
      up.second = right.second;

    }
    if ( l == 2 || r == 2 )
    {
      for ( auto i = 0; i < tileInfo.size(); ++i )
      {
        for ( auto j = 0; j < tileInfo[i].size(); ++j )
        {
          newTileInfo[tileInfo.size() - 1 - i][tileInfo.size() - 1 - j] = tileInfo[i][j];
        }
      }

      left.second = right.second;
      down.second = up.second;
      right.second = left.second;
      up.second = down.second;
    }
    if ( l == 3 || r == 1 )
    {
      for ( auto i = 0; i < tileInfo.size(); ++i )
      {
        for ( auto j = 0; j < tileInfo[i].size(); ++j )
        {
          newTileInfo[tileInfo.size() - 1 - i][j] = tileInfo[i][j];
        }
      }
      left.second = down.second;
      down.second = right.second;
      right.second = up.second;
      up.second = left.second;
    }
  }

  void flip( const int l, const int u )
  {
    if ( l == 1 )
    {
      std::transform( tileInfo.begin(), tileInfo.end(), tileInfo.begin(), []( std::string& line ) 
      {
        std::reverse( line.begin(), line.end() );
      } );

      left.second = right.second;
      right.second = left.second;
    }
    if ( u == 1 )
    {
      std::reverse( tileInfo.begin(), tileInfo.end() );

      down.second = up.second;
      up.second = down.second;
    }
  }

  bool isCorner() const
  {
    int countSides = 0;
    countSides += left.second != -1;
    countSides += right.second != -1;
    countSides += up.second != -1;
    countSides += down.second != -1;

    return countSides == 2;
  }

  void computeSides()
  {
    up.first = tileInfo[0];
    down.first = tileInfo[tileInfo.size() - 1];
    left.first.clear();
    right.first.clear();
    for ( auto& row : tileInfo )
    {
      left.first.push_back( row[0] );
      right.first.push_back( row[row.size()-1] );
    }
  }

  bool checkSide( side& s, Tile& t )
  {
    if ( s.second == -1 )
    {
      std::string reverse = s.first;
      std::reverse( reverse.begin(), reverse.end() );
      if ( ( t.left.second == -1 ) && ( ( s.first == t.left.first ) || ( reverse == t.left.first ) ) )
      {
        s.second = t.tileId;
        t.left.second = tileId;
        return true;
      }
      if ( ( t.right.second == -1 ) && ( ( s.first == t.right.first ) || ( reverse == t.right.first ) ) )
      {
        s.second = t.tileId;
        t.right.second = tileId;
        return true;
      }
      if ( ( t.up.second == -1 ) && ( ( s.first == t.up.first ) || ( reverse == t.up.first ) ) )
      {
        s.second = t.tileId;
        t.up.second = tileId;
        return true;
      }
      if ( ( t.down.second == -1 ) && ( ( s.first == t.down.first ) || ( reverse == t.down.first ) ) )
      {
        s.second = t.tileId;
        t.down.second = tileId;
        return true;
      }
    }
    return false;
  }

  void matchTile( Tile& tile )
  {
    bool matched = false;
    matched = checkSide( left, tile );
    if ( matched ) return;

    matched = checkSide( right, tile );
    if ( matched ) return;

    matched = checkSide( up, tile );
    if ( matched ) return;

    matched = checkSide( down, tile );
    if ( matched ) return;
  }

  void modifyByNeis()
  {

  }

};


void adventDay20()
{
  // Open numbers file
  std::ifstream myfile( FILE_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file found" << std::endl;
    return;
  }

  std::map<int, Tile> mapTiles;
  std::string line;
  std::regex expr( "Tile (\\d+):" );
  std::smatch sm;
  int tileId = -1;
  while ( getline( myfile, line ) )
  {
    if ( std::regex_search( line, sm, expr ) )
    {
      tileId = std::stoi( sm[1].str() );
      mapTiles[tileId] = Tile( tileId );
    }
    else if ( line != "" )
    {
      mapTiles[tileId].tileInfo.push_back( line );
    }
  }
  if ( mapTiles.empty() )
  {
    std::cout << "Error, no valid input file" << std::endl;
    return;
  }


  for ( auto& tile : mapTiles )
  {
    tile.second.computeSides();
  }


  for ( auto& tile1 : mapTiles )
  {
    for ( auto& tile2 : mapTiles )
    {
      if ( tile1.first == tile2.first )
      {
        continue;
      }
      tile1.second.matchTile( tile2.second );
    }
  }

  long long result = 1;
  for ( auto& tile : mapTiles )
  {
    if ( tile.second.isCorner() )
    {
      result *= tile.second.tileId;
    }
  }
  std::cout << "Part 1:  " << result << std::endl;
  
  for ( auto& tile : mapTiles )
  {
    tile.modifyWithNeis();
  }


  std::cout << "Part 2:  " << result << std::endl;
  //std::cout << "Part 2:" << result << std::endl;

}



int main( int argc, char* argv[] )
{
  adventDay20();
}
