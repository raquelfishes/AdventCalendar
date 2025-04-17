#include "std_includes.h"
#include "resource.h"
#include "utils.h"

struct Instruction
{
  Instruction( const std::string& s )
  {
    if( s == "noop" )
    {
      cyclesToComplete = 1;
      return;
    }
    std::vector<std::string> values;
    splitStringByChar( s, ' ', values );
    cyclesToComplete = 2;
    value = std::stoi( values[1] );
  }

  int cyclesToComplete = 0;
  int value = 0;
};

void day10Part1()
{
  std::vector<Instruction> input;
  readDocument<Instruction>( DAY10_PATH, input );

  std::vector<int> interestingSignals = { 20, 60, 100, 140, 180, 220 };
  std::vector<int> valuesInterestingSignals;

  int currValue = 1;
  int currCycle = 1;
  int currIndexSignal = 0;

  for( auto& instr : input )
  {
    currCycle += instr.cyclesToComplete;

    if( currCycle > interestingSignals[currIndexSignal] )
    {
      valuesInterestingSignals.push_back( interestingSignals[currIndexSignal] * currValue );
      currIndexSignal++;
      if( currIndexSignal >= interestingSignals.size() )
        break;
    }
    currValue += instr.value;
  }

  long long result = std::accumulate( valuesInterestingSignals.begin(), valuesInterestingSignals.end(), 0 );
  printf("The solution for part 1 is: %lli \n", result);
}


void day10Part2()
{
  std::vector<Instruction> input;
  readDocument<Instruction>( DAY10_PATH, input );

  const int sizeX = 40;
  const int sizeY = 6;
  std::vector<std::string> spriteDraw( sizeY, std::string( sizeX, ' ' ) );

  int currValue = 0;
  int currCycle = 0;

  int xSprite = 0;
  int ySprite = 0;

  for( auto& instr : input )
  {
    currCycle += instr.cyclesToComplete;

    for( int i = 0; i < instr.cyclesToComplete; ++i )
    {

      if( xSprite >= currValue && xSprite <= ( currValue + 2 ) )
      {
        spriteDraw[ySprite][xSprite] = '#';
      }

      xSprite++;

      if( xSprite >= sizeX )
      {
        xSprite = 0;
        ySprite++;
      }
      
    }
    currValue += instr.value;
  }

  for( auto& line : spriteDraw )
  {
    std::cout << line << std::endl;
  }
  //long long result = std::accumulate( valuesInterestingSignals.begin(), valuesInterestingSignals.end(), 0 );
  //printf("The solution for part 2 is: %lli \n", result);
}
