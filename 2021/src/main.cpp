#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <stdlib.h>

#include "adventdays_fwd.h"

#define ANSI_RED "\x1b[31m" 
#define ANSI_GREEN "\x1b[32m" 
#define ANSI_YELLOW "\x1b[33m" 
#define ANSI_BLUE "\x1b[34m" 
#define ANSI_MAGENTA "\x1b[35m" 
#define ANSI_CYAN "\x1b[36m" 
#define ANSI_RESET "\x1b[0m" 




void paintAdventCalendar()
{
  printf(ANSI_RED "red text" ANSI_GREEN " green text" ANSI_BLUE " blue text" ANSI_RESET "default text\n");
  std::cout << "                      ~   ~  ~ ~~ ~~~~~~~~~~~~~~~  " << "     " << "1" << std::endl;
  std::cout << "                                      '. ' ..''''  " << "     " << "2" << std::endl;
  std::cout << "                                                   " << "     " << "3" << std::endl;
  std::cout << "                                                   " << "     " << "4" << std::endl;
  std::cout << "                                                   " << "     " << "5" << std::endl;
  std::cout << "                                                   " << "     " << "6" << std::endl;
  std::cout << "                                                   " << "     " << "7" << std::endl;
  std::cout << "                                                   " << "     " << "8" << std::endl;
  std::cout << "                                                   " << "     " << "9" << std::endl;
  std::cout << "                                                   " << "     " << "10" << std::endl;
  std::cout << "                                                   " << "     " << "11" << std::endl;
  std::cout << "                                                   " << "     " << "12" << std::endl;
  std::cout << "                                                   " << "     " << "13" << std::endl;
  std::cout << "                                                   " << "     " << "14" << std::endl;
  std::cout << "                                                   " << "     " << "15" << std::endl;
  std::cout << "                                                   " << "     " << "16" << std::endl;
  std::cout << "                                                   " << "     " << "17" << std::endl;
  std::cout << "                                                   " << "     " << "18" << std::endl;
  std::cout << "                                                   " << "     " << "19" << std::endl;
  std::cout << "                                                   " << "     " << "20" << std::endl;
  std::cout << "                                                   " << "     " << "21" << std::endl;
  std::cout << "                                                   " << "     " << "22" << std::endl;
  std::cout << "                                                   " << "     " << "23" << std::endl;
  std::cout << "                                                   " << "     " << "24" << std::endl;
  std::cout << "                                                   " << "     " << "25" << std::endl;
}

int getDay()
{
  std::cout << "Introduce el día que quieres ejecutar:";
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
      break;
    default:
      break;
  }
}