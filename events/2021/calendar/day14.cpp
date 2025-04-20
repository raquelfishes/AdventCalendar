
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <numeric>

#include "resources.h"
#include "utils_2021.h"

static const int numIterations = 100;

typedef std::pair<int, int> coord;

template <typename T>
struct Grid
{
    Grid(std::vector<std::string> strValues)
    {
        std::string lineExpr("(\\d+),(\\d+)");
        sizeX = std::numeric_limits<int>::min();
        sizeY = std::numeric_limits<int>::min();
        for (auto &line : strValues)
        {
            if (matchRegex(line, lineExpr))
            {
                std::vector<std::string> values;
                splitString(line, ',', values);
                sizeX = std::max(sizeX, std::stoi(values[0]) + 1);
                sizeY = std::max(sizeY, std::stoi(values[1]) + 1);
            }
        }

        const int numValues = (sizeX) * (sizeY);
        values.resize(numValues, false);
        for (auto &line : strValues)
        {
            if (matchRegex(line, lineExpr))
            {
                std::vector<std::string> coords;
                splitString(line, ',', coords);
                int index = getIndex(std::stoi(coords[0]), std::stoi(coords[1]));
                values[index] = true;
            }
        }
    }

    coord getXY(const int index)
    {
        return std::pair<int, int>((index % sizeX), (index / sizeY));
    }

    int getIndex(const int x, const int y)
    {
        return x + y * sizeX;
    }

    int getIndex(const coord c)
    {
        return getIndex(c.first, c.second);
    }

    bool isValidCoord(const coord c)
    {
        bool validX = (0 <= c.first && c.first < sizeX);
        bool validY = (0 <= c.second && c.second < sizeY);

        return validX && validY;
    }

    bool isValidIndex(const int index)
    {
        return (index >= 0) && (index < (sizeX * sizeY));
    }

    void printGrid()
    {
        for (int i = 0; i < sizeY; ++i)
        {
            for (int j = 0; j < sizeX; ++j)
            {
                int index = getIndex(coord(j, i));
                if (values[index] == 0)
                    printf(".");
                else
                    printf("#");
            }
            printf("\n");
        }
        printf("\n");
        printf("\n");
    }

    int sizeX;
    int sizeY;
    std::vector<T> values;
};

struct Rules
{

    Rules(const std::vector<std::string> strValues)
    {
        std::string lineExpr("(\\w+) -> (\\w+)");
        for (auto &line : strValues)
        {
            if (matchRegex(line, lineExpr))
            {
                std::vector<std::string> values;
                splitByRegex(line, lineExpr, values);
                rules.insert(std::pair<std::string, char>(values[1], values[2][0]));
                rules.insert(std::pair<std::string, long long>(values[1], 0));
            }
        }
    }

    std::map<std::string, char> rules;
    std::map<std::string, long long> rulesCount;
};

void addCharToCount(const char c, std::map<char, long long> &mcount, const long long value)
{
    if (mcount.find(c) != std::end(mcount))
    {
        mcount[c] += value;
    }
    else
    {
        mcount[c] = value;
    }
}

void extendedPolymerizationPart1()
{
    std::string resourcePath = getResourcePath(2021, 14);
    std::vector<std::string> strInput;
    readDocument<std::string>(resourcePath, strInput);

    std::string polymerTemplate = strInput[0];

    Rules rls(strInput);

    std::map<char, long long> countById;
    std::for_each(polymerTemplate.begin(), polymerTemplate.end(), [&countById](char c)
                  { addCharToCount(c, countById, 1); });

    for (int i = 0; i < 10; ++i)
    {
        std::vector<std::string> newPolymerTemplate(polymerTemplate.size() - 1, "");

        std::transform(polymerTemplate.begin(), std::prev(polymerTemplate.end()),
                       std::next(polymerTemplate.begin()), newPolymerTemplate.begin(), [&](char c1, char c2)
                       {
      std::string ruleId = "";
      ruleId.push_back( c1 );
      ruleId.push_back( c2 );
      char ruleChar = rls.rules[ruleId];
      addCharToCount( ruleChar, countById,1 );
      std::string aux;
      aux.push_back( c1 );
      aux.push_back( ruleChar );
      aux.push_back( c2 );
      return aux; });

        polymerTemplate = newPolymerTemplate[0];

        std::for_each(std::next(newPolymerTemplate.begin()), newPolymerTemplate.end(), [&polymerTemplate](const std::string str)
                      { polymerTemplate.append(str.substr(1)); });
        // std::transform( std::next( newPolymerTemplate.begin() ), newPolymerTemplate.end(),
        //                 std::back_inserter( polymerTemplate ), [] ( const std::string str ) { return str/*str.substr( 1 )*/; } );

        printf("%s\n", polymerTemplate.c_str());
    }

    const auto [min, max] = std::minmax_element(countById.begin(), countById.end(), [](auto &p1, auto &p2)
                                                { return p1.second < p2.second; });

    // printf( newPolymerTemplate.c_str() );

    long long result = max->second - min->second;
    printf("The solution for part 1 is: %lld \n", result);
}

void initializeRulesTemplate(const std::string &str, Rules &rls)
{
    std::vector<char> aux(str.size());
    std::transform(str.begin(), std::prev(str.end()),
                   std::next(str.begin()), aux.begin(), [&](char c1, char c2)
                   {
    std::string ruleId = "";
    ruleId.push_back( c1 );
    ruleId.push_back( c2 );
    ++rls.rulesCount[ruleId];
    return '.'; });
}

void tickRules(Rules &rls, std::map<char, long long> &countById)
{
    std::map<std::string, long long> newRulesCount(rls.rulesCount);
    std::for_each(rls.rulesCount.begin(), rls.rulesCount.end(), [&](auto &p)
                  {
    if ( rls.rules.find( p.first ) != rls.rules.end() )
    {
      char c = rls.rules[p.first];
      std::string ruleId1 = "";
      ruleId1.push_back( p.first[0] );
      ruleId1.push_back( c );

      std::string ruleId2 = "";
      ruleId2.push_back( c );
      ruleId2.push_back( p.first[1] );

      newRulesCount[ruleId1] += p.second;
      newRulesCount[ruleId2] += p.second;
      newRulesCount[p.first] -= p.second;
      addCharToCount( c, countById, p.second );
    } });

    rls.rulesCount = newRulesCount;
}

void extendedPolymerizationPart2()
{
    std::string resourcePath = getResourcePath(2021, 14);
    std::vector<std::string> strInput;
    readDocument<std::string>(resourcePath, strInput);

    std::string polymerTemplate = strInput[0];

    std::map<char, long long> countById;
    std::for_each(polymerTemplate.begin(), polymerTemplate.end(), [&countById](char c)
                  { addCharToCount(c, countById, 1); });

    Rules rls(strInput);
    initializeRulesTemplate(polymerTemplate, rls);

    for (int i = 0; i < 40; i++)
    {
        tickRules(rls, countById);
    }

    const auto [min, max] = std::minmax_element(countById.begin(), countById.end(), [](auto &p1, auto &p2)
                                                { return p1.second < p2.second; });

    // printf( newPolymerTemplate.c_str() );

    long long result = max->second - min->second;
    printf("The solution for part 2 is: %lld \n", result);
}
