#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <stdlib.h>
#include <stdio.h>

#include <unordered_map>
#include <functional>

// #include "adventdays_fwd.h"
#include "ansi_colors.h"
#include "design_base.h"

#include "../events/2021/design.h"
#include "../events/2022/design.h"
#include "../events/2023/design.h" // Ruta relativa correcta
#include "../events/2024/design.h"

#define FIRST_AOC 2015
#define LAST_AOC 2024

#define FIRST_ADVENT_DAY 1
#define LAST_ADVENT_DAY 25

int getEvent()
{
    bool isValidYear = false;
    int year;
    while (!isValidYear)
    {
        std::cout << "Introduce el a�o del Advent Of Code que quieres ejecutar:";
        std::cin >> year;
        std::cout << std::endl;
        if (year >= FIRST_AOC && year <= LAST_AOC)
        {
            isValidYear = true;
        }
        else
        {
            std::cout << "El a�o introducido no es valido, introduce un a�o entre 2015 y 2024" << std::endl;
        }
    }
    return year;
}

int getDay()
{
    bool isValidDay = false;
    int day;
    while (!isValidDay)
    {
        std::cout << "Introduce el a�o del Advent Of Code que quieres ejecutar:";
        std::cin >> day;
        std::cout << std::endl;
        if (day >= FIRST_ADVENT_DAY && day <= LAST_ADVENT_DAY)
        {
            isValidDay = true;
        }
        else
        {
            std::cout << "El día introducido no es valido, introduce un día entre 1 y 25" << std::endl;
        }
    }
    return day;
}

int main(int argc, char *argv[])
{
    int year = getEvent();

    // Crear el mapa de funciones autom�ticamente
    auto designs = createDesignMap<2023, 2024>();

    // Seleccionar el dise�o seg�n el a�o
    if (designs.find(year) != designs.end())
    {
        designs[year](); // Llama a la funci�n correspondiente
    }
    else
    {
        std::cout << "Año sin diseño.\n";
    }

    int day = getDay();
}

// void paintAdventCalendar()
//{
//   printf( HGRN"Advent of Code\n" GRN"\ty(" HGRN"2022" GRN")" reset "\n" );
//
//   printf( RED "  - " WHT "/\\" RED " -  -        -       -     -      -    -   " reset "\n");
//   printf( HRED " - " HBLK "/  \\/\\" HRED "  -    -     -  -    -   - " HBLK " /\\" HRED"  -     -" reset "\n" );
//   printf( HBLK " /\\    \\ \\" YEL"-  - -   -   -    - -  -" HBLK"/\\/  \\" YEL"-   -  - " reset "    " "25" BHYEL " " "**" reset "\n" );
//   printf( HBLK  "/" GRN"@@" HBLK "\\   /\\" GRN"#" HBLK "\\" GRN"@@@@@##@@@#@@@@###@@@@@#@@@###@@@##@@@" reset "    " "24" BHYEL " " "**" reset "\n" );
//   printf( GRN  "#@@.' '.@@#" HGRN"@#@@@@@" BGRN"@@@@@@#@@" GRN"#@@#|@@@#" HGRN"@@#@@@" BGRN"@#@@@@#" reset "    " "23" BHYEL " " "**" reset "\n" );
//   printf( GRN  "#@@'. .'#@@@" YEL"." GRN"##@#@@@@@@##@@@##@@#@@##@@@#" WHT"()))" GRN"@@@@" reset "    " "22" BHYEL " " "**" reset "\n" );
//   printf( GRN  "@#@@#@@@@#@@@##@@@" YEL"." GRN"#@#@#@@##@@@@@@@@#@##@@@#@@@#@" reset "    " "21" BHYEL " " "**" reset "\n" );
//   printf( GRN  "@@###" YEL"." GRN"@@#@#@@##@#@###@@#" YEL"." GRN"@@@" CYN"~~" BGRN"#@@#@@@@@@@@#@##@@@" reset "    " "20" BHYEL " " "**" reset "\n" );
//   printf( GRN  "@@@@#|#@@@@#@" CYN"." GRN"@@@@@##@@@@@@" CYN"~~~~" WHT" .~'" BGRN"@@@@@@@@#@@#@#" reset "    " "19" BHYEL " " "**" reset "\n" );
//   printf( GRN  "@@@@#@#@@#@@@#" CYN"." GRN"#@##@@@@@" HGRN "@" GRN "@@@" CYN "~~" HBLK " /" HRED "~" HBLK "\\ " HGRN "#" HGRN "@#" GRN "@" HGRN "##@@###@@@" reset "    " "18" BHYEL " " "**" reset "\n" );
//   printf( GRN  "#@@@" YEL"." GRN"@#@##@@#@@" CYN".." GRN"#@#@#@@@@@#@" HBLK" / " HRED"/ " HBLK "\\ " GRN"##@@@@@#@@@##" reset "    " "17" BHYEL " " "**" reset "\n" );
//   printf( GRN  "@##@##@@@@#@@@@#" CYN".." GRN"#@@##@@##@@" HBLK"/ " HRED"/ \\ " HBLK "\\" GRN"@#@@@@@@#|##@" reset "    " "16" BHYEL " " "**" reset "\n" );
//   printf( GRN  "#@@##@@#@@#@@" GRN "@@_" CYN ".~." GRN "_@@@" HGRN "##@" HGRN "@" GRN "@" WHT".'" HRED"/\\" WHT".'" HRED"~" WHT". " GRN"@#@@#@##@@@@" reset "    " "15" BHYEL " " "**" reset "\n" );
//   printf( GRN  "#@@#" YEL"." GRN"@@@##@##" HGRN "@" GRN "@" WHT " ||| " GRN "@#@@#@#" WHT"'." HRED"~" WHT".'" HRED"~" WHT". " HRED"\\" WHT"'." GRN"@@@@@@@@#@#" reset "    " "14" BHYEL " " "**" reset "\n" );
//   printf( GRN  "@@@@#@@@@@@@##"  HGRN "#@" WHT "~~~" GRN "@#@@@@@#@" WHT"' ..'.'." HRED"\\" WHT". . " GRN"@@@@#@##" reset "    " "13" BHYEL " " "**" reset "\n" );
//   printf( GRN  "@@#@@@@@@@@#" GRN "@#" CYN ".~~." HGRN "#@@#@@@@@@@###@ " WHT".'." HRED"~~~" WHT"' " GRN"@" WHT"'" GRN"#@@#@" reset "    " "12" BHYEL " " "**" reset "\n" );
//   printf( GRN  "@@#@@@@@#@" GRN "@" HGRN "@" CYN ".~~."  HGRN "#@@##@@@@#@@@@@@#@  " HRED"~~~~~" WHT".." GRN"@@#@@#" reset "    " "11" BHYEL " " "**" reset "\n" );
//   printf( GRN  "#@@@" YEL"." GRN"@@@@" GRN "@@" CYN ".~~." HGRN "#@#@#@##@#@@#@@@@#" WHT".'" HRED"/ ~~~ \\" WHT"' " GRN"#@@@#" reset "    " "10" BHYEL " " "**" reset "\n" );
//   printf( GRN  "@" HGRN "#" GRN "@#" YEL "." GRN "@#" WHT " _" YEL "|%%%%%%=%%%%|" WHT "_ " GRN "@@@##@@@##@@#" WHT". " HRED"~ /" WHT"' .'" HRED"/\\" WHT"." GRN"@@@@" BRED"|" reset "    " "9" BHYEL "  " "**" reset "\n" );
//   printf( GRN "@#@" HGRN "@@" YEL ".." WHT "/  \\" CYN ".~~." WHT "/  \\" YEL "....." GRN "@@##@#@@#" WHT"' " HRED"/\\" WHT".''" HRED"/" WHT"' " HRED"\\" WHT"' " GRN"@@@" reset "    " "8" BHYEL "  " "**" reset "\n" );
//   printf( GRN  "@@@@#@@@@" GRN "@" HGRN "@" CYN ".~~." GRN "#@" HGRN "#@" GRN "@#@#@" YEL "." HGRN "@" GRN "@#@@@#" WHT"'." HRED"/" WHT"." HRED"/\\ " WHT"." HRED"\\" WHT"'." HRED"/\\ " WHT"'. " reset "    " "7" BHYEL "  " "**" reset "\n" );
//   printf( GRN  "@@##@#@#@@" GRN "@@" CYN ".~~." GRN "@@@@@" HGRN "@"  GRN "@" YEL ".." GRN "@@@#@@" WHT"' " HRED"~" WHT". " HRED"\\" WHT"." HRED"\\  \\ \\" WHT"." HRED"~~~" WHT"." reset "    " "6" BHYEL "  " "**" reset "\n" );
//   printf( GRN  "@@@@#@@@" RED "|" GRN "@" HGRN "@" GRN "@" HGRN "@" CYN ".~~." GRN "##" YEL "."  WHT "/\\" YEL ".'" GRN "@#@#@@#@" WHT"'.' .'" HRED"/" WHT"." GRN"@" WHT". " HRED"/" WHT".'" HRED"~~~" reset "    " "5" BHYEL "  " "**" reset "\n" );
//   printf( GRN  "@#@#@" HGRN "@" GRN "#" GRN "@@" HGRN "@" GRN "@" YEL ".'" CYN " ~  " YEL "'." WHT "/\\" YEL "'." WHT "/\\" YEL "' ." GRN "@" HGRN "@" GRN "@" HGRN "@##@" WHT "'" HRED " /\\" WHT" . " HRED "/" WHT"'. ..'" reset "    " "4" BHYEL "  " "**" reset "\n" );
//   printf( HGRN "#" GRN "@" HGRN "#" GRN "#" HGRN "#" GRN "@" HGRN "@" GRN "@@" YEL "_/" CYN " ~   ~  " YEL "\\ ' '. '.'." GRN "@#" HGRN "#@" HRED "  /  \\  \\  " HGRN "#@#@" reset "    " "3" BHYEL "  " "**" reset "\n" );
//   printf( YEL  "-~------'" CYN "    ~    ~ " YEL "'--~-----~-~----___________--" reset "    " "2" BHYEL "  " "**" reset "\n" );
//   printf( CYN  "  ~    ~  ~      ~     ~ ~   ~     ~  ~  ~   ~     " reset "  " "1" BHYEL "  " "**" reset "\n" );
// }
