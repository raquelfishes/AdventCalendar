#include "std_includes.h"
#include "resource.h"
#include "utils.h"


struct ElfCouple
{
  ElfCouple( std::string s )
  {
    std::vector<std::string> values;
    std::string regExp = "(\\d+)-(\\d+),(\\d+)-(\\d+)";
    splitByRegex( s, regExp, values );
    initElf1 = std::stoi( values[1] );
    endElf1 = std::stoi( values[2] );
    initElf2 = std::stoi( values[3] );
    endElf2 = std::stoi( values[4] );
  }

  bool fullOverlap()
  {
    if( initElf2 <= initElf1 && endElf2 >= endElf1 ) return true;
    if( initElf1 <= initElf2 && endElf1 >= endElf2 ) return true;
    return false;
  }

  bool hasOverlap()
  {
    int minMax = std::min( endElf1, endElf2 );
    int maxMin = std::max( initElf1, initElf2 );
    
    if( minMax >= maxMin ) return true;
    return false;
  }
  

  int initElf1;
  int endElf1;
  int initElf2;
  int endElf2;

};


void day4Part1()
{

  std::vector<ElfCouple> input;
  readDocument<ElfCouple>( DAY4_PATH, input );
  int count = 0;
  for( auto& elf : input )
  {
    if( elf.fullOverlap() ) count++;    
  }
  
  long long result = count;
  printf("The solution for part 1 is: %i \n", result);
}


void day4Part2()
{

  std::vector<ElfCouple> input;
  readDocument<ElfCouple>( DAY4_PATH, input );
  int count = 0;
  for( auto& elf : input )
  {
    if( elf.hasOverlap() ) count++;
  }
  
  
  long long result = count;
  printf("The solution for part 2 is: %i \n", result);
}
