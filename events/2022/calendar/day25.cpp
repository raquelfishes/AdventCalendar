#include "std_includes.h"
#include "resources.h"
#include "utils_2022.h"

long long convertFromSNAFU(const std::string &s)
{
    long long result = 0;
    for (int i = 0; i < s.length(); ++i)
    {
        long long powValue = pow(5, s.length() - 1 - i);
        char c = s[i];
        if (std::isdigit(c))
            result += char2int(c) * powValue;
        else if (c == '-')
            result -= powValue;
        else if (c == '=')
            result -= (powValue * 2);
    }
    return result;
}

std::string convertToSNAFU(long long value)
{
    std::string result = "";
    const int div = 5;

    while (value)
    {
        int aux = value % div;
        bool b = aux > 2;
        if (b)
        {
            if (aux == 3)
                result = '=' + result;
            ;
            if (aux == 4)
                result = '-' + result;
        }
        else
        {
            result = int2char(aux) + result;
        }
        value = (value / div) + b;
    }

    /*int idPow = 0;
    long long fishes = pow( 5, idPow );
    while( value > pow( 5, idPow ) )
    {
      idPow++;
      fishes = pow( 5, idPow );
    }

    if( value < ( 2 * pow( 5, idPow - 1 ) ) ) idPow--;

    long long auxValue=0;
    while( idPow >= 0 )
    {
      long long powValue = pow( 5, idPow );
      if( auxValue <= value )
      {
        int count = 0;
        while( auxValue < value )
        {
          auxValue += powValue;
          count++;
        }
        result.push_back( int2char( count ) );
      }
      else
      {
        char c = '-';
        auxValue -= powValue;
        if( auxValue > value )
        {
          auxValue -= powValue;
          c = '=';
        }
        result.push_back( c );
      }
      idPow--;
    }*/

    return result;
}

void day25Part1()
{
    std::string resourcePath = getResourcePath(2022, 25);
    std::vector<std::string> input;
    readDocument(resourcePath, input);

    long long decimalSum = 0;
    for (auto &value : input)
    {
        decimalSum += convertFromSNAFU(value);
    }

    std::string result = convertToSNAFU(decimalSum);

    std::string auxResult1 = convertToSNAFU(2022);
    std::string auxResult2 = convertToSNAFU(12345);
    std::string auxResult3 = convertToSNAFU(314159265);

    printf("The solution for part 1 is: %s \n", result.c_str());
}

void day25Part2()
{
    long long result = 0;
    printf("Merry christmas!!");
}
