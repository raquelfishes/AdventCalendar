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
  Player( const int& id, std::vector<int> cards ) : id_( id ), cards_(cards) {};

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
    //std::cout << "Player " << id_ << " plays: " << result << std::endl;
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

  bool checkHistory()
  {
    const int config = std::count ( history_.begin(), history_.end(), cards_);
    return config == 0;
  }

  void saveHistory()
  {
    history_.push_back( cards_ );
  }

  int id_;
  std::vector<int> cards_;

  std::vector<std::vector<int>> history_;

};


int game( const int g, Player& p1, Player& p2, const bool recursive=false )
{
  //std::cout << "== Game " << g << " ==" << std::endl;
  bool playing = true;
  int round = 1;
  while ( playing )
  {
    //std::cout << "-- Round " << round << " Game (" << g << ") --" << std::endl;

    if (recursive && ( !p1.checkHistory() || !p2.checkHistory() ))
    {
      //std::cout << " Player 1 wins round " << round << " of game " << g << "! " << std::endl;
      return p1.id_;
    }
    p1.saveHistory();
    p2.saveHistory();

    //p1.printDeck();
    //p2.printDeck();

    int play1 = p1.playCard();
    int play2 = p2.playCard();

    int winId = -1;
    // Is recursive ??
    if ( recursive && ( p1.cards_.size() >= play1 ) && ( p2.cards_.size() >= play2 ) )
    {
      //std::cout << "Playing a sub-game to determine the winner..." << std::endl;
      std::vector<int> cards1(p1.cards_.begin(), p1.cards_.begin()+play1);
      std::vector<int> cards2( p2.cards_.begin(), p2.cards_.begin() + play2 );
      winId = game( g+1, Player( p1.id_, cards1 ), Player( p2.id_, cards2 ), recursive );
      //std::cout << "...anyway, back to game " << g << "." << std::endl;
    }
    else if ( play1 > play2 )
    {
      winId = p1.id_;      
    }
    else if ( play2 > play1 )
    {
      winId = p2.id_;      
    }

    if ( winId == p1.id_ )
    {
      p1.addCards( std::vector<int>{play1, play2} );
    }
    else if ( winId == p2.id_ )
    {
      p2.addCards( std::vector<int>{play2, play1} );
    }

    //std::cout << " Player " << winId << " wins round " << round << " of game " << g << "! " << std::endl;
    playing = p1.hasCards() && p2.hasCards();
    round++;
    //std::cout << std::endl;
  }

  return p1.getResult() ? p1.id_ : p2.id_;

}


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
  
  //game( 1, player1, player2, false );
 
  //std::cout << "== Post-game results ==" << std::endl;

  //long long result = player1.getResult() + player2.getResult();
  //std::cout << "Part 1:  " << result << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  
  game( 1, player1, player2, true );

  std::cout << "== Post-game results ==" << std::endl;

  long long result = player1.getResult() + player2.getResult();

  std::cout << "Part 2:  " << result << std::endl;
  //std::cout << "Part 2:" << result << std::endl;

}



int main( int argc, char* argv[] )
{
  adventDay22();
}
