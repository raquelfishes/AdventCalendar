#include "std_includes.h"
#include "resource.h"
#include "utils.h"


void day3Part1()
{
  std::vector<std::string> input;
  readDocument( DAY3_PATH, input );
  
  if ( input.empty() )
  {
    std::cout << "Error, no binary numbers at file" << std::endl;
  }

  // Part 1:
  long long count = 0;
  
  for( auto& line : input )
  {
    int sizeC = line.size() / 2;
    std::set<char> comp1(line.begin(), line.begin()+sizeC) ;
    for( int i = 0; i < sizeC; ++i )
    {
      if( comp1.contains( line[sizeC + i] ) )
      {
        int value;
        if( isCharLowerCase(line[sizeC + i] ) ) value = line[sizeC + i] - 'a';
        if( isCharUpperCase( line[sizeC + i] ) ) value = line[sizeC + i] - 'A'+26;

        count += value + 1;
        break;
      }
    }
  }
  
  
  long long result = count;
  printf("The solution for part 1 is: %i \n", result);
}


void day3Part2()
{
  std::vector<std::string> input;
  readDocument( DAY3_PATH, input );

  if( input.empty() )
  {
    std::cout << "Error, no binary numbers at file" << std::endl;
  }


  // Part 1:
  long long count = 0;
  for( int i = 0; i < input.size(); i += 3 )
  {
    std::set<char> elf1( input[i].begin(), input[i].end() );
    std::set<char> elf2( input[i + 1].begin(), input[i + 1].end() );
    std::set<char> elf3( input[i + 2].begin(), input[i + 2].end() );

    std::vector<char> intersection1;
    std::vector<char> intersection2;
    std::set_intersection( elf1.begin(), elf1.end(), elf2.begin(), elf2.end(), std::back_inserter( intersection1 ) );
    std::set_intersection( intersection1.begin(), intersection1.end(), elf3.begin(), elf3.end(), std::back_inserter( intersection2 ) );

    int value;
    if( isCharLowerCase( intersection2[0] ) ) value = intersection2[0] - 'a';
    if( isCharUpperCase( intersection2[0] ) ) value = ( intersection2[0] - 'A' ) + 26;

    count += value + 1;

  }
  
  long long result = count;
  printf("The solution for part 2 is: %i \n", result);
}
