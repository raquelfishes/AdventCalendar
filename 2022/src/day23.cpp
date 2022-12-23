#include "std_includes.h"
#include "resource.h"
#include "utils.h"
#include "vector2.h"

namespace
{

using Coord = std::pair<int, int>;

Coord operator+(const Coord& c1, const Coord& c2)
{
  auto [x1, y1] = c1;
  auto [x2, y2] = c2;

  return {x1 + x2, y1 + y2};
}

Coord NW{-1, -1};
Coord N{0, -1};
Coord NE{1, -1};
Coord E{1,  0};
Coord W{-1,  0};
Coord SW{-1,  1};
Coord S{0,  1};
Coord SE{1,  1};

std::vector<Coord> North = {NW, N, NE};
std::vector<Coord> South = {SE, S, SW};
std::vector<Coord> East = {NE, E, SE};
std::vector<Coord> West = {SW, W, NW};

const std::vector<std::vector<Coord>> DIR = {North, South, West, East};
auto All = {NE, N, NW, W, SW, S, SE, E};

bool moveRound(std::map<uint64_t, Coord>& elfs, std::set<Coord>& occupied, const uint64_t roundNum)
{
  std::map<Coord, uint64_t> coordCnt;
  std::map<uint64_t, Coord> proposedPos;
  std::set<Coord> newOccupied;

  for(auto& elf : elfs)
  {
    if(std::none_of(All.begin(), All.end(), [&elf, &occupied](auto& c) { return occupied.contains(elf.second + c); }))
    {

      newOccupied.insert(elf.second);
      continue;
    }

    bool hasProposed = false;
    for(int idx = 0; idx < 4; ++idx)
    {
      auto dirs = DIR[( roundNum + idx ) % 4];
      if(std::none_of(dirs.begin(), dirs.end(), [&elf, &occupied](auto& c) { return occupied.contains(elf.second + c); }))
      {

        proposedPos[elf.first] = elf.second + dirs[1];
        coordCnt[elf.second + dirs[1]]++;
        hasProposed = true;
        break;
      }
    }
    if(!hasProposed) newOccupied.insert(elf.second);
  }

  for(auto& proposed : proposedPos)
  {
    if(coordCnt[proposed.second] == 1)
    {
      elfs[proposed.first] = proposed.second;
      newOccupied.insert(proposed.second);
    }
    else
    {
      newOccupied.insert(elfs[proposed.first]);
    }
  }

  occupied = newOccupied;

  return !proposedPos.empty();
}

void auxSize(const std::set<Coord>& occupied)
{
  int minX = std::numeric_limits<int>::max();
  int maxX = std::numeric_limits<int>::min();
  int minY = std::numeric_limits<int>::max();
  int maxY = std::numeric_limits<int>::min();

  for(auto pos : occupied)
  {
    minX = std::min(minX, pos.first);
    maxX = std::max(maxX, pos.first);
    minY = std::min(minY, pos.second);
    maxY = std::max(maxY, pos.second);
  }
  uint64_t score = ( maxX - minX + 1 ) * ( maxY - minY + 1 ) - occupied.size();

  std::cout << score << std::endl;
}

uint64_t adventDay23problem12022(std::ifstream& input)
{
  uint64_t score = 0;

  std::map<uint64_t, Coord> elfs;
  std::set<Coord> occupied;

  uint64_t idx = 0;
  uint64_t x = 0;
  uint64_t y = 0;

  std::vector<std::string> in;
  readDocument(DAY23_PATH, in);
  for(auto& s : in)
  {
    x = 0;
    for(char c : s)
    {
      if(c == '#')
      {
        elfs[idx] = {x, y};
        occupied.insert(elfs[idx]);
        idx++;
      }
      x++;
    }
    y++;
  }

  for(int i = 0; i < 10; ++i)
  {
    moveRound(elfs, occupied, i);
    std::cout << "Iteration: " << i << " score: ";
    auxSize(occupied);
  }
    


  int minX = std::numeric_limits<int>::max();
  int maxX = std::numeric_limits<int>::min();
  int minY = std::numeric_limits<int>::max();
  int maxY = std::numeric_limits<int>::min();

  for(auto pos : occupied)
  {
    minX = std::min(minX, pos.first);
    maxX = std::max(maxX, pos.first);
    minY = std::min(minY, pos.second);
    maxY = std::max(maxY, pos.second);
  }

  score = ( maxX - minX + 1 ) * ( maxY - minY + 1 ) - occupied.size();

  std::cout << score << std::endl;

  return score;
}
}

struct Elf
{
  Elf(const int& x, const int& y)
  {
    pos = Vector2I(x, y);
  }
  Vector2I pos;
  Vector2I posToMove;
  int moveIndex = 0;
};

void printElves(const std::vector<Elf>& elves)
{
  int maxX = std::numeric_limits<int>::min();
  int maxY = std::numeric_limits<int>::min();
  int minX = std::numeric_limits<int>::max();
  int minY = std::numeric_limits<int>::max();

  for(auto& elf : elves)
  {
    maxX = std::max(maxX, elf.pos.x);
    maxY = std::max(maxY, elf.pos.y);
    minX = std::min(minX, elf.pos.x);
    minY = std::min(minY, elf.pos.y);
  }

  std::vector<std::string> printS(maxY - minY + 1, std::string(maxX - minX + 1, '.'));
  for(auto& elf : elves)
  {
    int x = elf.pos.x - minX;
    int y = elf.pos.y - minY;
    printS[y][x] = '#';
  }
  std::cout << "=======================================" << std::endl;
  for(auto& s : printS)
  {
    std::cout << s << std::endl;
  }
}

void printElves(const std::set<Vector2I>& elves)
{
  int maxX = std::numeric_limits<int>::min();
  int maxY = std::numeric_limits<int>::min();
  int minX = std::numeric_limits<int>::max();
  int minY = std::numeric_limits<int>::max();

  for(auto& elf : elves)
  {
    maxX = std::max(maxX, elf.x);
    maxY = std::max(maxY, elf.y);
    minX = std::min(minX, elf.x);
    minY = std::min(minY, elf.y);
  }

  std::vector<std::string> printS(maxY - minY + 1, std::string(maxX - minX + 1, '.'));
  for(auto& elf : elves)
  {
    int x = elf.x - minX;
    int y = elf.y - minY;
    printS[y][x] = '#';
  }
  std::cout << "=======================================" << std::endl;
  for(auto& s : printS)
  {
    std::cout << s << std::endl;
  }
}

void computeSize(const std::set<Vector2I>& elves)
{
  int maxX = std::numeric_limits<int>::min();
  int maxY = std::numeric_limits<int>::min();
  int minX = std::numeric_limits<int>::max();
  int minY = std::numeric_limits<int>::max();

  for(auto& elf : elves)
  {
    maxX = std::max(maxX, elf.x);
    maxY = std::max(maxY, elf.y);
    minX = std::min(minX, elf.x);
    minY = std::min(minY, elf.y);
  }
  long long result = ( ( maxX - minX + 1 ) * ( maxY - minY + 1 ) ) - elves.size();
  std::cout << result << std::endl;;
}

// X > 3993  /// 4075
void day23Part1()
{
  std::ifstream inputFile(DAY23_PATH);
  adventDay23problem12022(inputFile);

  std::vector<std::string> input;
  readDocument(DAY23_PATH, input);

  std::set<Vector2I> elvesPos;
  std::map<Vector2I, int> newElvesPos;
  std::vector<Elf> elves;

  for(int i = 0; i < input.size(); ++i)
  {
    for(int j = 0; j < input.front().size(); ++j)
    {
      if(input[i][j] == '#')
      {
        Vector2I c(j, i);
        elvesPos.insert(c);
        elves.push_back(Elf(j, i));
      }
    }
  }

  const std::vector<std::vector<Vector2I>> checkPos = {{{-1, -1}, {0, -1}, {1, -1}},
                                                    {{-1, 1}, {0, 1}, {1, 1}}, 
                                                    {{-1, -1}, {-1, 0}, {-1, 1}}, 
                                                    {{1, -1}, {1, 0}, {1, 1}}};
  const std::vector<Vector2I> movePos = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

  //printElves(elvesPos);

  const int countSteps = 10;
  for (int i = 0; i < countSteps; ++i)
  {
    // Compute target position
    newElvesPos.clear();
    for(auto& elf : elves)
    {
      bool someElfAround = false;
      std::for_each(checkPos.begin(), checkPos.end(), [&](const std::vector<Vector2I>& vV)
                    {
                      std::for_each(vV.begin(), vV.end(), [&](const Vector2I v)
                                    {
                                      someElfAround |= elvesPos.contains(elf.pos + v);
                                    });
                    });
      if(!someElfAround)
      {
        newElvesPos[elf.pos]++;
        continue;
      }

      for(int k = 0; k < movePos.size(); ++k)
      {
        int checkId = ( i + k) % movePos.size();
        
        bool validMove = ( !elvesPos.contains(elf.pos + checkPos[checkId][0]) &&
                          !elvesPos.contains(elf.pos + checkPos[checkId][1]) &&
                          !elvesPos.contains(elf.pos + checkPos[checkId][2]) );
        Vector2I tc = elf.pos + movePos[checkId];

        if(validMove)
        {
          newElvesPos[tc]++;
          elf.posToMove = tc;
          break;
        }
      }
    }

    // Move to target position
    elvesPos.clear();
    for(auto& elf : elves)
    {
      if(newElvesPos[elf.posToMove] == 1)
      {
        elf.pos = elf.posToMove;
      }
      elvesPos.insert(elf.pos);
    }
    //printElves(elvesPos);
    std::cout << "Iteration: " << i << " score: ";
    computeSize(elvesPos);

  }

  int maxX = std::numeric_limits<int>::min();
  int maxY = std::numeric_limits<int>::min();
  int minX = std::numeric_limits<int>::max();
  int minY = std::numeric_limits<int>::max();

  for(auto& elf : elvesPos)
  {
    maxX = std::max(maxX, elf.x);
    maxY = std::max(maxY, elf.y);
    minX = std::min(minX, elf.x);
    minY = std::min(minY, elf.y);
  }

  long long result = ( ( maxX - minX + 1 ) * ( maxY - minY + 1 ) ) - elvesPos.size();
  printf("The solution for part 1 is: %lli \n", result);
}


void day23Part2()
{
  //std::vector<std::string> input;
  //readDocument(DAY23_PATH, input);
  //
  //std::set<Vector2I> elvesPos;
  //std::map<Vector2I, int> newElvesPos;
  //std::vector<Elf> elves;
  //
  //for(int i = 0; i < input.size(); ++i)
  //{
  //  for(int j = 0; j < input.front().size(); ++j)
  //  {
  //    if(input[i][j] == '#')
  //    {
  //      Vector2I c(j, i);
  //      elvesPos.insert(c);
  //      elves.push_back(Elf(j, i));
  //    }
  //  }
  //}
  //
  //const std::vector<std::vector<Vector2I>> checkPos = {{{-1, -1}, {0, -1}, {1, -1}},
  //                                                  {{-1, 1}, {0, 1}, {1, 1}},
  //                                                  {{-1, -1}, {-1, 0}, {-1, 1}},
  //                                                  {{1, -1}, {1, 0}, {1, 1}}};
  //const std::vector<Vector2I> movePos = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
  //
  //printElves(elvesPos);
  //
  //const int countSteps = 10;
  //for(int i = 0; i < 10; ++i)
  //{
  //  // Compute target position
  //  newElvesPos.clear();
  //  for(auto& elf : elves)
  //  {
  //    bool someElfAround = false;
  //    std::for_each(checkPos.begin(), checkPos.end(), [&](const std::vector<Vector2I>& vV)
  //                  {
  //                    std::for_each(vV.begin(), vV.end(), [&](const Vector2I v)
  //                                  {
  //                                    someElfAround |= elvesPos.contains(elf.pos + v);
  //                                  });
  //                  });
  //    if(!someElfAround)
  //      continue;
  //
  //    for(int k = 0; k < movePos.size(); ++k)
  //    {
  //      int checkId = ( i + k ) % movePos.size();
  //
  //      bool validMove = ( !elvesPos.contains(elf.pos + checkPos[checkId][0]) &&
  //                        !elvesPos.contains(elf.pos + checkPos[checkId][1]) &&
  //                        !elvesPos.contains(elf.pos + checkPos[checkId][2]) );
  //      Vector2I tc = elf.pos + movePos[checkId];
  //
  //      if(validMove)
  //      {
  //        newElvesPos[tc]++;
  //        elf.posToMove = tc;
  //        //elf.moveIndex = checkId;
  //        break;
  //      }
  //    }
  //  }
  //
  //  // Move to target position
  //  elvesPos.clear();
  //  for(auto& elf : elves)
  //  {
  //    if(newElvesPos[elf.posToMove] == 1)
  //    {
  //      elf.pos = elf.posToMove;
  //      //elf.moveIndex = ( elf.moveIndex + 1 ) % movePos.size();
  //    }
  //    elvesPos.insert(elf.pos);
  //  }
  //  printElves(elvesPos);
  //}
  //
  //int maxX = std::numeric_limits<int>::min();
  //int maxY = std::numeric_limits<int>::min();
  //int minX = std::numeric_limits<int>::max();
  //int minY = std::numeric_limits<int>::max();
  //
  //for(auto& elf : elves)
  //{
  //  maxX = std::max(maxX, elf.pos.x);
  //  maxY = std::max(maxY, elf.pos.y);
  //  minX = std::min(minX, elf.pos.x);
  //  minY = std::min(minY, elf.pos.y);
  //}
  //
  //long long result = ( ( maxX - minX + 1 ) * ( maxY - minY + 1 ) ) - elves.size();
  long long result = 0;
  printf("The solution for part 2 is: %lli \n", result);
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

