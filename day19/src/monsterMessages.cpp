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

static const std::regex finalExpr( "\"(\\w)\"" );
static const std::regex orExpr( "(.*) \\| (.*)" );

struct Rule
{
  int ruleId;
  std::vector<std::string> followRules;
  Rule() {};
  Rule( int ruleId, std::string value ) : ruleId( ruleId ) 
  {
    parseRule( value );
  };

  bool isTerminal() 
  {
    for ( auto& valid : followRules )
    {
      std::regex validExpr( "[ab]+" );
      std::smatch sm;
      if ( !std::regex_match( valid, sm, validExpr ) )
        return false;
    }
    return true;
  }

  void parseRule( std::string& rule )
  {
    std::smatch sm;
    if ( std::regex_search( rule, sm, finalExpr ) )
    {
      followRules = { sm[1].str() };
    }
    else if ( std::regex_search( rule, sm, orExpr ) )
    {
      followRules.push_back( sm[1].str() );
      followRules.push_back( sm[2].str() );
    }
    else
    {
      followRules.push_back( rule );
    }
  }
  
  int getNextRule()
  {
    for ( auto& rule : followRules )
    {
      std::regex n1Expr( "(\\d+)(.*)?" );
      std::regex n2Expr( "[ab]+ (\\d+)(.*)?" );
      std::smatch sm;
      if ( std::regex_search( rule, sm, n1Expr ) )
      {
        return std::stoi( sm[1].str());
      }
      else if ( std::regex_search( rule, sm, n1Expr ) )
      {
        return std::stoi( sm[2].str() );
      }
    }
    return -1;
  }

  void replaceRule( int r, const std::vector<std::string>& values )
  {
    std::vector<std::string> auxFollowRules;
    for ( auto& rule : followRules )
    {
      auto found = rule.find( std::to_string( r ));
      if ( found == std::string::npos )
      {
        auxFollowRules.push_back( rule );
        continue;
      }

      for ( auto& value : values )
      {
        std::string auxRule = rule;
        found = auxRule.find( std::to_string( r ) );
        while ( found != std::string::npos )
        {
          std::string before = auxRule.substr( 0, found );
          std::string after = auxRule.substr( found + std::to_string( r ).length() );
          auxRule = before + " " + value + " " + after;
          found = auxRule.find( std::to_string( r ) );
        }
        auxFollowRules.push_back( auxRule );
      }
    }
    followRules = auxFollowRules;
  }
};

void evaluate( Rule& rule, std::map<int, Rule>& rules )
{
  bool isTerminal = rule.isTerminal();
  if ( isTerminal )
    return;

  while ( !isTerminal )
  {
    int nextRule = rule.getNextRule();
    if ( nextRule == -1 )
      return;

    evaluate( rules[nextRule], rules );
    rule.replaceRule( nextRule, rules[nextRule].followRules );
    isTerminal = rule.isTerminal();
  }
}


void adventDay19()
{
  // Open numbers file
  std::ifstream myfile( FILE_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file found" << std::endl;
    return;
  }

  std::vector<Rule> rules;
  std::map<int, Rule> mapRules;
  std::vector<std::string> words;
  std::string line;
  bool isRule = true;
  while ( getline( myfile, line ) )
  {
    if ( line == "" )
    {
      isRule = false;
      continue;
    }
      

    if ( isRule )
    {
      std::regex expr( "(\\d+): (.*)" );
      std::smatch sm;
      if ( std::regex_search( line, sm, expr ) )
      {
        Rule auxRule = Rule( std::stoi( sm[1].str() ), sm[2].str() );
        rules.push_back( auxRule );
        mapRules.insert( { auxRule.ruleId, auxRule } );
      }
    }
    else
    {
      words.push_back( line );
    }
  }
  if ( rules.empty() || words.empty() )
  {
    std::cout << "Error, no valid input file" << std::endl;
    return;
  }

  std::sort( rules.begin(), rules.end(), []( const Rule& rule1, const Rule& rule2 ) { return rule1.ruleId < rule2.ruleId; } );

  evaluate( mapRules[0], mapRules );

  std::for_each( mapRules[0].followRules.begin(), mapRules[0].followRules.end(), []( std::string& aux ) 
  {
    aux.erase( std::remove( aux.begin(), aux.end(), ' ' ), aux.end() );
  } );
  int result = 0;
  for ( auto& word : words )
  {
    auto found = std::find( mapRules[0].followRules.begin(), mapRules[0].followRules.end(), word );
    if ( found != mapRules[0].followRules.end() )
    {
      result++;
    }
  }
  std::cout << "Part 1:  " << result << std::endl;
  
  std::cout << "Part 2:  " << result << std::endl;
  //std::cout << "Part 2:" << result << std::endl;

}



int main( int argc, char* argv[] )
{
  adventDay19();
}
