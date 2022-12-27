#include "std_includes.h"
#include "resource.h"
#include "utils.h"

typedef std::tuple<int, int, int, int> OreClayObsiGeo;
OreClayObsiGeo operator-( const OreClayObsiGeo& op1, const OreClayObsiGeo& op2 )
{
  auto [x1, y1, z1, w1] = op1;
  auto [x2, y2, z2, w2] = op2;
  return { x1 - x2, y1 - y2, z1 - z2, w1 - w2 };
}
OreClayObsiGeo operator+( const OreClayObsiGeo& op1, const OreClayObsiGeo& op2 )
{
  auto [x1, y1, z1, w1] = op1;
  auto [x2, y2, z2, w2] = op2;
  return { x1 + x2, y1 + y2, z1 + z2, w1 + w2 };
}
bool operator>=( const OreClayObsiGeo& op1, const OreClayObsiGeo& op2 )
{
  auto [x1, y1, z1, w1] = op1;
  auto [x2, y2, z2, w2] = op2;
  if( x1 >= x2 && y1 >= y2 && z1 >= z2 && w1 >= w2 ) return true;
  return false;
}
bool anyInTuple( const OreClayObsiGeo& op )
{
  auto [x, y, z, w] = op;
  return x || y || z || w;
}


struct BluePrint
{
  BluePrint() = default;
  BluePrint( const std::string& s )
  {
    std::vector<std::string> values;
    std::string regExp = "Blueprint (\\d+): Each ore robot costs (\\d+) ore. Each clay robot costs (\\d+) ore. Each obsidian robot costs (\\d+) ore and (\\d+) clay. Each geode robot costs (\\d+) ore and (\\d+) obsidian";
    splitByRegex( s, regExp, values );
    id = std::stoi( values[1] );
    oreRobotCost = std::make_tuple( std::stoi( values[2] ), 0, 0, 0 );
    clayRobotCost = std::make_tuple( std::stoi( values[3] ), 0, 0, 0 );
    obsiRobotCost = std::make_tuple( std::stoi( values[4] ), std::stoi( values[5] ), 0, 0 );
    geoRobotCost = std::make_tuple( std::stoi( values[6] ), 0, std::stoi( values[7] ), 0 );
  }

  OreClayObsiGeo canBuildRobot( const OreClayObsiGeo& res ) const
  {
    OreClayObsiGeo robot = std::make_tuple( 0, 0, 0, 0 );
    if( res >= oreRobotCost ) std::get<0>( robot ) = 1;
    if( res >= clayRobotCost ) std::get<1>( robot ) = 1;
    if( res >= obsiRobotCost ) std::get<2>( robot ) = 1;
    if( res >= geoRobotCost ) std::get<3>( robot ) = 1;
    return robot;
  }

  int id = 0;
  OreClayObsiGeo oreRobotCost;
  OreClayObsiGeo clayRobotCost;
  OreClayObsiGeo obsiRobotCost;
  OreClayObsiGeo geoRobotCost;
};

int computeGeodes( const int time, int& maxGeodes, const BluePrint& bluePrint, const OreClayObsiGeo& robotsState, const OreClayObsiGeo& resources )
{
  if( time <= 0 )
  {
    maxGeodes = std::max(maxGeodes, std::get<3>( resources ));
  }

  int theoricalMaxGeodes = std::get<3>( resources );
  for( int i = time, j = 0; i >= 0; i--, j++ )
  {
    theoricalMaxGeodes += ( std::get<3>( robotsState ) + j ) * i;
  }
  if( maxGeodes > 0 && theoricalMaxGeodes < maxGeodes ) return 0;

  //OreClayObsiGeo qualityLevel = std::make_tuple( 0, 0, 0, 0 );
  OreClayObsiGeo newRobot = std::make_tuple(0, 0, 0, 0);
  OreClayObsiGeo newRobotsState = robotsState;
  OreClayObsiGeo newResources = resources;
  OreClayObsiGeo canBuildRobot = bluePrint.canBuildRobot( resources );
  long long newQualityLevel = std::numeric_limits<long long>::min();

  // Check what can do
  if( resources >= bluePrint.geoRobotCost )
  {

  }

  //
  //if( anyintuple( canbuildrobot ) )
  //{
  //  if( resources >= blueprint.georobotcost )
  //  {
  //    newresources = resources - blueprint.georobotcost;
  //    std::get<3>( newrobot ) += 1;
  //    newresources = newresources + robotsstate;
  //    newrobotsstate = robotsstate + newrobot;
  //    long long auxqlevel = computegeodes( time - 1, blueprint, newrobotsstate, newresources );
  //    newqualitylevel = std::max( newqualitylevel, auxqlevel );
  //  }
  //  if( resources >= blueprint.obsirobotcost )
  //  {
  //    newresources = resources - blueprint.obsirobotcost;
  //    std::get<2>( newrobot ) += 1;
  //    newresources = newresources + robotsstate;
  //    newrobotsstate = robotsstate + newrobot;
  //    long long auxqlevel = computegeodes( time - 1, blueprint, newrobotsstate, newresources );
  //    newqualitylevel = std::max( newqualitylevel, auxqlevel );
  //  }
  //  if( resources >= blueprint.clayrobotcost )
  //  {
  //    newresources = resources - blueprint.clayrobotcost;
  //    std::get<1>( newrobot ) += 1;
  //    newresources = newresources + robotsstate;
  //    newrobotsstate = robotsstate + newrobot;
  //    long long auxqlevel = computegeodes( time - 1, blueprint, newrobotsstate, newresources );
  //    newqualitylevel = std::max( newqualitylevel, auxqlevel );
  //  }
  //  if( resources >= blueprint.orerobotcost )
  //  {
  //    newresources = resources - blueprint.orerobotcost;
  //    std::get<0>( newrobot ) += 1;
  //    newresources = newresources + robotsstate;
  //    newrobotsstate = robotsstate + newrobot;
  //    long long auxqlevel = computegeodes( time - 1, blueprint, newrobotsstate, newresources );
  //    newqualitylevel = std::max( newqualitylevel, auxqlevel );
  //  }
  //}

  //// compute state without build robots
  //newresources = resources + robotsstate;
  //long long qualitylevel = computegeodes( time - 1, blueprint, robotsstate, newresources );

  //return std::max( qualitylevel, newqualitylevel );
  return 0;
}

void day19Part1()
{
  std::vector<BluePrint> input;
  readDocument<BluePrint>( DAY19_TEST_PATH, input );

  const int numMinutes = 24;

  long long qualityLevel = 0;
  for( const auto& bp : input )
  {
    OreClayObsiGeo res;
    OreClayObsiGeo robots( 1, 0, 0, 0 );
    int geodes = 0;
    computeGeodes( numMinutes, geodes, bp, robots, res );
    qualityLevel += geodes * bp.id;
  }

  long long result = qualityLevel;
  printf("The solution for part 1 is: %lli \n", result);
}


void day19Part2()
{
  long long result = 0;
  printf("The solution for part 2 is: %lli \n", result);
}
