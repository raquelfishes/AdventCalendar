#include "std_includes.h"
#include "resources.h"
#include "utils_2022.h"
#include "vector2.h"

struct Elf
{
    Elf(const int &x, const int &y)
    {
        pos = Vector2I(x, y);
    }
    Vector2I pos;
    Vector2I posToMove;
    int moveIndex = 0;
};

void printElves(const std::vector<Elf> &elves)
{
    int maxX = std::numeric_limits<int>::min();
    int maxY = std::numeric_limits<int>::min();
    int minX = std::numeric_limits<int>::max();
    int minY = std::numeric_limits<int>::max();

    for (auto &elf : elves)
    {
        maxX = std::max(maxX, elf.pos.x);
        maxY = std::max(maxY, elf.pos.y);
        minX = std::min(minX, elf.pos.x);
        minY = std::min(minY, elf.pos.y);
    }

    std::vector<std::string> printS(maxY - minY + 1, std::string(maxX - minX + 1, '.'));
    for (auto &elf : elves)
    {
        int x = elf.pos.x - minX;
        int y = elf.pos.y - minY;
        printS[y][x] = '#';
    }
    std::cout << "=======================================" << std::endl;
    for (auto &s : printS)
    {
        std::cout << s << std::endl;
    }
}

void printElves(const std::set<Vector2I> &elves)
{
    int maxX = std::numeric_limits<int>::min();
    int maxY = std::numeric_limits<int>::min();
    int minX = std::numeric_limits<int>::max();
    int minY = std::numeric_limits<int>::max();

    for (auto &elf : elves)
    {
        maxX = std::max(maxX, elf.x);
        maxY = std::max(maxY, elf.y);
        minX = std::min(minX, elf.x);
        minY = std::min(minY, elf.y);
    }

    std::vector<std::string> printS(maxY - minY + 1, std::string(maxX - minX + 1, '.'));
    for (auto &elf : elves)
    {
        int x = elf.x - minX;
        int y = elf.y - minY;
        printS[y][x] = '#';
    }
    std::cout << "=======================================" << std::endl;
    for (auto &s : printS)
    {
        std::cout << s << std::endl;
    }
}

long long computeSize(const std::set<Vector2I> &elves)
{
    int maxX = std::numeric_limits<int>::min();
    int maxY = std::numeric_limits<int>::min();
    int minX = std::numeric_limits<int>::max();
    int minY = std::numeric_limits<int>::max();

    for (auto &elf : elves)
    {
        maxX = std::max(maxX, elf.x);
        maxY = std::max(maxY, elf.y);
        minX = std::min(minX, elf.x);
        minY = std::min(minY, elf.y);
    }
    long long result = ((maxX - minX + 1) * (maxY - minY + 1)) - elves.size();
    // std::cout << result << std::endl;;
    return result;
}

// X > 3993  /// 4075
void day23Part1()
{
    // std::ifstream inputFile(DAY23_PATH);
    // adventDay23problem12022(inputFile);

    std::string resourcePath = getResourcePath(2022, 23);
    std::vector<std::string> input;
    readDocument(resourcePath, input);

    std::set<Vector2I> elvesPos;
    std::map<Vector2I, int> newElvesPos;
    std::vector<Elf> elves;

    for (int i = 0; i < input.size(); ++i)
    {
        for (int j = 0; j < input.front().size(); ++j)
        {
            if (input[i][j] == '#')
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

    // printElves(elvesPos);

    const int countSteps = 10;
    for (int i = 0; i < countSteps; ++i)
    {
        // Compute target position
        newElvesPos.clear();
        for (auto &elf : elves)
        {
            bool someElfAround = false;
            std::for_each(checkPos.begin(), checkPos.end(), [&](const std::vector<Vector2I> &vV)
                          { std::for_each(vV.begin(), vV.end(), [&](const Vector2I v)
                                          { someElfAround |= elvesPos.contains(elf.pos + v); }); });
            if (!someElfAround)
            {
                newElvesPos[elf.pos]++;
                elf.posToMove = elf.pos;
                continue;
            }

            for (int k = 0; k < movePos.size(); ++k)
            {
                int checkId = (i + k) % movePos.size();

                bool validMove = (!elvesPos.contains(elf.pos + checkPos[checkId][0]) &&
                                  !elvesPos.contains(elf.pos + checkPos[checkId][1]) &&
                                  !elvesPos.contains(elf.pos + checkPos[checkId][2]));
                Vector2I tc = elf.pos + movePos[checkId];

                if (validMove)
                {
                    newElvesPos[tc]++;
                    elf.posToMove = tc;
                    break;
                }
            }
        }

        // Move to target position
        elvesPos.clear();
        for (auto &elf : elves)
        {
            if (newElvesPos[elf.posToMove] == 1)
            {
                elf.pos = elf.posToMove;
            }
            elvesPos.insert(elf.pos);
        }
        // printElves(elvesPos);
        // std::cout << "Iteration: " << i << "elves: " << elvesPos.size() << " | " << elves.size() << " score: ";
        // computeSize(elvesPos);
    }

    long long result = computeSize(elvesPos);
    printf("The solution for part 1 is: %lli \n", result);
}

void day23Part2()
{
    std::string resourcePath = getResourcePath(2022, 23);
    std::vector<std::string> input;
    readDocument(resourcePath, input);

    std::set<Vector2I> elvesPos;
    std::map<Vector2I, int> newElvesPos;
    std::vector<Elf> elves;

    for (int i = 0; i < input.size(); ++i)
    {
        for (int j = 0; j < input.front().size(); ++j)
        {
            if (input[i][j] == '#')
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

    // printElves(elvesPos);

    int countSteps = 0;
    bool someElfMove = true;
    while (someElfMove)
    {
        someElfMove = false;
        // Compute target position
        newElvesPos.clear();
        for (auto &elf : elves)
        {
            bool someElfAround = false;
            std::for_each(checkPos.begin(), checkPos.end(), [&](const std::vector<Vector2I> &vV)
                          { std::for_each(vV.begin(), vV.end(), [&](const Vector2I v)
                                          { someElfAround |= elvesPos.contains(elf.pos + v); }); });

            someElfMove |= someElfAround;
            if (!someElfAround)
            {
                newElvesPos[elf.pos]++;
                elf.posToMove = elf.pos;
                continue;
            }

            for (int k = 0; k < movePos.size(); ++k)
            {
                int checkId = (countSteps + k) % movePos.size();

                bool validMove = (!elvesPos.contains(elf.pos + checkPos[checkId][0]) &&
                                  !elvesPos.contains(elf.pos + checkPos[checkId][1]) &&
                                  !elvesPos.contains(elf.pos + checkPos[checkId][2]));
                Vector2I tc = elf.pos + movePos[checkId];

                if (validMove)
                {
                    newElvesPos[tc]++;
                    elf.posToMove = tc;
                    break;
                }
            }
        }

        // Move to target position
        elvesPos.clear();

        for (auto &elf : elves)
        {
            if (newElvesPos[elf.posToMove] == 1)
            {
                elf.pos = elf.posToMove;
            }
            elvesPos.insert(elf.pos);
        }
        countSteps++;
        // printElves(elvesPos);
        // std::cout << "Iteration: " << i << "elves: " << elvesPos.size() << " | " << elves.size() << " score: ";
        // computeSize( elvesPos );
    }

    long long result = countSteps;
    printf("The solution for part 2 is: %lli \n", result);
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
