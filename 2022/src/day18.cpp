#include "std_includes.h"
#include "resource.h"
#include "utils.h"

struct Point
{
  Point( const std::string& s )
  {
    std::vector<std::string> values;
    splitStringByChar( s, ',', values );
    x = std::stoi( values[0] );
    y = std::stoi( values[1] );
    z = std::stoi( values[2] );
  }

  Point( const int i, const int j, const int k ):
    x(i),y(j),z(k)
  { }
  
  Point ( const int v) :
    x( v ), y( v ), z( v )
  {
  }

  void getNeighbours( std::vector<Point>& neis )
  {
    neis.clear();
    neis.push_back( Point( x, y, z + 1 ) );
    neis.push_back( Point( x, y, z - 1 ) );
    neis.push_back( Point( x, y + 1, z ) );
    neis.push_back( Point( x, y - 1, z ) );
    neis.push_back( Point( x + 1, y, z ) );
    neis.push_back( Point( x - 1, y, z ) );
  }

  std::string getKey()
  {
    return std::to_string( x ) + "," + std::to_string(y) + "," + std::to_string(z);
  }

  int x;
  int y;
  int z;
};

struct PointCmp
{
  bool operator()(const Point& p1, const Point& p2) const
  {
    return ( p1.x <= p2.x ) && ( p1.y <= p2.y ) && ( p1.z <= p2.z );
  }
};


void day18Part1()
{
  
  std::vector<Point> input;
  readDocument( DAY18_PATH, input );
  
  std::map<std::string, bool> cache;
  for( auto& point : input ) { cache[point.getKey()] = true; };
  
  int surface = 0;
  std::vector<Point> neis;
  for( auto& point : input )
  {
    point.getNeighbours(neis);
    std::for_each( neis.begin(), neis.end(), [&]( Point& p ) 
                   { 
                     if( cache.find(p.getKey()) == cache.end() ) 
                       surface++; 
                   });
  }

  long long result = surface;
  printf("The solution for part 1 is: %lli \n", result);
  
}

enum State{AIR, LAVA, NONE};

void spreadAir( const int x, const int y, const int z, std::map<std::string, State>& cache,
                const int minX, const int maxX, const int minY, const int maxY, const int minZ, const int maxZ )
{
  Point auxP( x, y, z );
  cache[auxP.getKey()] = State::AIR;
  std::vector<Point> neis;
  auxP.getNeighbours( neis );
  for( auto& p : neis )
  {
    if ( ( x>=minX && x<=maxX && y>=minY && y<=maxY && z>=minZ && z<=maxZ ) && 
         ( cache.find( p.getKey() ) == cache.end() ) )
    {
      spreadAir( p.x, p.y, p.z, cache, minX, maxX, minY, maxY, minZ, maxZ );
    }
  }
}

void day18Part2()
{
  
  std::vector<Point> input;
  readDocument<Point>( DAY18_PATH, input );
  
  Point minP( std::numeric_limits<int>::max() );
  Point maxP( std::numeric_limits<int>::min() );

  for( auto& point : input )
  {
    minP.x = std::min( minP.x, point.x );
    minP.y = std::min( minP.y, point.y );
    minP.z = std::min( minP.z, point.z );
    maxP.x = std::max( maxP.x, point.x );
    maxP.y = std::max( maxP.y, point.y );
    maxP.z = std::max( maxP.z, point.z );
  }
  minP.x -= 1; minP.y -= 1; minP.z -= 1;
  maxP.x += 1; maxP.y += 1; maxP.z += 1;
  std::map<std::string, State> cache;
  for( auto& point : input ) { cache[point.getKey()] = State::LAVA; };

  std::set<std::string> fillAir;
  fillAir.insert( minP.getKey() );
  while( !fillAir.empty() )
  {
    Point auxP( *fillAir.begin() );
    fillAir.erase(auxP.getKey());
    cache[auxP.getKey()] = State::AIR;
    std::vector<Point> neis;
    auxP.getNeighbours( neis );
    for( auto& p : neis )
    {
      if( ( p.x >= minP.x && p.x <= maxP.x && p.y >= minP.y && p.y <= maxP.y && p.z >= minP.z && p.z <= maxP.z ) &&
          ( cache.find( p.getKey() ) == cache.end() ) )
      {
        fillAir.insert( p.getKey() );
      }
    }
  }

  int surface = 0;
  std::vector<Point> neis;
  for( auto& point : input )
  {
    point.getNeighbours( neis );
    std::for_each( neis.begin(), neis.end(), [&]( Point& p )
                   {
                     if( cache.find( p.getKey() ) != cache.end() && cache.find(p.getKey() )->second == State::AIR )
                       surface++;
                   } );
  }

  long long result = surface;
  printf("The solution for part 2 is: %lli \n", result);
  
}
