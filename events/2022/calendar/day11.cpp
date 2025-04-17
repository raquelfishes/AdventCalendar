#include "std_includes.h"
#include "resource.h"
#include "utils.h"

struct Monkey
{
  Monkey( std::vector<std::string>& input )
  {
    std::vector<std::string> splittedText;
    std::string regExpMonkeyNum   = "Monkey (\\d+):";
    std::string regExpMonkeyItems = "\\s+Starting items: (.*)";
    std::string regExpMonkeyOps   = "\\s+Operation: new = old (.) (.*)";
    std::string regExpMonkeyTest  = "\\s+Test: divisible by (\\d+)";
    std::string regExpMonkeyTrue  = "\\s+If true: throw to monkey (\\d+)";
    std::string regExpMonkeyFalse = "\\s+If false: throw to monkey (\\d+)";
    splitByRegex( input[0], regExpMonkeyNum, splittedText );
    id = std::stoi( splittedText[1] );
    splitByRegex( input[1], regExpMonkeyItems, splittedText );
    splitStringByChar( splittedText[1], ',', splittedText );
    std::for_each( splittedText.begin(), splittedText.end(), [&]( std::string& s ) {items.push_back( std::stoi( s ) ); } );
    splitByRegex( input[2], regExpMonkeyOps, splittedText );
    newOp = splittedText[1][0];
    newOperand = splittedText[2];
    splitByRegex( input[3], regExpMonkeyTest, splittedText );
    test = std::stoi( splittedText[1] );
    splitByRegex( input[4], regExpMonkeyTrue, splittedText );
    ifTrue = std::stoi( splittedText[1] );
    splitByRegex( input[5], regExpMonkeyFalse, splittedText );
    ifFalse = std::stoi( splittedText[1] );
  }

  long long getNewValue( long long value )
  {
    long operand;
    if( newOperand == "old" ) operand = value;
    else operand = std::stoi( newOperand );
    if( newOp =='+' )
      return value + operand;
    if ( newOp == '*' )
      return value * operand;
  }

  int throwToMonkey( int value )
  {
    if( ( value % test ) == 0 ) return ifTrue;
    else return ifFalse;
  }


  int id;
  std::vector<long long> items;

  char newOp;
  std::string newOperand;

  int test;
  int ifTrue;
  int ifFalse;

  long long count = 0;

};

void day11Part1()
{
  std::vector<Monkey> input;
  readDocumentSeveralLines( DAY11_PATH, 6, input );
  
  const int rounds = 20;

  for( int i = 0; i < rounds; ++i )
  {
    for( auto& monkey : input )
    {
      for( auto& item : monkey.items )
      {
        int newValue = monkey.getNewValue( item );
        newValue = newValue / 3;  
        input[monkey.throwToMonkey( newValue )].items.push_back(newValue);
        monkey.count++;
      }
      monkey.items.clear();
    }
  }

  std::sort( input.begin(), input.end(), []( Monkey& m1, Monkey& m2 ) {return m1.count > m2.count; } );

  long long result = input[0].count * input[1].count;
  printf("The solution for part 1 is: %lli \n", result);
}


void day11Part2()
{

  std::vector<Monkey> input;
  readDocumentSeveralLines( DAY11_PATH, 6, input );

  const int rounds = 10000;

  long long divisor=1;
  for( auto& monkey : input ) divisor *= monkey.test;

  for( int i = 0; i < rounds; ++i )
  {
    for( auto& monkey : input )
    {
      for( auto& item : monkey.items )
      {
        long long newValue = monkey.getNewValue( item );
        newValue = newValue % divisor;
        input[monkey.throwToMonkey( newValue )].items.push_back( newValue );
        monkey.count++;
      }
      monkey.items.clear();
    }
  }

  std::sort( input.begin(), input.end(), []( Monkey& m1, Monkey& m2 ) {return m1.count > m2.count; } );

  long long result = input[0].count * input[1].count;
  printf("The solution for part 2 is: %lli \n", result);
}
