#include "sonar_sweep.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <string>
#include <numeric>

#include "resource.h"
#include "utils.h"


void theTreacheryOfWhalesPart1()
{
  std::vector<std::string> numsStr;
  readDocument<std::string>(DAY7_PATH, numsStr);

  splitString(numsStr.front(), ',', numsStr);

  std::vector<int> positions;
  std::for_each(numsStr.begin(), numsStr.end(), [&positions](std::string s)
    {
      positions.push_back(std::stoi(s));
    });
  
  // sort by value
  std::sort(positions.begin(), positions.end());

  int minDiff = std::numeric_limits<int>::max();
  int minDiffValue = 0;
  for (int i = 0; i < positions.back(); ++i)
  {
    int currentValue = 0;
    for (auto& pos : positions)
    {
      currentValue += std::abs(pos - i);
      if (currentValue > minDiff)
      {
        break;
      }
    }
    minDiff = std::min(minDiff, currentValue);
    minDiffValue = i;
  }

  int result = minDiff;
  printf("The solution for part 1 is: %i \n", result);

}

void theTreacheryOfWhalesPart2()
{
  std::vector<std::string> numsStr;
  readDocument<std::string>(DAY7_PATH, numsStr);

  splitString(numsStr.front(), ',', numsStr);

  std::vector<int> positions;
  std::for_each(numsStr.begin(), numsStr.end(), [&positions](std::string s)
    {
      positions.push_back(std::stoi(s));
    });

  // sort by value
  std::sort(positions.begin(), positions.end());

  int minDiff = std::numeric_limits<int>::max();
  int minDiffValue = 0;
  for (int i = 0; i < positions.back(); ++i)
  {
    int currentValue = 0;
    for (auto& pos : positions)
    {
      // Compute summatory = n * (a1 + an) / 2
      int diff = std::abs(pos - i);
      currentValue += (diff * (1+diff)) * 0.5;
      if (currentValue > minDiff)
      {
        break;
      }
    }
    minDiff = std::min(minDiff, currentValue);
    minDiffValue = i;
  }

  int result = minDiff;
  printf("The solution for part 2 is: %lld \n", result);
}
