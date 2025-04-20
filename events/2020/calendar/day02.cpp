#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "resources.h"

struct PassFormat
{
    int min;
    int max;
    char letter;
    std::string password;
};

void adventDay2()
{
    std::string resourcePath = getResourcePath(2020, 2);
    // Open numbers file
    std::ifstream myfile(resourcePath);
    if (!myfile.is_open())
    {
        std::cout << "Error, no file found" << std::endl;
        return;
    }

    std::vector<PassFormat> passWords;
    std::string pass;
    while (getline(myfile, pass))
    { // read data from file object and put it into string.
        std::stringstream ss(pass);
        std::string value;
        std::vector<std::string> values;
        while (getline(ss, value, ' '))
        {
            // PassFormat passFormat;
            // char* cstr = new char[value.length() + 1];
            // strcpy( cstr, value.c_str() );
            // char* pch = strtok( cstr, " :-" );
            // int id = 0;
            // while ( pch != NULL )
            //{
            //
            //   pch = strtok( NULL, " ,.-" );
            // }
            //// do stuff
            // delete[] cstr;
            values.push_back(value);
        }
        if (values.size() != 3)
        {
            std::cout << "Error reading line, wrong password format" << std::endl;
        }

        // Fist value, range, need to be also splited
        std::stringstream ssRange(values[0]);
        std::string range;
        std::vector<int> rangeVector;
        while (getline(ssRange, range, '-'))
        {
            rangeVector.push_back(std::stoi(range));
        }
        if (rangeVector.size() != 2)
        {
            std::cout << "Error reading range, wrong password format" << std::endl;
        }

        PassFormat passFormat;
        passFormat.min = rangeVector[0];
        passFormat.max = rangeVector[1];
        passFormat.letter = values[1][0];
        passFormat.password = values[2];
        passWords.push_back(passFormat);
    }
    if (passWords.empty())
    {
        std::cout << "Error, no passwords at file" << std::endl;
    }

    // Part 1
    unsigned int numberOfCorrectPass = 0;
    for (auto pass : passWords)
    {
        size_t n = std::count(pass.password.begin(), pass.password.end(), pass.letter);
        if (n >= pass.min && n <= pass.max)
        {
            numberOfCorrectPass++;
        }
    }
    std::cout << "Part1: The number of valid passwords is: " << numberOfCorrectPass << std::endl;

    // Part 2
    numberOfCorrectPass = 0;
    for (auto pass : passWords)
    {
        const bool firstChar = pass.password[pass.min - 1] == pass.letter;
        const bool secondChar = pass.password[pass.max - 1] == pass.letter;
        if (firstChar ^ secondChar)
        {
            numberOfCorrectPass++;
        }
    }
    std::cout << "Part2: The number of valid passwords is: " << numberOfCorrectPass << std::endl;
}

int main(int argc, char *argv[])
{
    adventDay2();
}