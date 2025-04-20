#include "std_includes.h"
#include "resources.h"
#include "utils_2022.h"

typedef std::bitset<7> RockLine;
typedef std::vector<RockLine> Rock;

const std::vector<Rock> stones = {
    {RockLine(0x1E)},
    {RockLine(0x8), RockLine(0x1C), RockLine(0x8)},
    {RockLine(0x1C), RockLine(0x4), RockLine(0x4)},
    {RockLine(0x10), RockLine(0x10), RockLine(0x10), RockLine(0x10)},
    {RockLine(0x18), RockLine(0x18)}};

bool checkMoveToStack(const Rock &stone, const Rock &stackRocks, const long long line)
{
    for (int i = 0; i < stone.size(); ++i)
    {
        long long checkNewLine = line + i;
        if (checkNewLine >= stackRocks.size())
            break;
        auto stackLine = stackRocks[checkNewLine];
        if ((stackLine & stone[i]).any())
        {
            return false;
        }
    }
    return true;
}

bool checkMoveCurrent(const Rock &stone, const Rock &stackRock, const long long line, const char c)
{
    bool canMove = true;
    Rock auxRock = stone;
    if (c == '<')
        std::for_each(auxRock.begin(), auxRock.end(), [&canMove](RockLine &b)
                      { canMove &= (b.count() == (b << 1).count()); });
    else if (c == '>')
        std::for_each(auxRock.begin(), auxRock.end(), [&canMove](RockLine &b)
                      { canMove &= (b.count() == (b >> 1).count()); });
    if (!canMove)
        return false;
    if (c == '<' && canMove)
        std::for_each(auxRock.begin(), auxRock.end(), [&canMove](RockLine &b)
                      { b <<= 1; });
    if (c == '>' && canMove)
        std::for_each(auxRock.begin(), auxRock.end(), [&canMove](RockLine &b)
                      { b >>= 1; });

    canMove = checkMoveToStack(auxRock, stackRock, line);

    return canMove;
}

long long moveToStartHeight(std::vector<RockLine> &stackRocks, const std::vector<RockLine> &rock)
{
    const int emptyLines = 3;
    // Add 3 empty rows plus size of rock
    long long currLine = stackRocks.size() + emptyLines;
    for (int i = 0; i < emptyLines + rock.size(); ++i)
        stackRocks.push_back(RockLine());

    return currLine;
}

void applyMove(const std::vector<RockLine> &stackRocks, std::vector<RockLine> &rock, long long line, const char c)
{
    if (c == '<')
    {
        bool canMove = checkMoveCurrent(rock, stackRocks, line, c);
        if (canMove)
            std::for_each(rock.begin(), rock.end(), [&canMove](RockLine &b)
                          { b <<= 1; });
    }
    else if (c == '>')
    {
        bool canMove = checkMoveCurrent(rock, stackRocks, line, c);
        if (canMove)
            std::for_each(rock.begin(), rock.end(), [&canMove](RockLine &b)
                          { b >>= 1; });
    }
}

void checkMoveDown(const std::vector<RockLine> &stackRocks, const std::vector<RockLine> &rock, long long &line, bool &down)
{
    // Check if the rock can go down;
    for (int i = 0; i < rock.size(); ++i)
    {
        long long checkNewLine = line - 1 + i;
        if (checkNewLine >= stackRocks.size())
            break;
        auto stackLine = stackRocks[checkNewLine];
        if ((stackLine & rock[i]).any())
        {
            down = false;
            break;
        }
    }
    if (down)
        line--;
}

void day17Part1()
{
    std::string resourcePath = getResourcePath(2022, 17);
    std::vector<std::string> input;
    readDocument(resourcePath, input);

    std::string inputStr = input.front();

    int countRocks = 0;
    const int maxRocks = 2022;
    int idInput = 0;
    int idStone = 0;
    std::vector<RockLine> stackRocks;
    stackRocks.push_back(RockLine(0x7F));

    while (countRocks < maxRocks)
    {
        auto currentRock = stones[(idStone++) % stones.size()];

        // Add empty lines
        long long currLine = moveToStartHeight(stackRocks, currentRock);

        bool testToDown = true;
        while (testToDown)
        {
            // Move rock (moving bits)
            char c = inputStr[(idInput++) % inputStr.size()];
            applyMove(stackRocks, currentRock, currLine, c);
            checkMoveDown(stackRocks, currentRock, currLine, testToDown);
        }

        // Add currRock to stack
        for (int i = 0; i < currentRock.size(); ++i)
        {
            stackRocks[currLine + i] |= currentRock[i];
        }

        // Remove empty lines
        while (stackRocks.back().none())
            stackRocks.pop_back();

        countRocks++;
    }

    long long result = stackRocks.size() - 1;
    printf("The solution for part 1 is: %lli \n", result);
}

struct CacheState
{
    CacheState() = default;
    int idRock;
    int idInput;
    std::vector<int> heightMap = std::vector<int>(7, -1);
    long long countRocks;
    long long rocksHeight;
    int nextCache;
};

// EX. 1514285714288
// X > 1528901734093
void day17Part2()
{
    std::string resourcePath = getResourcePath(2022, 17);
    std::vector<std::string> input;
    readDocument(resourcePath, input);

    std::string inputStr = input.front();

    const int width = 7;
    int countRocks = 0;
    const long long maxRocks = 1000000000000;
    int idInput = 0;
    int idStone = 0;
    std::vector<RockLine> stackRocks;
    stackRocks.push_back(RockLine(0x7F));
    std::vector<int> heightMap(7, 0);
    std::vector<CacheState> cacheVector;

    long long rocksHeight;
    while (countRocks < maxRocks)
    {
        CacheState cacheState;
        cacheState.idRock = idStone % stones.size();
        cacheState.idInput = idInput % inputStr.size();
        cacheState.countRocks = countRocks;
        cacheState.rocksHeight = stackRocks.size();
        for (int i = 0; i < width; ++i)
        {
            int h = 0;
            int l = stackRocks.size() - 1;
            while (!stackRocks[l].test(i))
                l--;
            cacheState.heightMap[i] = stackRocks.size() - l;
        }

        auto found = std::find_if(cacheVector.begin(), cacheVector.end(), [&](const CacheState &cS)
                                  { return (cS.idInput == cacheState.idInput && cS.idRock == cacheState.idRock && cS.heightMap == cacheState.heightMap); });
        if (found != cacheVector.end())
        {
            long long cycleStart = found->countRocks;
            long long cycleEnd = countRocks;
            long long cycleWidth = cycleEnd - cycleStart;

            long long heightEnd = stackRocks.size();
            long long heightStart = found->rocksHeight;

            long long repeats = (maxRocks - cycleStart) / cycleWidth;
            long long repeatedHeight = repeats * (heightEnd - heightStart);

            long long remaining = (maxRocks - cycleStart) % cycleWidth;

            std::advance(found, remaining);
            long long remainingHeight = found->rocksHeight - heightStart;

            rocksHeight = heightStart + repeatedHeight + remainingHeight;
            break;
        }

        cacheVector.push_back(cacheState);

        auto currentRock = stones[(idStone++) % stones.size()];
        // Add empty lines
        long long currLine = moveToStartHeight(stackRocks, currentRock);

        bool testToDown = true;
        while (testToDown)
        {
            // Move rock (moving bits)
            char c = inputStr[(idInput++) % inputStr.size()];
            applyMove(stackRocks, currentRock, currLine, c);
            checkMoveDown(stackRocks, currentRock, currLine, testToDown);
        }

        // Add currRock to stack
        for (int i = 0; i < currentRock.size(); ++i)
        {
            stackRocks[currLine + i] |= currentRock[i];
        }

        // Remove empty lines
        while (stackRocks.back().none())
            stackRocks.pop_back();

        countRocks++;
    }

    long long result = rocksHeight - 1;
    printf("The solution for part 2 is: %lli \n", result);
}
