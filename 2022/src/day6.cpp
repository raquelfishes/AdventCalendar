#include "std_includes.h"
#include "resource.h"


void day6Part1()
{
  std::vector<std::string> inputV;
  readDocument( DAY6_PATH, inputV );
  
  std::string input = inputV.front();

  std::map<char, int> auxMap;
  int init = 0;
  int end = 0;
  const int sizeUnique = 4;
 
  while( ( end - init ) < sizeUnique )
  {
    char c = input[end];
    if( auxMap.find( c ) == auxMap.end() || auxMap[c] == 0 )
    {
      auxMap[c] = 1;
      end++;
    }
    else
    {
      while( auxMap[c] > 0 )
      {
        auxMap[input[init]]--;
        init++;
      }
    }
  }

  int result = end;
  printf("The solution for part 1 is: %i \n", result);
}


void day6Part2()
{
  std::vector<std::string> inputV;
  readDocument( DAY6_PATH, inputV );

  std::string input = inputV.front();

  std::map<char, int> auxMap;
  int init = 0;
  int end = 0;
  const int sizeUnique = 14;

  while( ( end - init ) < sizeUnique )
  {
    char c = input[end];
    if( auxMap.find( c ) == auxMap.end() || auxMap[c] == 0 )
    {
      auxMap[c] = 1;
      end++;
    }
    else
    {
      while( auxMap[c] > 0 )
      {
        auxMap[input[init]]--;
        init++;
      }
    }
  }

  int result = end;

  printf( "The solution for part 2 is: %i \n", result );
}
