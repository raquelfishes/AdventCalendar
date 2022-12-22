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

void day20Part1()
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
      Value aux= *it;

      int steps = std::abs(it->val) % ( input.size() - 1 );
      int currPosition = std::distance(listInput.begin(), it);
      int newPosition;
      if (it->val >= 0)
      {
        newPosition = currPosition + steps;
        if (newPosition >= input.size())
        {
          newPosition = newPosition - ( input.size());
        }
      }
      else
      {
        newPosition = currPosition - steps;
        if (newPosition <= 0)
        {
          newPosition = input.size() - 1 - std::abs(newPosition);
        }
      }
      auto newIt = listInput.begin();
      std::advance( newIt, newPosition+1 );
      listInput.insert( newIt, aux );
      listInput.erase( it );
    }
  }
  
  auto it0 = std::find_if( listInput.begin(), listInput.end(), []( const Value& v ) {return v.val == 0; } );
  int pos0 = std::distance( listInput.begin(), it0 );
  
  int sum= 0;
  for (int i = 1; i <= 3; ++i)
  {
    it = listInput.begin();
    int advance1k = ( pos0 + (1000*i) ) % ( input.size() );
    std::advance(it, advance1k);
    sum += it->val;
  }
  
  long long result = sum;
  printf("The solution for part 1 is: %lli \n", result);
}


void day20Part2()
{
  Index = 0;
  std::vector<Value> input;
  readDocument<Value>(DAY20_TEST_PATH, input);

  const long long decryptKey = 811589153;
  std::for_each(input.begin(), input.end(), [&] (Value& v) { v.val *= decryptKey; });

  std::list<Value> listInput(input.begin(), input.end());

  auto it = listInput.begin();
  for (int j = 0; j < 10; ++j)
  {
    std::cout << "!!!!!Round " << std::to_string(j) << std::endl;
    for (int i = 0; i < input.size(); ++i)
    {
      std::cout << "##Iteration " << std::to_string(i) << std::endl;
      it = std::find_if(listInput.begin(), listInput.end(), [i] (const Value& v) { return v.id == i; });
      if (it->id == i)
      {
        Value aux = *it;

        long long steps = std::abs(it->val) % ( input.size() - 1 );
        long long currPosition = std::distance(listInput.begin(), it);
        long long newPosition;
        if (it->val >= 0)
        {
          newPosition = currPosition + steps;
          if (newPosition >= input.size())
          {
            newPosition = newPosition - ( input.size() );
          }
        }
        else
        {
          newPosition = currPosition - steps;
          if (newPosition <= 0)
          {
            newPosition = input.size() - 1 - std::abs(newPosition);
          }
        }
        auto newIt = listInput.begin();
        std::advance(newIt, newPosition + 1);
        listInput.insert(newIt, aux);
        listInput.erase(it);
        std::for_each(listInput.begin(), listInput.end(), [] (const Value& v) { std::cout << v.val << " "; });
        std::cout << " " << std::endl;
      }
    }
  }

  auto it0 = std::find_if(listInput.begin(), listInput.end(), [] (const Value& v) { return v.val == 0; });
  int pos0 = std::distance(listInput.begin(), it0);

  long long sum = 0;
  for (int i = 1; i <= 3; ++i)
  {
    it = listInput.begin();
    int advance1k = ( pos0 + ( 1000 * i ) ) % ( input.size() );
    std::advance(it, advance1k);
    sum += it->val;
  }

  long long result = sum;
  printf("The solution for part 2 is: %lli \n", result);
}





///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

