#include "std_includes.h"
#include "resource.h"
#include "utils.h"

int Index = 0;

struct Value
{
  Value() = default;

  Value( const std::string& s )
  {
    v = std::stoi( s );
    id = Index++;
  }
  Value ( int val, int id ): v(val), id(id){}
  
  bool operator==( const Value& v ) const 
  {
    return v.id == id;
  }

  int v;
  int id = -1;
};

void day20Part1()
{
  Index = 0;
  std::vector<Value> input;
  readDocument<Value>( DAY20_TEST_PATH, input );

  std::list<Value> listInput( input.begin(), input.end() );
  
  auto it = listInput.begin();
  for( int i = 0; i < input.size(); ++i )
  {
    it = std::find_if( listInput.begin(), listInput.end(), [i]( const Value& v ) {return v.id == i; } );
    if( it->id == i )
    {
      Value aux= *it;
      int newPosition = (std::distance( listInput.begin(), it) + it->v);
      newPosition = newPosition > 0 ? (newPosition % input.size()) : input.size() - 1 - ( std::abs(newPosition) % input.size() );
      auto newIt = listInput.begin();
      std::advance( newIt, newPosition+1 );
      listInput.insert( newIt, aux );
      listInput.erase( it );
    }
  }
  
  auto it0 = std::find_if( listInput.begin(), listInput.end(), []( const Value& v ) {return v.v == 0; } );
  int pos0 = std::distance( listInput.begin(), it0 );

  int sum= 0;
  it = listInput.begin();
  int advance1k = ( pos0 + 1000 ) % input.size();
  std::advance( it, advance1k );
  sum += it->v;
  it = listInput.begin();
  int advance2k = ( pos0 + 2000 ) % input.size();
  std::advance( it, advance2k );
  sum += it->v;
  it = listInput.begin();
  int advance3k = ( pos0 + 3000 ) % input.size();
  std::advance( it, advance3k );
  sum += it->v;

  long long result = sum;
  printf("The solution for part 1 is: %lli \n", result);
}


void day20Part2()
{
  Index = 0;
  std::vector<Value> input;
  readDocument<Value>( DAY20_PATH, input );

  std::list<Value> listInput( input.begin(), input.end() );

  auto it = listInput.begin();
  for( int i = 0; i < input.size(); ++i )
  {
    it = std::find_if( listInput.begin(), listInput.end(), [i]( const Value& v ) {return v.id == i; } );
    if( it->id == i )
    {
      Value aux = *it;
      listInput.erase( it );
      int newPosition = ( std::distance( listInput.begin(), it ) + it->v );
      newPosition = newPosition > 0 ? ( newPosition % input.size() ) : input.size() - 1 - ( std::abs( newPosition ) % input.size() );
      auto newIt = listInput.begin();
      std::advance( newIt, newPosition );
      listInput.insert( newIt, aux );
    }
  }

  auto it0 = std::find_if( listInput.begin(), listInput.end(), []( const Value& v ) {return v.v == 0; } );
  int pos0 = std::distance( listInput.begin(), it0 );

  int sum = 0;
  it = listInput.begin();
  int advance1k = ( pos0 + 1000 ) % input.size();
  std::advance( it, advance1k+1 );
  sum += it->v;
  it = listInput.begin();
  int advance2k = ( pos0 + 2000 ) % input.size();
  std::advance( it, advance2k-1 );
  sum += it->v;
  it = listInput.begin();
  int advance3k = ( pos0 + 3000 ) % input.size();
  std::advance( it, advance3k-1 );
  sum += it->v;

  long long result = sum;
  printf("The solution for part 2 is: %lli \n", result);
}
