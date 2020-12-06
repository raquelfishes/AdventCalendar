#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <numeric>

#include "resource.h"


int countNonRepeatedCharacters( std::vector<std::string>& group )
{
  std::string joinQuestions = "";
  std::for_each( group.begin(), group.end(), [&joinQuestions] ( std::string& person ) { joinQuestions += person; } );
  std::sort( joinQuestions.begin(), joinQuestions.end() );
  joinQuestions.erase(std::unique( joinQuestions.begin(), joinQuestions.end()), joinQuestions.end());
  return joinQuestions.size();
}

int countRepeatedCharactersByAll( std::vector<std::string>& group )
{
  std::string joinQuestions = "";
  std::for_each( group.begin(), group.end(), [&joinQuestions] ( std::string& person ) { joinQuestions += person; } );
  std::sort( joinQuestions.begin(), joinQuestions.end() );
  int repeatedChars = 0;
  for ( auto c : group[0] )
  {
    repeatedChars = std::count( joinQuestions.begin(), joinQuestions.end(), c ) == group.size() ? repeatedChars + 1 : repeatedChars;
  }

  return repeatedChars;
}

void adventDay5()
{
  // Open numbers file
  std::ifstream myfile( FILE_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file found" << std::endl;
    return;
  }

  
  std::vector<std::vector<std::string>> forms;
  std::string line;
  std::smatch sm;
  std::vector<std::string> group;
  while ( getline( myfile, line ) )
  { 
    if ( line == "" )
    {
      forms.push_back( group );
      group.clear();
      continue;
    }
    group.push_back(line);
  }
  if ( !group.empty() )
  {
    forms.push_back( group );
  }

  if ( forms.empty() )
  {
    std::cout << "Error, no seats at file" << std::endl;
  }
  
  int numberOfQuestions = 0;
  std::for_each( forms.begin(), forms.end(), [&numberOfQuestions]( std::vector<std::string>& group )
  {
    const int numberOfGroupQuestions = countNonRepeatedCharacters( group );
    numberOfQuestions += numberOfGroupQuestions;
  } );
  std::cout << "Part1: The number of questions answered are: " << numberOfQuestions << std::endl;


  numberOfQuestions = 0;
  std::for_each( forms.begin(), forms.end(), [&numberOfQuestions] ( std::vector<std::string>& group )
  {
    const int numberOfGroupQuestions = countRepeatedCharactersByAll( group );
    numberOfQuestions += numberOfGroupQuestions;
  } );
  std::cout << "Part2: The number of questions answered by all group are: " << numberOfQuestions << std::endl;


}



int main( int argc, char* argv[] )
{
  adventDay5();
}