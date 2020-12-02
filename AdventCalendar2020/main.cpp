
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

// Way of use: 
// Arguments: 
// Day of advent Calendar (1..25)

struct PassFormat
{
  int min;
  int max;
  char letter;
  std::string password;
};


void adventDay1()
{
  // Open numbers file
  std::ifstream myfile("day1.txt");
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file finded" << std::endl;
    return;
  }

  std::vector<int> numbers;
  std::string number;
  while ( getline( myfile, number ) )
  {  //read data from file object and put it into string.
    numbers.push_back( std::stoi(number) );
  }
  if ( numbers.empty() )
  {
    std::cout << "Error, no numbers at file" << std::endl;
  }

  // Part 1:
  for ( auto i = 0; i < numbers.size(); ++i )
  {
    for ( auto j = i + 1; j < numbers.size(); ++j )
    {
      auto sum = numbers[i] + numbers[j];
      if ( sum == 2020 )
      {
        std::cout << "Part1: Success!!! Numbers found: " << numbers[i] << "  " << numbers[j] << std::endl;
        auto mult = numbers[i] * numbers[j];
        std::cout << "Result Part1: " << mult << std::endl;
      }
    }
  }

  // Part 2:
  for ( auto i = 0; i < numbers.size(); ++i )
  {
    for ( auto j = i + 1; j < numbers.size(); ++j )
    {
      for ( auto k = j + 1; k < numbers.size(); ++k )
      {
        auto sum = numbers[i] + numbers[j] + numbers[k];
        if ( sum == 2020 )
        {
          std::cout << "Part2: Success!!! Numbers found: " << numbers[i] << "  " << numbers[j] << "  " << numbers[k] << std::endl;
          auto mult = numbers[i] * numbers[j] * numbers[k];
          std::cout << "Result: " << mult << std::endl;
        }
      }
    }
  }
}


void adventDay2()
{
  // Open numbers file
  std::ifstream myfile( "day2.txt" );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file finded" << std::endl;
    return;
  }

  std::vector<PassFormat> passWords;
  std::string pass;
  while ( getline( myfile, pass ) )
  { //read data from file object and put it into string.
    std::stringstream ss( pass );
    std::string value;
    std::vector<std::string> values;
    while ( getline( ss, value, ' ' ) )
    {
      values.push_back( value );
    }
    if ( values.size() != 3 )
    {
      std::cout << "Error reading line, wrong password format" << std::endl;
    }

    // Fist value, range, need to be also splited
    std::stringstream ssRange( values[0] );
    std::string range;
    std::vector<int> rangeVector;
    while ( getline( ssRange, range, '-' ) )
    {
      rangeVector.push_back( std::stoi( range ) );
    }
    if ( rangeVector.size() != 2 )
    {
      std::cout << "Error reading range, wrong password format" << std::endl;
    }

    PassFormat passFormat;
    passFormat.min = rangeVector[0];
    passFormat.max = rangeVector[1];
    passFormat.letter = values[1][0];
    passFormat.password = values[2];
    passWords.push_back( passFormat );
  }
  if ( passWords.empty() )
  {
    std::cout << "Error, no passwords at file" << std::endl;
  }

  // Part 1
  unsigned int numberOfCorrectPass = 0;
  for ( auto pass : passWords )
  {
    size_t n = std::count( pass.password.begin(), pass.password.end(), pass.letter );
    if ( n >= pass.min && n <= pass.max )
    {
      numberOfCorrectPass++;
    }
  }
  std::cout << "Part1: The number of valid passwords is: " << numberOfCorrectPass  << std::endl;

  // Part 2
  numberOfCorrectPass = 0;
  for ( auto pass : passWords )
  {
    const bool firstChar = pass.password[pass.min-1] == pass.letter;
    const bool secondChar = pass.password[pass.max-1] == pass.letter;
    if ( firstChar ^ secondChar )
    {
      numberOfCorrectPass++;
    }
  }
  std::cout << "Part2: The number of valid passwords is: " << numberOfCorrectPass << std::endl;


}


int main( int argc, char* argv[] )
{
  if ( argc < 2 )
  {
    // At least the advent day
    std::cout << "Please insert advent day" << std::endl;
  }

  auto value = std::stoi(argv[1]);
  switch ( value )
  {
    case 1:
      adventDay1();
      break;
    case 2:
      adventDay2();
      break;
    default:
      break;
  }

}