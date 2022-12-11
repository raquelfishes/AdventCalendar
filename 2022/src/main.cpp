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
  printf( HGRN"Advent of Code\n" GRN"\ty(" HGRN"2022" GRN")" reset "\n" );

  
  printf( HBLK "@@@@#@@#@#@@@@@@@@@@@@@@#@#@@#@@@@@#@@@##@@@@@@#@" reset "    " "25" reset "\n" );
  printf( HBLK "#@@@@@@@##@@#@@@@@@@#@@#@@##@##@@@@#@##@@@#@@#@@@" reset "    " "24" reset "\n" );
  printf( HBLK "@@@@@@@@##@#@@@@@@@@@@@@##@@@#@@#@@@###@##@@@##@#" reset "    " "23" reset "\n" );
  printf( HBLK "#@@@@@@@@@@#@@@#@@@#@@#@@@@#@@@@#@##@##@@@#@@#@@@" reset "    " "22" reset "\n" );
  printf( HBLK "@@@@@@#@#@#@@@@@@@#@@@##@##@#@@##@@@@@@#@@#@@@@#@" reset "    " "21" reset "\n" );
  printf( HBLK "@@@@@@##@@#@#@@##@@#@@@@@@##@@#@@@@@#@#@|@#@@@@#@" reset "    " "20" reset "\n" );
  printf( HBLK "@@@@#@@#@@@@@@@#@#@@#@@@@@#@@@#@#@#@@@@@@@@@@@@@@" reset "    " "19" reset "\n" );
  printf( HBLK "####@#@@@@@#@@@###@#@#@|@@@@@@@@@@@@#@@@##@#@@###" reset "    " "18" reset "\n" );
  printf( HBLK "##@@@@@##@@@@#@##@@@@@@@@@@#@@@@@@#@#@@@@@@@#@@#@" reset "    " "17" reset "\n" );
  printf( HBLK "#@@#@##@###@@@@@##@#@#@@@#@@#@@@#@@@@#@@@###@@#@@" reset "    " "16" reset "\n" );
  printf( HBLK "#@#@#@@@@@@@@#@#@@@##@@#@@@#@##@#@@@#@##@@@@##@@@" reset "    " "15" reset "\n" );
  printf( HBLK "#@#@@@#@@@@@##@@@@##@@@@@@@@@@@@@@@#@@###@@@@@@@@" reset "    " "14" reset "\n" );
  printf( HBLK "@@@@@@@@@@#@#@@#@@@#@@@@#@#@#@#@#@#@@@##@@@@@@@@@" reset "    " "13" reset "\n" );
  printf( HBLK "@@@@#@@@@@@@@###@@#@@#@#@@@#@@####@@@@@@@@@#@@##@" reset "    " "12" reset "\n" );
  printf( HBLK "@@#@@@@@#@" GRN "@" HGRN "@" CYN ".~~."  HGRN "#" GRN "@" HBLK "@@@@@@@##@@@#@@##@@##@@@@@@@@##" reset "    " "11" BHYEL " " "**" reset "\n" );
  printf( HBLK "#@@@@@@@@" GRN "@@" CYN ".~~." HGRN "@" GRN "@@@@" HBLK "#@@@#@@@@#@@#@##@@###@@@@@##@" reset "    " "10" BHYEL " " "**" reset "\n" );
  printf( GRN "@" HGRN "#" GRN "@#" YEL "." GRN "@#" WHT " _" YEL "|%%%%%%=%%%%|" WHT "_ " GRN "@@@@" HGRN "@" GRN "@" HBLK "@@##@@@@@@@#@#@@@@@#@@@#" reset "    " "9" BHYEL "  " "**" reset "\n" );
  printf( HBLK "@#@" HGRN "@@" YEL ".." WHT "/  \\" CYN ".~~." WHT "/  \\" YEL "....." GRN "@" HGRN "@" HBLK "@#@@@@#@@@@@@@@@#@@#@@#" reset "    " "8" BHYEL "  " "**" reset "\n" );
  printf( HBLK "@@@@#@@@@" GRN "@" HGRN "@" CYN ".~~." GRN "#@" HGRN "#@" GRN "@#@#@" YEL "." HGRN "@" GRN "@" HBLK "@#@@@@@@#@#@@##@@#@#@@" reset "    " "7" BHYEL "  " "**" reset "\n" );
  printf( HBLK "@@##@#@#@@" GRN "@@" CYN ".~~." GRN "@@@@@" HGRN "@"  GRN "@" YEL ".." GRN "@@" HBLK "@@@@##@#@#@@@@#@@#@@#@" reset "    " "6" BHYEL "  " "**" reset "\n" );
  printf( HBLK "@@@@#@@@" RED "|" GRN "@" HGRN "@" GRN "@" HGRN "@" CYN ".~~." GRN "##" YEL "."  WHT "/\\" YEL ".'" GRN "@#@#@" HBLK "@#@@@#@@@@@@@@@@@@#@" reset "    " "5" BHYEL "  " "**" reset "\n" );
  printf( HBLK "@#@#@" HGRN "@" GRN "#" GRN "@@" HGRN "@" GRN "@" YEL ".'" CYN " ~  " YEL "'." WHT "/\\" YEL "'." WHT "/\\" YEL "' ." GRN "@" HGRN "@" GRN "@" HBLK "@@@@@#@@@#@@@@##@#" reset "    " "4" BHYEL "  " "**" reset "\n" );
  printf( HBLK "#" GRN "@" HGRN "#" GRN "#" HGRN "#" GRN "@" HGRN "@" GRN "@@" YEL "_/" CYN " ~   ~  " YEL "\\ ' '. '.'." GRN "@#" HBLK "#@@@@#@@@@##@#@##" reset "    " "3" BHYEL "  " "**" reset "\n" );
  printf( YEL  "-~------'" CYN "    ~    ~ " YEL "'--~-----~-~----___________--" reset "    " "2" BHYEL "  " "**" reset "\n" );
  printf( CYN  "  ~    ~  ~      ~     ~ ~   ~     ~  ~  ~   ~     " reset "  " "1" BHYEL "  " "**" reset "\n" );
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
    case 0:
      testColors();
      break;
    case 1:
      day1Part1();
      day1Part2();
      break;
    case 2:
      day2Part1();
      day2Part2();
      break;
    case 3:
      day3Part1();
      day3Part2();
      break;
    case 4:
      day4Part1();
      day4Part2();
      break;
    case 5:
      day5Part1();
      day5Part2();
      break;
    case 6:
      day6Part1();
      day6Part2();
      break;
    case 7:
      day7Part1();
      day7Part2();
      break;
    case 8:
      day8Part1();
      day8Part2();
      break;
    case 9:
      day9Part1();
      day9Part2();
      break;
    case 10:
      day10Part1();
      day10Part2();
      break;
    case 11:
      day11Part1();
      day11Part2();
      break;
    case 12:
      day12Part1();
      day12Part2();
      break;
    case 13:
      day13Part1();
      day13Part2();
      break;
    case 14:
      day14Part1();
      day14Part2();
      break;
    case 15:
      day15Part1();
      day15Part2();
      break;
    case 16:
      day16Part1();
      day16Part2();
      break;
    case 17:
      day17Part1();
      day17Part2();
      break;
    case 18:
      day18Part1();
      day18Part2();
      break;
    case 19:
      day19Part1();
      day19Part2();
      break;
    case 20:
      day20Part1();
      day20Part2();
      break;
    case 21:
      day21Part1();
      day21Part2();
      break;
    case 22:
      day22Part1();
      day22Part2();
      break;
    case 23:
      day23Part1();
      day23Part2();
      break;
    case 24:
      day24Part1();
      day24Part2();
      break;
    case 25:
      day25Part1();
      day25Part2();
      break;
    default:
      break;
  }
}