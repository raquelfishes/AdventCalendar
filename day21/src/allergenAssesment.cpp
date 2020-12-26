#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <regex>
#include <numeric>
#include <limits>

#include "resource.h"


struct Food
{
  std::vector<std::string> ingredients;
  std::vector<std::string> allergens;

  bool containAllergen( const std::string& aller ) const
  {
    return std::find( allergens.begin(), allergens.end(), aller ) != allergens.end();
  }

  void removeAllergen( const std::string aller )
  {
    auto found = std::find( allergens.begin(), allergens.end(), aller );
    if ( found != allergens.end() )
    {
      allergens.erase( found );
    }
  }


  bool containIngredient( const std::string& ingre ) const
  {
    return std::find( ingredients.begin(), ingredients.end(), ingre ) != ingredients.end();
  }

  void removeIngredient( const std::string ingre )
  {
    auto found = std::find( ingredients.begin(), ingredients.end(), ingre );
    if ( found != ingredients.end() )
    {
      ingredients.erase( found );
    }
  }

};


void adventDay21()
{
  // Open numbers file
  std::ifstream myfile( FILE_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file found" << std::endl;
    return;
  }

  std::vector<Food> foods;
  std::set<std::string> ingredients;
  std::set<std::string> allergens;
  std::string line;
  std::regex expr( "(.*) \\(contains (.*)\\)" );
  std::smatch sm;
  while ( getline( myfile, line ) )
  {
    if ( std::regex_search( line, sm, expr ) )
    {
      Food food;
      // Get ingredients
      std::stringstream ssIng( sm[1].str() );
      std::string valueIng;
      while ( getline( ssIng, valueIng, ' ' ) )
      {
        food.ingredients.push_back( valueIng );
        ingredients.insert( valueIng );
      }
      // Get allergens
      std::stringstream ssA( sm[2].str() );
      std::string valueA;
      while ( getline( ssA, valueA, ',' ) )
      {
        if ( valueA.front() == ' ' ) valueA.erase( valueA.begin() );
        food.allergens.push_back( valueA );
        allergens.insert( valueA );
      }
      foods.push_back( food );
    }

  }
  if ( foods.empty() )
  {
    std::cout << "Error, no valid input file" << std::endl;
    return;
  }

  std::map<std::string, std::string> listAllergens;

  const int ingredientsSize = ingredients.size();
  std::set<std::string> noAllergenIngre( ingredients );
  std::vector<Food> auxFoods( foods );
  while ( noAllergenIngre.size() != ingredientsSize - allergens.size() )
  {
    for ( const auto& aller : allergens )
    {
      std::vector<std::string> auxIngrAller;
      for ( auto& f : auxFoods )
      {
        if ( f.allergens.empty() )
          continue;

        if ( !f.containAllergen( aller ) )
          continue;

        if ( auxIngrAller.empty() )
        {
          auxIngrAller = f.ingredients;
        }
        else
        {
          auxIngrAller.erase( std::remove_if( auxIngrAller.begin(), auxIngrAller.end(), [&]( auto const& x )
          {
            return !f.containIngredient( x );
          } ), auxIngrAller.end() );
        }

      }
      if ( auxIngrAller.size() == 1 )
      {
        // Remove ingredient from full list
        noAllergenIngre.erase( auxIngrAller.front() );
        listAllergens[aller] = auxIngrAller.front();
        for ( auto& f : auxFoods )
        {
          f.removeIngredient( auxIngrAller.front() );
          f.removeAllergen( aller );
        }
      }
    }
  }

  int result=0;
  for ( auto& f : auxFoods )
  {
    result += f.ingredients.size();
  }
  std::cout << "Part 1:  " << result << std::endl;


  std::vector<std::string> allergensV( allergens.begin(), allergens.end() );
  std::sort( allergensV.begin(), allergensV.end() );
  std::stringstream resultStr;
  for ( const auto& a : allergensV )
  {
    resultStr << listAllergens[a] << ",";
  }
  
  std::cout << "Part 2:  " << resultStr.str() << std::endl;
  
}



int main( int argc, char* argv[] )
{
  adventDay21();
}
