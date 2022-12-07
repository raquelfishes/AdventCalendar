#include "std_includes.h"
#include "resource.h"
#include "utils.h"


void day7Part1()
{
  std::vector<std::string> input;
  readDocument( DAY7_PATH, input );
  
  std::string currentDir = "";
  std::stack<std::string> dirStack;
  std::map<std::string, long long> dirMap;

  for ( auto& line : input )
  {
    std::vector<std::string>simbolsLine;
    splitString( line, ' ', simbolsLine );

    if ( simbolsLine.front() == "$" && simbolsLine[1] == "cd" )
    {
      if ( simbolsLine[2] == ".." )
      {
        dirStack.pop();
        currentDir = dirStack.top();
      }
      else
      {
        currentDir.append( "/" );
        currentDir.append( simbolsLine[2] );
        dirStack.push( currentDir );
        dirMap[currentDir] = 0;
      }
    }
    else if ( simbolsLine.front() != "$" && simbolsLine.front().find_first_not_of( "0123456789" ) == std::string::npos )
    {
      dirMap[currentDir] += std::stoll( simbolsLine.front() );

      // Add to all the parent directories
      std::stack<std::string> auxStack;
      auxStack.push( dirStack.top() );
      dirStack.pop();
      while ( !dirStack.empty() )
      {
        auxStack.push( dirStack.top() );
        dirMap[dirStack.top()] += std::stoll( simbolsLine.front() );
        dirStack.pop();
      }
      while ( !auxStack.empty() )
      {
        dirStack.push( auxStack.top() );
        auxStack.pop();
      }
    }
  }

  const long long maxSize = 100000;
  long long count = 0;
  for ( auto& dir : dirMap )
  {
    if ( dir.second < maxSize )
    {
      count += dir.second;
    }
  }

  long long result = count;
  printf("The solution for part 1 is: %lli \n", result);
}


void day7Part2()
{

  std::stack<std::string> dirStack;
  std::map<std::string, long long int> dirMap;

  std::string currentDir = "";

  std::vector<std::string> input;
  readDocument( DAY7_PATH, input );

  long long int usedSpace = std::numeric_limits<long long int>::min();

  for ( auto& line : input )
  {
    std::vector<std::string>simbolsLine;
    splitString( line, ' ', simbolsLine );

    if ( simbolsLine.front() == "$" && simbolsLine[1] == "cd" )
    {
      if ( simbolsLine[2] == ".." )
      {
        dirStack.pop();
        currentDir = dirStack.top();
      }
      else
      {
        currentDir.append( "/" );
        currentDir.append( simbolsLine[2] );
        dirStack.push( currentDir );
        dirMap[currentDir] = 0;
      }
    }
    else if ( simbolsLine.front() != "$" && simbolsLine.front().find_first_not_of( "0123456789" ) == std::string::npos )
    {
      dirMap[currentDir] += std::stoll( simbolsLine.front() );
      usedSpace = std::max( dirMap[currentDir], usedSpace );
  
      // Add to all the parent directories
      std::stack<std::string> auxStack;
      auxStack.push( dirStack.top() );
      dirStack.pop();
      while ( !dirStack.empty() )
      {
        auxStack.push( dirStack.top() );
        dirMap[dirStack.top()] += std::stoll( simbolsLine.front() );
        usedSpace = std::max( dirMap[dirStack.top()], usedSpace );
        dirStack.pop();
      }
      while ( !auxStack.empty() )
      {
        dirStack.push( auxStack.top() );
        auxStack.pop();
      }
    }
  }
  
  const long long int totalDiskSize = 70000000;
  const long long int totalNeedSpace = 30000000;
  const long long int needToRemove = usedSpace - ( totalDiskSize - totalNeedSpace );

  long long int removedDisk = std::numeric_limits<long long int>::max();
  
  if ( needToRemove > 0 )
  {
    for ( auto& dir : dirMap )
    {
      if ( dir.second >= needToRemove )
      {
        removedDisk = std::min( removedDisk, dir.second );
      }
    }
  }

  
  printf("The solution for part 2 is: %lli \n", removedDisk );
}
