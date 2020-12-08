#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <numeric>

#include "resource.h"


struct Instruction
{
  std::string type;
  int value;
  bool visited = false;

  Instruction( std::string t, std::string sign, std::string val ) :
    type(t), visited(false) 
  {
    value = sign == "-" ? std::stoi( val ) * ( -1 ) : std::stoi( val );
  };
};

bool computeInstruction( std::vector<Instruction>& commands, int idx, int& accumulator )
{
  // Return true if ended instructions
  if ( idx >= commands.size() )
    return true;

  // Return false if infinity loop found
  if ( commands[idx].visited )
    return false;


  commands[idx].visited = true;
  if ( commands[idx].type == "nop" )
  {
    return computeInstruction( commands, ++idx, accumulator );
  }
  else if ( commands[idx].type == "acc" )
  {
    accumulator += commands[idx].value;
    return computeInstruction( commands, ++idx, accumulator );
  }
  else if ( commands[idx].type == "jmp" )
  {
    idx += commands[idx].value;
    return computeInstruction( commands, idx, accumulator );
  }
}

void adventDay5()
{
  // Open numbers file
  std::ifstream myfile( FILE_PATH );
  if ( !myfile.is_open() )
  {
    std::cout << "Error, no file found" << std::endl;
    return;
  }

  
  std::vector<Instruction> commands;
  std::string line;
  std::regex expr( "(\\w+) ([+-]{1})(\\d+)" );
  std::smatch sm;

  while ( getline( myfile, line ) )
  { 
    if ( std::regex_search( line, sm, expr ) )
    {
      Instruction inst( sm[1], sm[2], sm[3] );
      commands.push_back( inst );
    }    
  }
  if ( commands.empty() )
  {
    std::cout << "Error, no seats at file" << std::endl;
  }
  
  int accumulator = 0;
  computeInstruction( commands, 0, accumulator );
  std::cout << "Part1: The accumulator value before infinite loop is: " << accumulator << std::endl;
  
  // Clean visited attr
  std::for_each( commands.begin(), commands.end(), [] ( Instruction &instr )
  {
    instr.visited = false;
  } );

  for ( auto i = 0; i < commands.size(); ++i )
  {
    std::vector<Instruction> duplicate;
    std::copy( commands.begin(), commands.end(), std::back_inserter( duplicate ) );
    accumulator = 0;
    if ( commands[i].type == "jmp" )
    {
      duplicate[i].type = "nop";
      bool infinityLoop = computeInstruction( duplicate, 0, accumulator );
      if ( infinityLoop )
      {
        break;
      }
    }
  }

  std::cout << "Part2: The accumulator value of fixed code is: " << accumulator << std::endl;


}



int main( int argc, char* argv[] )
{
  adventDay5();
}