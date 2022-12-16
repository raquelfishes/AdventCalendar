#include "std_includes.h"
#include "resource.h"
#include "utils.h"

struct Valve
{
  Valve() = default;
  Valve( const std::string& s )
  {
    std::vector<std::string> aux;
    std::string regExp = "Valve (\\w+) has flow rate=(\\d+); tunnels? leads? to valves? (.*)";
    splitByRegex( s, regExp, aux );
    id = aux[1];
    rate = std::stoi( aux[2] );
    std::vector<std::string> aux2;
    splitStringByString( aux[3], ", ", aux2 );
    if ( aux2.size() > 1 ) connectTo = aux2;
    else connectTo = {aux[3]};
  }

  std::string id = "";
  std::vector<std::string> connectTo;
  int rate = 0;
  bool opened = false;

};

int pathSearch( const std::string& valve, const int countValves, int leftTime, std::map<std::string, int>& map, std::vector<Valve> vector )
{
  leftTime--;

  if ( countValves == 0 || leftTime == 0 )
    return 0;

  Valve& v = vector[map[valve]];
  int pressure = 0;
  // Two options ( open ) or move to connections
  if ( !v.opened && v.rate > 0 )
  {
    pressure = v.rate * leftTime;
    v.opened = true;
    pressure += pathSearch( valve, countValves - 1, leftTime-1, map );
  }
  
  for ( auto& c : v.connectTo )
  {
    int auxPressure = pathSearch( c, countValves, leftTime, map );
    pressure = std::max( pressure, auxPressure );
  }

  return pressure;

}


void day16Part1()
{
  std::vector<Valve> input;
  readDocument<Valve>( DAY16_TEST_PATH, input );
  std::map<std::string, int> mapToInput;
  int valvesToOpen = 0;
  for ( int i=0; i<input.size(); ++i ) 
  { 
    mapToInput.insert( { input[i].id, i } );
    if ( input[i].rate > 0 ) valvesToOpen++;
  }
  const int time = 30;
  const std::string firstValve = input[0].id;

  long long result = 0;
  printf("The solution for part 1 is: %lli \n", result);
}


void day16Part2()
{
  long long result = 0;
  printf("The solution for part 2 is: %lli \n", result);
}
