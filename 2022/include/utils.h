#pragma once


#include "std_includes.h"


bool splitStringByChar(const std::string value, const char c, std::vector<std::string>& splited );
bool splitStringByString( const std::string& value, const std::string& del, std::vector<std::string>& splited );

bool splitByRegex( const std::string line, const std::string regex, std::vector<std::string>& values );
bool splitByRegex(const std::string line, const std::regex regex, std::vector<std::string>& values);

bool matchRegex( const std::string line, const std::string regex);

template<typename T>
bool readDocument(const std::string path, std::vector<T>& values)
{
  // Open numbers file
  std::ifstream myfile(path);
  if (!myfile.is_open())
  {
    fprintf(stderr, "readDocument: Error, no file founded %s\n", path.c_str());
    return false;
  }

  std::string line;
  while (getline(myfile, line))
  {
    values.push_back(T(line));
  }

  myfile.close();
}



template<typename T>
bool readDocumentSeveralLines( const std::string path, const int numLines, std::vector<T>& values )
{
  // Open numbers file
  std::ifstream myfile( path );
  if( !myfile.is_open() )
  {
    fprintf( stderr, "readDocument: Error, no file founded %s\n", path.c_str() );
    return false;
  }

  std::string line;
  int currLines = 0;
  std::vector<std::string> currLinesToProcess;
  while( getline( myfile, line ) )
  {
    if ( line.empty() )
    {
      values.push_back( T( currLinesToProcess ) );
      currLinesToProcess.clear();
      currLines = 0;      
    }
    else if( currLines < numLines )
    {
      currLinesToProcess.push_back( line );
      currLines++;
    }
  }
  values.push_back( T( currLinesToProcess ) );

  myfile.close();
}

template<typename T>
bool readDocumentUntilEmptyLine( const std::string path, std::vector<T>& values )
{
  // Open numbers file
  std::ifstream myfile( path );
  if( !myfile.is_open() )
  {
    fprintf( stderr, "readDocument: Error, no file founded %s\n", path.c_str() );
    return false;
  }

  std::string line;
  while( getline( myfile, line ) )
  {
    if( line.empty() )
      break;
    values.push_back( T( line ) );
  }

  myfile.close();
}

template<typename T>
bool readDocumentFromEmptyLine( const std::string path, std::vector<T>& values )
{
  // Open numbers file
  std::ifstream myfile( path );
  if( !myfile.is_open() )
  {
    fprintf( stderr, "readDocument: Error, no file founded %s\n", path.c_str() );
    return false;
  }

  std::string line;
  bool foundEmptyLine = false;
  while( getline( myfile, line ) )
  {
    if( line.empty() )
    {
      foundEmptyLine = true;
      continue;
    }
      
    if ( foundEmptyLine )
      values.push_back( T( line ) );
  }

  myfile.close();
}


int char2int(const char c);
int charLowerCase2int( const char c );
int charUpperCase2int( const char c );

bool isCharLowerCase( const char c );
bool isCharUpperCase( const char c );

bool isUpperCase(const std::string& s);
bool isLowerCase(const std::string& s);
bool isAllDigits(const std::string& s);


