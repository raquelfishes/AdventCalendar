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

int main( int argc, char* argv[] )
{
  paintAdventCalendar();
  auto day = getDay();
  switch (day)
  {
    case 1:
      sonarSweepPart1();
      sonarSweepPart2();
      break;
    case 2:
      divePart1();
      divePart2();
      break;
    case 3:
      binaryDiagnosticPart1();
      binaryDiagnosticPart2();
      break;
    case 4:
      giantSquidPart1();
      giantSquidPart2();
      break;
    case 5:
      hydrothermalVenturePart1();
      hydrothermalVenturePart2();
      break;
    case 6:
      lanternfishPart1();
      lanternfishPart2();
      break;
    case 7:
      theTreacheryOfWhalesPart1();
      theTreacheryOfWhalesPart2();
      break;
    case 8:
      sevenSegmentSearchPart1();
      sevenSegmentSearchPart2();
      break;
    case 9:
      smokeBasinPart1();
      smokeBasinPart2();
      break;
    case 10:
      syntaxScoringPart1();
      syntaxScoringPart2();
      break;
    case 11:
      dumboOctopusPart1();
      dumboOctopusPart2();
      break;
    case 12:
      passagePathingPart1();
      passagePathingPart2();
      break;
    case 13:
      //transparentOrigamiPart1();
      transparentOrigamiPart2();
      break;
    default:
      break;
  }
}