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

  printf( RED "  - " WHT "/\\" RED " -  -        -       -     -      -    -   " reset "\n");
  printf( HRED " - " HBLK "/  \\/\\" HRED "  -    -     -  -    -   - " HBLK " /\\" HRED"  -     -" reset "\n" );
  printf( HBLK " /\\    \\ \\" YEL"-  - -   -   -    - -  -" HBLK"/\\/  \\" YEL"-   -  - " reset "    " "25" BHYEL " " "**" reset "\n" );
  printf( HBLK  "/" GRN"@@" HBLK "\\   /\\" GRN"#" HBLK "\\" GRN"@@@@@##@@@#@@@@###@@@@@#@@@###@@@##@@@" reset "    " "24" BHYEL " " "**" reset "\n" );
  printf( GRN  "#@@.' '.@@#" HGRN"@#@@@@@" BGRN"@@@@@@#@@" GRN"#@@#|@@@#" HGRN"@@#@@@" BGRN"@#@@@@#" reset "    " "23" BHYEL " " "**" reset "\n" );
  printf( GRN  "#@@'. .'#@@@" YEL"." GRN"##@#@@@@@@##@@@##@@#@@##@@@#" WHT"()))" GRN"@@@@" reset "    " "22" BHYEL " " "**" reset "\n" );
  printf( GRN  "@#@@#@@@@#@@@##@@@" YEL"." GRN"#@#@#@@##@@@@@@@@#@##@@@#@@@#@" reset "    " "21" BHYEL " " "**" reset "\n" );
  printf( GRN  "@@###" YEL"." GRN"@@#@#@@##@#@###@@#" YEL"." GRN"@@@" CYN"~~" BGRN"#@@#@@@@@@@@#@##@@@" reset "    " "20" BHYEL " " "**" reset "\n" );
  printf( GRN  "@@@@#|#@@@@#@" CYN"." GRN"@@@@@##@@@@@@" CYN"~~~~" WHT" .~'" BGRN"@@@@@@@@#@@#@#" reset "    " "19" BHYEL " " "**" reset "\n" );
  printf( GRN  "@@@@#@#@@#@@@#" CYN"." GRN"#@##@@@@@" HGRN "@" GRN "@@@" CYN "~~" HBLK " /" HRED "~" HBLK "\\ " HGRN "#" HGRN "@#" GRN "@" HGRN "##@@###@@@" reset "    " "18" BHYEL " " "**" reset "\n" );
  printf( GRN  "#@@@" YEL"." GRN"@#@##@@#@@" CYN".." GRN"#@#@#@@@@@#@" HBLK" / " HRED"/ " HBLK "\\ " GRN"##@@@@@#@@@##" reset "    " "17" BHYEL " " "**" reset "\n" );
  printf( GRN  "@##@##@@@@#@@@@#" CYN".." GRN"#@@##@@##@@" HBLK"/ " HRED"/ \\ " HBLK "\\" GRN"@#@@@@@@#|##@" reset "    " "16" BHYEL " " "**" reset "\n" );
  printf( GRN  "#@@##@@#@@#@@" GRN "@@_" CYN ".~." GRN "_@@@" HGRN "##@" HGRN "@" GRN "@" WHT".'" HRED"/\\" WHT".'" HRED"~" WHT". " GRN"@#@@#@##@@@@" reset "    " "15" BHYEL " " "**" reset "\n" );
  printf( GRN  "#@@#" YEL"." GRN"@@@##@##" HGRN "@" GRN "@" WHT " ||| " GRN "@#@@#@#" WHT"'." HRED"~" WHT".'" HRED"~" WHT". " HRED"\\" WHT"'." GRN"@@@@@@@@#@#" reset "    " "14" BHYEL " " "**" reset "\n" );
  printf( GRN  "@@@@#@@@@@@@##"  HGRN "#@" WHT "~~~" GRN "@#@@@@@#@" WHT"' ..'.'." HRED"\\" WHT". . " GRN"@@@@#@##" reset "    " "13" BHYEL " " "**" reset "\n" );
  printf( GRN  "@@#@@@@@@@@#" GRN "@#" CYN ".~~." HGRN "#@@#@@@@@@@###@ " WHT".'." HRED"~~~" WHT"' " GRN"@" WHT"'" GRN"#@@#@" reset "    " "12" BHYEL " " "**" reset "\n" );
  printf( GRN  "@@#@@@@@#@" GRN "@" HGRN "@" CYN ".~~."  HGRN "#@@##@@@@#@@@@@@#@  " HRED"~~~~~" WHT".." GRN"@@#@@#" reset "    " "11" BHYEL " " "**" reset "\n" );
  printf( GRN  "#@@@" YEL"." GRN"@@@@" GRN "@@" CYN ".~~." HGRN "#@#@#@##@#@@#@@@@#" WHT".'" HRED"/ ~~~ \\" WHT"' " GRN"#@@@#" reset "    " "10" BHYEL " " "**" reset "\n" );
  printf( GRN  "@" HGRN "#" GRN "@#" YEL "." GRN "@#" WHT " _" YEL "|%%%%%%=%%%%|" WHT "_ " GRN "@@@##@@@##@@#" WHT". " HRED"~ /" WHT"' .'" HRED"/\\" WHT"." GRN"@@@@" BRED"|" reset "    " "9" BHYEL "  " "**" reset "\n" );
  printf( GRN "@#@" HGRN "@@" YEL ".." WHT "/  \\" CYN ".~~." WHT "/  \\" YEL "....." GRN "@@##@#@@#" WHT"' " HRED"/\\" WHT".''" HRED"/" WHT"' " HRED"\\" WHT"' " GRN"@@@" reset "    " "8" BHYEL "  " "**" reset "\n" );
  printf( GRN  "@@@@#@@@@" GRN "@" HGRN "@" CYN ".~~." GRN "#@" HGRN "#@" GRN "@#@#@" YEL "." HGRN "@" GRN "@#@@@#" WHT"'." HRED"/" WHT"." HRED"/\\ " WHT"." HRED"\\" WHT"'." HRED"/\\ " WHT"'. " reset "    " "7" BHYEL "  " "**" reset "\n" );
  printf( GRN  "@@##@#@#@@" GRN "@@" CYN ".~~." GRN "@@@@@" HGRN "@"  GRN "@" YEL ".." GRN "@@@#@@" WHT"' " HRED"~" WHT". " HRED"\\" WHT"." HRED"\\  \\ \\" WHT"." HRED"~~~" WHT"." reset "    " "6" BHYEL "  " "**" reset "\n" );
  printf( GRN  "@@@@#@@@" RED "|" GRN "@" HGRN "@" GRN "@" HGRN "@" CYN ".~~." GRN "##" YEL "."  WHT "/\\" YEL ".'" GRN "@#@#@@#@" WHT"'.' .'" HRED"/" WHT"." GRN"@" WHT". " HRED"/" WHT".'" HRED"~~~" reset "    " "5" BHYEL "  " "**" reset "\n" );
  printf( GRN  "@#@#@" HGRN "@" GRN "#" GRN "@@" HGRN "@" GRN "@" YEL ".'" CYN " ~  " YEL "'." WHT "/\\" YEL "'." WHT "/\\" YEL "' ." GRN "@" HGRN "@" GRN "@" HGRN "@##@" WHT "'" HRED " /\\" WHT" . " HRED "/" WHT"'. ..'" reset "    " "4" BHYEL "  " "**" reset "\n" );
  printf( HGRN "#" GRN "@" HGRN "#" GRN "#" HGRN "#" GRN "@" HGRN "@" GRN "@@" YEL "_/" CYN " ~   ~  " YEL "\\ ' '. '.'." GRN "@#" HGRN "#@" HRED "  /  \\  \\  " HGRN "#@#@" reset "    " "3" BHYEL "  " "**" reset "\n" );
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