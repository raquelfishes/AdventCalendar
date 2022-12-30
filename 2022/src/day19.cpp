#include "std_includes.h"
#include "resource.h"
#include "utils.h"

enum class Action{ORE=0, CLAY=1, OBSI=2, GEO=3, WAIT = 0};
const std::vector<Action> actions{ Action::ORE, Action::CLAY, Action::OBSI, Action::GEO, Action::WAIT };

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

    int maxOre = std::max( std::get<0>( oreRobotCost ), std::max( std::get<0>( clayRobotCost ), std::max( std::get<0>( obsiRobotCost ), std::get<0>( geoRobotCost ) ) ) );
    maxCostRobots = std::make_tuple( maxOre, std::get<1>( obsiRobotCost ), std::get<2>( geoRobotCost ), 0 );
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
  OreClayObsiGeo maxCostRobots;
};

inline int calcTheoreticalMax( const int& time, const OreClayObsiGeo& resources, const OreClayObsiGeo& robotsState )
{
  return std::get<3>( resources ) + ( time + 2 * std::get<3>( robotsState ) ) * time / 2;
}

bool isActionHelpful( const Action& action, const OreClayObsiGeo& bluePrintMaxCosts, const OreClayObsiGeo& robotsState )
{
  if( action == Action::ORE )
  {
    return std::get<0>( robotsState ) < std::get<0>( bluePrintMaxCosts );
  }
  if( action == Action::CLAY )
  {
    return std::get<1>( robotsState ) < std::get<1>( bluePrintMaxCosts );
  }
  if( action == Action::OBSI )
  {
    return std::get<2>( robotsState ) < std::get<2>( bluePrintMaxCosts );
  }
  return true;
}

bool isActionPossible( const Action& action, const BluePrint& bluePrint, const OreClayObsiGeo& resources )
{
  if( action == Action::ORE )
  {
    return resources >= bluePrint.oreRobotCost;
  }
  if( action == Action::CLAY )
  {
    return resources >= bluePrint.clayRobotCost;
  }
  if( action == Action::OBSI )
  {
    return resources >= bluePrint.obsiRobotCost;
  }
  return resources >= bluePrint.geoRobotCost;
}

void updateState( int& time, OreClayObsiGeo& resources, OreClayObsiGeo& robotsState )
{
  time--;
  resources = resources + robotsState;
}

void performAction( int& time, const Action& action, const BluePrint& bluePrint, OreClayObsiGeo& resources, OreClayObsiGeo& robotsState )
{
  if( action == Action::ORE )
  {
    resources = resources - bluePrint.oreRobotCost;
    updateState( time, resources, robotsState );
    std::get<0>( robotsState )++;
  }
  if( action == Action::CLAY )
  {
    resources = resources - bluePrint.clayRobotCost;
    updateState( time, resources, robotsState );
    std::get<1>( robotsState )++;
  }
  if( action == Action::OBSI )
  {
    resources = resources - bluePrint.obsiRobotCost;
    updateState( time, resources, robotsState );
    std::get<2>( robotsState )++;
  }
  if( action == Action::GEO )
  {
    resources = resources - bluePrint.geoRobotCost;
    updateState( time, resources, robotsState );
    std::get<3>( robotsState )++;
  }
}

void computeGeodesDFS( int time, int& maxGeodes, const BluePrint& bluePrint, const Action& action, OreClayObsiGeo robotsState, OreClayObsiGeo resources )
{
  // Is action helpful
  if( !isActionHelpful( action, bluePrint.maxCostRobots, robotsState ) ) return;
  if( calcTheoreticalMax( time, resources, robotsState ) <= maxGeodes ) return;

  while( time )
  {
    if( isActionPossible( action, bluePrint, resources ) )
    {
      OreClayObsiGeo newRobotsState = robotsState;
      OreClayObsiGeo newResources = resources;

      performAction( time, action, bluePrint, newResources, newRobotsState );
      for( auto& newAction : actions )
      {
        computeGeodesDFS( time, maxGeodes, bluePrint, newAction, newRobotsState, newResources );
      }
      return;
    }
    else
    {
      updateState( time, resources, robotsState );
    }
  }
  maxGeodes = std::max( maxGeodes, std::get<3>( resources ) );
}

void day19Part1()
{
  std::vector<BluePrint> input;
  readDocument<BluePrint>( DAY19_PATH, input );

  const int numMinutes = 24;

  long long qualityLevel = 0;
  for( const auto& bp : input )
  {
    int geodes = 0;
    for( auto& newAction : actions )
    {
      OreClayObsiGeo res;
      OreClayObsiGeo robots( 1, 0, 0, 0 );
      computeGeodesDFS( numMinutes, geodes, bp, newAction, robots, res );
    }
    qualityLevel += geodes * bp.id;
  }

  long long result = qualityLevel;
  printf("The solution for part 1 is: %lli \n", result);
}


void day19Part2()
{
  std::vector<BluePrint> input;
  readDocument<BluePrint>( DAY19_PATH, input );

  const int numMinutes = 32;

  long long qualityLevel = 1;
  for( int i=0; i<3; ++i)
  {
    BluePrint bp = input[i];
    int geodes = 0;
    for( auto& newAction : actions )
    {
      OreClayObsiGeo res;
      OreClayObsiGeo robots( 1, 0, 0, 0 );
      computeGeodesDFS( numMinutes, geodes, bp, newAction, robots, res );
    }
    qualityLevel *= geodes;
  }

  long long result = qualityLevel;
  printf("The solution for part 2 is: %lli \n", result);
}
