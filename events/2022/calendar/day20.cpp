#include "std_includes.h"
#include "resource.h"
#include "utils.h"

int Index = 0;

struct Value
{
  Value() = default;

  Value( const std::string& s )
  {
    val = std::stoi( s );
    id = Index++;
  }
  Value (long long v, int id ): val(v), id(id){}
  
  bool operator==( const Value& v ) const 
  {
    return v.id == id;
  }

  long long val;
  int id = -1;
};


void mixList( std::list<Value>& listInput, const int listSize, const int roundCount )
{
  const bool print = false;
  if( print )
  {
    std::for_each( listInput.begin(), listInput.end(), []( const Value& v ) { std::cout << v.val << " "; } );
    std::cout << " " << std::endl;
  }
  
  for( int j = 0; j < roundCount; ++j )
  {
    if (print) std::cout << "!!!!!Round " << std::to_string( j ) << std::endl;
    auto it = listInput.begin();
    for( int i = 0; i < listSize; ++i )
    {
      if ( print ) std::cout << "##Iteration " << std::to_string( i ) << std::endl;
      it = std::find_if( listInput.begin(), listInput.end(), [i]( const Value& v ) {return v.id == i; } );
      if( it->id == i )
      {
        Value aux = *it;

        int steps = std::abs( aux.val ) % ( listSize-1 );
        auto newIt = listInput.erase( it );
        for( int k = 0; k < steps; ++k )
        {
          if( aux.val > 0 )
          {
            if( newIt == listInput.end() ) newIt = listInput.begin();
            newIt++;
          }
          if( aux.val < 0 )
          {
            if( newIt == listInput.begin() ) newIt = listInput.end();
            newIt--;
          }
        }
        if( aux.val < 0 && newIt == listInput.begin() ) newIt == listInput.end();
        if( aux.val > 0 && newIt == listInput.end() ) newIt == listInput.begin();
        listInput.insert( newIt, aux );
        if( print )
        {
          std::for_each( listInput.begin(), listInput.end(), []( const Value& v ) { std::cout << v.val << " "; } );
          std::cout << " " << std::endl;
        }
      }
    }
  }
}

long long computeResult( const std::list<Value>& listInput )
{
  auto it0 = std::find_if( listInput.begin(), listInput.end(), []( const Value& v ) {return v.val == 0; } );
  int pos0 = std::distance( listInput.begin(), it0 );

  long long sum = 0;
  for( int i = 1; i <= 3; ++i )
  {
    auto it = listInput.begin();
    int advance1k = ( pos0 + ( 1000 * i ) ) % ( listInput.size() );
    std::advance( it, advance1k );
    sum += it->val;
  }
  return sum;
}

void day20Part1()
{
  Index = 0;
  std::vector<Value> input;
  readDocument<Value>( DAY20_PATH, input );
  
  std::list<Value> listInput( input.begin(), input.end() );
  
  mixList( listInput, input.size(), 1 );
  long long result = computeResult(listInput);

  printf("The solution for part 1 is: %lli \n", result);
}


void day20Part2()
{
  Index = 0;
  std::vector<Value> input;
  readDocument<Value>(DAY20_PATH, input);

  const long long decryptKey = 811589153;
  std::for_each(input.begin(), input.end(), [&] (Value& v) { v.val *= decryptKey; });

  std::list<Value> listInput(input.begin(), input.end());

  mixList( listInput, input.size(), 10 );
  long long result = computeResult( listInput );
  printf("The solution for part 2 is: %lli \n", result);
}





///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

