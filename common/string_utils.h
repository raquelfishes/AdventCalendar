#pragma once
#include "std_includes.h"

int char2int(const char c);
char int2char( const int i );

int charLowerCase2int( const char c );
int charUpperCase2int( const char c );

bool isCharLowerCase( const char c );
bool isCharUpperCase( const char c );

bool isUpperCase(const std::string& s);
bool isLowerCase(const std::string& s);
bool isAllDigits(const std::string& s);

bool splitStringByChar(const std::string value, const char c, std::vector<std::string>& splited );
bool splitStringByString( const std::string& value, const std::string& del, std::vector<std::string>& splited );

bool splitByRegex( const std::string line, const std::string regex, std::vector<std::string>& values );
bool splitByRegex(const std::string line, const std::regex regex, std::vector<std::string>& values);

bool matchRegex( const std::string line, const std::string regex);


