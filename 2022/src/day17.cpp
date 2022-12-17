#include "std_includes.h"
#include "resource.h"
#include "utils.h"

typedef std::bitset<7> RockLine;
typedef std::vector<RockLine> Rock;

const std::vector<Rock> stones = {
  { RockLine( 0x1E ) },
  { RockLine( 0x8 ),  RockLine( 0x1C ), RockLine( 0x8 ) },
  { RockLine( 0x1C ), RockLine( 0x4 ),  RockLine( 0x4 ) },
  { RockLine( 0x10 ), RockLine( 0x10 ), RockLine( 0x10 ), RockLine( 0x10 ) },
  { RockLine( 0x18 ), RockLine( 0x18 ) }
};

bool checkMoveToStack( const Rock& stone, const Rock& stackRocks, const int line )
{
  for( int i = 0; i < stone.size(); ++i )
  {
    int checkNewLine = line + i;
    if( checkNewLine >= stackRocks.size() ) break;
    auto stackLine = stackRocks[checkNewLine];
    if( ( stackLine & stone[i] ).any() )
    {
      return false;
    }
  }
  return true;
}

bool checkMoveCurrent( const Rock& stone, const Rock& stackRock, const int line, const char c )
{
  bool canMove = true;
  Rock auxRock = stone;
  if ( c == '<' )
    std::for_each( auxRock.begin(), auxRock.end(), [&canMove]( RockLine& b ) {canMove &= ( b.count() == ( b << 1 ).count() ); } );
  else if ( c == '>' )
    std::for_each( auxRock.begin(), auxRock.end(), [&canMove]( RockLine& b ) {canMove &= ( b.count() == ( b >> 1 ).count() ); } );
  if( !canMove ) return false;
  if( c == '<' && canMove )
    std::for_each( auxRock.begin(), auxRock.end(), [&canMove]( RockLine& b ) {b <<= 1; } );
  if( c == '>' && canMove )
    std::for_each( auxRock.begin(), auxRock.end(), [&canMove]( RockLine& b ) {b >>= 1; } );

  canMove = checkMoveToStack( auxRock, stackRock, line );

  return canMove;
}

void day17Part1()
{
  std::vector<std::string> input;
  readDocument( DAY17_PATH, input );

  std::string inputStr = input.front();

  const int width = 7;
  const int emptyLines = 3;
  long long height = 3;
  int countRocks = 0;
  int lastRow = 0x7F;
  const int maxRocks = 2022;
  int idInput = 0;
  int idStone = 0;
  std::vector<RockLine> stackRocks;
  stackRocks.push_back( RockLine( 0x7F ) );

  while( countRocks < maxRocks )
  {
    auto currentRock = stones[( idStone++ ) % stones.size()];
    // Add 3 empty rows plus size of rock
    int currLine = stackRocks.size() + emptyLines;
    for( int i = 0; i < emptyLines+currentRock.size(); ++i ) stackRocks.push_back( RockLine() );
    bool testToDown = true;
    while( testToDown )
    {
      // Move rock (moving bits)
      char c = inputStr[(idInput++)%inputStr.size()];
      if( c == '<' )
      {
        bool canMove = checkMoveCurrent(currentRock, stackRocks, currLine, c);
        if( canMove ) 
          std::for_each( currentRock.begin(), currentRock.end(), [&canMove]( RockLine& b ) {b <<= 1; } );
      }
      else if( c == '>' )
      {
        bool canMove = checkMoveCurrent( currentRock, stackRocks, currLine, c );
        if( canMove )
          std::for_each( currentRock.begin(), currentRock.end(), [&canMove]( RockLine& b ) {b >>= 1; } );
      }
      /*
      std::cout << "|||||||||||||||||||||" << std::endl;;
      for( int i = currentRock.size() - 1; i >= 0; --i )
      {
        std::cout << '|' << currentRock[i].to_string( '.', '#' ) << '|' << std::endl;;
      }
      */

      // Check if the rock can go down;
      for( int i=0; i<currentRock.size(); ++i)
      {
        int checkNewLine = currLine - 1 + i;
        if( checkNewLine >= stackRocks.size() ) break;
        auto stackLine = stackRocks[checkNewLine];
        if( ( stackLine & currentRock[i] ).any() )
        {
          testToDown = false;
          break;
        }
      }
      if ( testToDown ) currLine--;
    }
    for( int i = 0; i < currentRock.size(); ++i )
    {
      stackRocks[currLine + i] |= currentRock[i];
    }
    while( stackRocks.back().none() ) stackRocks.pop_back();
    /*    printf( "New Rock!!%d\n", countRocks );
    for( int i=stackRocks.size()-1; i>=0; --i )
    {
      std::cout << '|'  << stackRocks[i].to_string('.', '#') << '|' << std::endl;;
    }
    */


    countRocks++;
  }

  long long result = stackRocks.size()-1;
  printf("The solution for part 1 is: %lli \n", result);
}


void day17Part2()
{
  std::vector<std::string> input;
  readDocument( DAY17_PATH, input );

  std::string inputStr = input.front();

  const int width = 7;
  const int emptyLines = 3;
  long long height = 3;
  int countRocks = 0;
  int lastRow = 0x7F;
  const long long maxRocks = 1000000000000;
  int idInput = 0;
  int idStone = 0;
  std::vector<RockLine> stackRocks;
  stackRocks.push_back( RockLine( 0x7F ) );
  std::map<RockLine, std::map<Rock, int>> cache;
  std::vector<int> heightMap( 7, 0 );

  while( countRocks < maxRocks )
  {
    auto currentRock = stones[( idStone++ ) % stones.size()];
    // Add 3 empty rows plus size of rock
    int currLine = stackRocks.size() + emptyLines;
    for( int i = 0; i < emptyLines + currentRock.size(); ++i ) stackRocks.push_back( RockLine() );
    bool testToDown = true;
    while( testToDown )
    {
      // Move rock (moving bits)
      char c = inputStr[( idInput++ ) % inputStr.size()];
      if( c == '<' )
      {
        bool canMove = checkMoveCurrent( currentRock, stackRocks, currLine, c );
        if( canMove )
          std::for_each( currentRock.begin(), currentRock.end(), [&canMove]( RockLine& b ) {b <<= 1; } );
      }
      else if( c == '>' )
      {
        bool canMove = checkMoveCurrent( currentRock, stackRocks, currLine, c );
        if( canMove )
          std::for_each( currentRock.begin(), currentRock.end(), [&canMove]( RockLine& b ) {b >>= 1; } );
      }
      /*
      std::cout << "|||||||||||||||||||||" << std::endl;;
      for( int i = currentRock.size() - 1; i >= 0; --i )
      {
        std::cout << '|' << currentRock[i].to_string( '.', '#' ) << '|' << std::endl;;
      }
      */

      // Check if the rock can go down;
      for( int i = 0; i < currentRock.size(); ++i )
      {
        int checkNewLine = currLine - 1 + i;
        if( checkNewLine >= stackRocks.size() ) break;
        auto stackLine = stackRocks[checkNewLine];
        if( ( stackLine & currentRock[i] ).any() )
        {
          testToDown = false;
          break;
        }
      }
      if( testToDown ) currLine--;
    }
    for( int i = 0; i < currentRock.size(); ++i )
    {
      stackRocks[currLine + i] |= currentRock[i];
    }
    while( stackRocks.back().none() ) stackRocks.pop_back();
    /*    printf( "New Rock!!%d\n", countRocks );
    for( int i=stackRocks.size()-1; i>=0; --i )
    {
      std::cout << '|'  << stackRocks[i].to_string('.', '#') << '|' << std::endl;;
    }
    */


    countRocks++;
  }

  long long result = stackRocks.size(); 
  printf("The solution for part 2 is: %lli \n", result);
}
