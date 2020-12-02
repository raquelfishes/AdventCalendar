
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Way of use: 
// Arguments: 
// Day of advent Calendar (1..25)



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