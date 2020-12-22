#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <regex>
#include <numeric>
#include <limits>

#include "resource.h"


class Player 
{
public:
  Player() = default;
  Player( const int& id ) : id_( id ) {};

  void addCards( const std::vector<int>& cards )
  {
    cards_.insert( cards_.end(), cards.begin(), cards.end() );
  }

  void addCard( const int card )
  {
    cards_.push_back( card );
  }

  bool hasCards()
  {
    return !cards_.empty();
  }

  int playCard()
  {
    int result = cards_.front();
    cards_.erase( cards_.begin() );
    std::cout << "Player " << id_ << " plays: " << result << std::endl;
    return result;
  }

  long long getResult()
  {
    long long result = 0;
    for ( int i = 0; i < cards_.size(); ++i )
    {
      result += cards_[cards_.size() - 1 - i] * ( i+1 );
    }
    return result;
  }

  void printDeck()
  {
    std::cout << "Player " << id_ << "'s deck: ";
    for ( const auto& i : cards_ )
      std::cout << i << ' ';
    std::cout << std::endl;

  }

  int id_;
  std::vector<int> cards_;

};


void adventDay22()
{
  // Open numbers file
  std::ifstream myfile( FILE_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file found" << std::endl;
    return;
  }

  Player player1(1);
  Player player2(2);


  std::map<int, Player> players;
  std::string line;
  std::regex expr( "Player (\\d+):" );
  std::smatch sm;
  int playerId = -1;
  while ( getline( myfile, line ) )
  {
    if ( line == "" )
    {
      continue;
    }
    if ( std::regex_search( line, sm, expr ) )
    {
      playerId = std::stoi( sm[1].str() );
      continue;
    }
    if ( playerId == 1 )
    {
      player1.addCard( std::stoi( line ) );
    }
    else if ( playerId == 2 )
    {
      player2.addCard( std::stoi( line ) );
    }
  }
  

  for ( auto& player : players )
  {
    player.second.id_ = player.first;
  }

  bool playing = true;
  int round = 1;
  while ( playing )
  {
    std::cout << "-- Round " << round << " --" << std::endl;

    player1.printDeck();
    player2.printDeck();

    int play1 = player1.playCard();
    int play2 = player2.playCard();

    if ( play1 > play2 )
    {
      player1.addCards( std::vector<int>{play1, play2} );
      std::cout << " Player 1 wins the round! " << std::endl;
    }
    else
    {
      player2.addCards( std::vector<int>{play2, play1} );
      std::cout << " Player 2 wins the round! " << std::endl;
    }
    playing = player1.hasCards() && player2.hasCards();
    std::cout << " " << std::endl;
  }

  std::cout << "== Post-game results ==" << std::endl;

  long long result = player1.getResult() + player2.getResult();
  std::cout << "Part 1:  " << result << std::endl;
  


  std::cout << "Part 2:  " << result << std::endl;
  //std::cout << "Part 2:" << result << std::endl;

}



int main( int argc, char* argv[] )
{
  adventDay22();
}
