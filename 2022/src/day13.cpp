#include "std_includes.h"
#include "resource.h"
#include "utils.h"

struct PacketsPair
{
  PacketsPair( std::vector<std::string>& vs )
  {
    if ( vs.size() != 2 ) return;
    s1 = vs.front();
    s2 = vs.back();
  }

  bool correctOrder()
  {
    return true;
  }

  std::string s1;
  std::string s2;
};


void day13Part1()
{
  std::vector<PacketsPair> input;
  readDocumentSeveralLines( DAY13_TEST_PATH, 2, input );

  long long sumIndices = 0;
  for ( int i = 0; i < input.size(); ++i )
  {
    if ( input[i].correctOrder() )
    {
      sumIndices += i + 1;
    }
  }

  long long result = sumIndices;
  printf("The solution for part 1 is: %lli \n", result);
}


void day13Part2()
{
  long long result = 0;
  printf("The solution for part 2 is: %lli \n", result);
}
