#include "std_includes.h"
#include "resource.h"
#include "utils.h"


std::vector<std::string> rockPaperScissors = { "A", "B", "C" };

bool isWin( std::string a, std::string b )
{
  if ( a == "A" && b == "B" ) return true;
  if ( a == "B" && b == "C" ) return true;
  if ( a == "C" && b == "A" ) return true;
  return false;
}

bool isDraw( std::string a, std::string b )
{
  if ( a == b ) return true;
  return false;
}

bool isLoss( std::string a, std::string b )
{
  if ( a == "A" && b == "C" ) return true;
  if ( a == "B" && b == "A" ) return true;
  if ( a == "C" && b == "B" ) return true;
  return false;
}

int optionScore( std::string a )
{
  if ( a == "A" ) return 1;
  if ( a == "B" ) return 2;
  if ( a == "C" ) return 3;
  return 0;
}

int getScore( std::string a, std::string b )
{
  int score = 0;

  if ( isWin(a,b) ) score += 6;
  if ( isDraw( a, b ) ) score += 3;
  if ( isLoss( a, b ) ) score += 0;

  score += optionScore( b );

  return score;
}

std::string convertOption( std::string a )
{
  if ( a == "X" ) return "A";
  if ( a == "Y" ) return "B";
  if ( a == "Z" ) return "C";
  return "";
}

// Column 1: A = Rock | B = Paper | C = Scissors
// Column 2: X = Rock | Y = Paper | Z = Scissors
// Score round : Win = 6 | Draw = 3  | Loss = 0
// Score option: Rock = 1 | Paper = 2 | Scissors = 3

void day2Part1()
{
  std::vector<std::string> input;
  readDocument<std::string>( DAY2_PATH, input );

  int totalScore = 0;
  for ( auto& line : input )
  {
    std::vector<std::string> parts;
    splitStringByChar( line, ' ', parts );

    std::string newOption = convertOption( parts[1] );

    totalScore += getScore(parts[0], newOption );
  }

  long long result = totalScore;
  printf("The solution for part 1 is: %lli \n", result);
}

// Column 1: A = Rock | B = Paper | C = Scissors
// Column 2: X = Loss | Y = Draw | Z = Win
// Score round : Win = 6 | Draw = 3  | Loss = 0
// Score option: Rock = 1 | Paper = 2 | Scissors = 3

std::string getOption( std::string a, std::string b )
{
  if ( b == "X" )
  {
    if ( a == "A" ) return "C";
    if ( a == "B" ) return "A";
    if ( a == "C" ) return "B";
  }
  if ( b == "Y" ) return a;
  if ( b == "Z" )
  {
    if ( a == "A" ) return "B";
    if ( a == "B" ) return "C";
    if ( a == "C" ) return "A";
  }

  return "";
}

void day2Part2()
{
  std::vector<std::string> input;
  readDocument<std::string>( DAY2_PATH, input );

  int totalScore = 0;
  for ( auto& line : input )
  {
    std::vector<std::string> parts;
    splitStringByChar( line, ' ', parts );

    std::string option = getOption( parts[0], parts[1] );

    totalScore += getScore( parts[0], option );
  }

  long long result = totalScore;
  printf("The solution for part 2 is: %lli \n", result);
}
