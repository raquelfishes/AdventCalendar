#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>

#include "resources.h"

struct Passport
{
    std::string byr = ""; //( Birth Year )
    std::string iyr = ""; //( Issue Year )
    std::string eyr = ""; //( Expiration Year )
    std::string hgt = ""; //( Height )
    std::string hcl = ""; //( Hair Color )
    std::string ecl = ""; //( Eye Color )
    std::string pid = ""; //( Passport ID )
    std::string cid = ""; //( Country ID )

    //
    bool isValid()
    {
        return !byr.empty() && !iyr.empty() && !eyr.empty() && !hgt.empty() && !hcl.empty() && !ecl.empty() && !pid.empty();
    }

    bool isValidValues()
    {
        bool valid = true;
        valid &= byr.size() == 4 && (std::stoi(byr) >= 1920 && std::stoi(byr) <= 2002);
        valid &= iyr.size() == 4 && (std::stoi(iyr) >= 2010 && std::stoi(iyr) <= 2020);
        valid &= eyr.size() == 4 && (std::stoi(eyr) >= 2020 && std::stoi(eyr) <= 2030);

        std::regex hgtCmExp("(\\d+)cm");
        std::regex hgtInExp("(\\d+)in");
        std::smatch sm;
        valid &= (std::regex_search(hgt, sm, hgtCmExp) && (std::stoi(sm[1]) >= 150 && std::stoi(sm[1]) <= 193)) ||
                 (std::regex_search(hgt, sm, hgtInExp) && (std::stoi(sm[1]) >= 59 && std::stoi(sm[1]) <= 76));

        std::regex hclExp("#([a-f0-9]){6}");
        valid &= std::regex_match(hcl, sm, hclExp);
        valid &= ecl == "amb" || ecl == "blu" || ecl == "brn" || ecl == "gry" || ecl == "grn" || ecl == "hzl" || ecl == "oth";
        valid &= pid.size() == 9 && std::all_of(pid.begin(), pid.end(), [](char c)
                                                { return isdigit(c); });
        return valid;
    }
};

void adventDay4()
{
    std::string resourcePath = getResourcePath(2020, 4);
    // Open numbers file
    std::ifstream myfile(resourcePath);
    if (!myfile.is_open())
    {
        std::cout << "Error, no file found" << std::endl;
        return;
    }

    // std::vector<std::string> ids{ "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};
    std::vector<Passport> passport;
    passport.push_back(Passport()); // Initialize with an empty Passport
    std::string line;
    std::regex exp("(\\w+):(.*)");
    std::smatch sm;
    while (getline(myfile, line))
    {
        if (line == "")
        {
            passport.push_back(Passport()); // Add empty passport to full with info
        }
        else
        {
            // read data from file object and put it into string.
            //  Split by space
            std::stringstream ss(line);
            std::string value;
            std::vector<std::string> values;
            while (getline(ss, value, ' '))
            {
                if (std::regex_search(value, sm, exp))
                {
                    if (sm[1] == "byr")
                    {
                        passport[passport.size() - 1].byr = sm[2];
                    }
                    else if (sm[1] == "iyr")
                    {
                        passport[passport.size() - 1].iyr = sm[2];
                    }
                    else if (sm[1] == "eyr")
                    {
                        passport[passport.size() - 1].eyr = sm[2];
                    }
                    else if (sm[1] == "hgt")
                    {
                        passport[passport.size() - 1].hgt = sm[2];
                    }
                    else if (sm[1] == "hcl")
                    {
                        passport[passport.size() - 1].hcl = sm[2];
                    }
                    else if (sm[1] == "ecl")
                    {
                        passport[passport.size() - 1].ecl = sm[2];
                    }
                    else if (sm[1] == "pid")
                    {
                        passport[passport.size() - 1].pid = sm[2];
                    }
                    else if (sm[1] == "cid")
                    {
                        passport[passport.size() - 1].cid = sm[2];
                    }
                }
            }
        }
    }
    if (passport.empty())
    {
        std::cout << "Error, no passports at file" << std::endl;
    }

    int validPassports = 0;
    std::for_each(passport.begin(), passport.end(), [&validPassports](Passport &pass)
                  { 
    if ( pass.isValid() )
    {
      validPassports++;
    } });
    std::cout << "Part1: The number of valid passports are: " << validPassports << std::endl;

    validPassports = 0;
    std::for_each(passport.begin(), passport.end(), [&validPassports](Passport &pass)
                  {
    if ( pass.isValidValues() )
    {
      validPassports++;
    } });
    std::cout << "Part2: The number of valid passports are: " << validPassports << std::endl;
}
