#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <stdlib.h>
#include <stdio.h>

#include "adventdays_fwd.h"
#include "ansi_colors.h"
 



void paintAdventCalendar()
{
  printf( HGRN"Advent of Code\n" GRN"\ty(" HGRN"2021" GRN")" reset "\n" );

  printf( HBLK "                      ~   " CYN "~" HBLK"  ~ " CYN "~" HBLK "~ " CYN "~" HBLK "~" CYN "~~" HBLK "~" CYN "~~~~~~~~~~" );
  printf( reset "    1  " HYEL "**" reset "\n" );
  printf( HBLK "                                      '" CYN ". ' " YEL "..''''" );
  printf( reset "    2  " HYEL "**" reset "\n" );
  printf( "                                                 " );
  printf( reset "    3  " HYEL "**" reset "\n" );
  std::cout << "                                                   " << "  " << "4" << std::endl;
  std::cout << "                                                   " << "  " << "5" << std::endl;
  std::cout << "                                                   " << "  " << "6" << std::endl;
  std::cout << "                                                   " << "  " << "7" << std::endl;
  std::cout << "                                                   " << "  " << "8" << std::endl;
  std::cout << "                                                   " << "  " << "9" << std::endl;
  std::cout << "                                                   " << "  " << "10" << std::endl;
  std::cout << "                                                   " << "  " << "11" << std::endl;
  std::cout << "                                                   " << "  " << "12" << std::endl;
  std::cout << "                                                   " << "  " << "13" << std::endl;
  std::cout << "                                                   " << "  " << "14" << std::endl;
  std::cout << "                                                   " << "  " << "15" << std::endl;
  std::cout << "                                                   " << "  " << "16" << std::endl;
  std::cout << "                                                   " << "  " << "17" << std::endl;
  std::cout << "                                                   " << "  " << "18" << std::endl;
  std::cout << "                                                   " << "  " << "19" << std::endl;
  std::cout << "                                                   " << "  " << "20" << std::endl;
  std::cout << "                                                   " << "  " << "21" << std::endl;
  std::cout << "                                                   " << "  " << "22" << std::endl;
  std::cout << "                                                   " << "  " << "23" << std::endl;
  std::cout << "                                                   " << "  " << "24" << std::endl;
  std::cout << "                                                   " << "  " << "25" << std::endl;
}

int getDay()
{
  std::cout << "Introduce el dia que quieres ejecutar:";
  int day;
  std::cin >> day;
  std::cout << std::endl;
  return day;
}

#include <algorithm>

int checkSubList( const std:: vector<int> &A, const int n ) // 1 2 1 5 // 2 1 5 // 1 5
{
    if ( A.empty())
    {
        return 0;
    }

    int maxLength = 0;
    
    for ( int i=0; i<A.size();++i ) // 1 // 2 // 5
    {
        int maxLengthAux = 0;
        if (A[i] <= n) //
            continue;

        maxLengthAux++; // 1 // 1 // 1
        std::vector<int> auxA(A.begin()+i+1, A.end()); // 2 1 5 // 1 5 //
        maxLengthAux+=checkSubList(auxA, A.at(i)); 

        maxLength = std::max( maxLength, maxLengthAux);
    }
    return maxLength;
}

int lis(const std::vector<int> &A) {

    return checkSubList(A, -1);
}

void fb1()
{
  std::vector<int> A = { 86, 64, 34, 56, 73, 52, 75, 51, 2, 78, 14, 10, 74, 36, 32, 31, 32, 87, 36, 4, 66, 89, 47, 12, 53, 9, 73, 34, 92, 34, 87, 1, 28, 24, 46, 92, 27, 1, 13, 75, 46, 4, 74, 93, 76, 56, 31, 42, 65, 58, 84, 61, 18, 59, 89, 29, 96, 101, 42, 95, 28, 65, 48, 51, 51, 18, 90, 43, 75, 22, 87, 100, 80, 14, 13, 78, 55, 78, 18, 25, 53, 88, 8, 9, 16, 86, 18 };
  std::cout << lis( A ) << std::endl;

}


int main( int argc, char* argv[] )
{
  paintAdventCalendar();
  auto day = getDay();
  switch (day)
  {
    case 0:
      fb1();
      break;
    case 1:
      day1Part1();
      day1Part2();
      break;
    //case 2:
    //  day2Part1();
    //  day2Part2();
    //  break;
    //case 3:
    //  day3Part1();
    //  day3Part2();
    //  break;
    //case 4:
    //  day4Part1();
    //  day4Part2();
    //  break;
    //case 5:
    //  day5Part1();
    //  day5Part2();
    //  break;
    //case 6:
    //  day6Part1();
    //  day6Part2();
    //  break;
    //case 7:
    //  day7Part1();
    //  day7Part2();
    //  break;
    //case 8:
    //  day8Part1();
    //  day8Part2();
    //  break;
    //case 9:
    //  day9Part1();
    //  day9Part2();
    //  break;
    //case 10:
    //  day10Part1();
    //  day10Part2();
    //  break;
    //case 11:
    //  day11Part1();
    //  day11Part2();
    //  break;
    //case 12:
    //  day12Part1();
    //  day12Part2();
    //  break;
    //case 13:
    //  day13Part1();
    //  day13Part2();
    //  break;
    //case 14:
    //  day14Part1();
    //  day14Part2();
    //  break;
    //case 15:
    //  day15Part1();
    //  day15Part2();
    //  break;
    //case 16:
    //  day16Part1();
    //  day16Part2();
    //  break;
    //case 17:
    //  day17Part1();
    //  day17Part2();
    //  break;
    //case 18:
    //  day18Part1();
    //  day18Part2();
    //  break;
    //case 19:
    //  day19Part1();
    //  day19Part2();
    //  break;
    //case 20:
    //  day20Part1();
    //  day20Part2();
    //  break;
    //case 21:
    //  day21Part1();
    //  day21Part2();
    //  break;
    //case 22:
    //  day22Part1();
    //  day22Part2();
    //  break;
    //case 23:
    //  day23Part1();
    //  day23Part2();
    //  break;
    //case 24:
    //  day24Part1();
    //  day24Part2();
    //  break;
    //case 25:
    //  day25Part1();
    //  day25Part2();
    //  break;
    default:
      break;
  }
}