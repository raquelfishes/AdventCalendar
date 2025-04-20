#include "std_includes.h"
#include "resources.h"
#include "utils_2022.h"
#include "grid.h"

struct Instruction
{
    Instruction(const std::string &s)
    {
        std::vector<std::string> inputs;
        std::string regExp = "(\\w+) (\\d+)";
        splitByRegex(s, regExp, inputs);
        countMoves = std::stoi(inputs[2]);
        if (inputs[1] == "R")
            dirX = 1;
        if (inputs[1] == "L")
            dirX = -1;
        if (inputs[1] == "U")
            dirY = 1;
        if (inputs[1] == "D")
            dirY = -1;
    }

    int dirX = 0;
    int dirY = 0;
    int countMoves = 0;
};

void day9Part1()
{
    std::string resourcePath = getResourcePath(2022, 9);
    std::vector<Instruction> input;
    readDocument<Instruction>(resourcePath, input);

    std::set<Coord> tailVisited;

    Coord initPos(0, 0);
    Coord headPos = initPos;
    Coord tailPos = initPos;
    tailVisited.insert(initPos);

    for (auto &inst : input)
    {
        int moved = inst.countMoves;
        while (moved > 0)
        {
            Coord oldHeadPos = headPos;

            headPos.first += inst.dirX;
            headPos.second += inst.dirY;

            Coord diffHeadTail((headPos.first - tailPos.first), (headPos.second - tailPos.second));
            if (std::abs(diffHeadTail.first) > 1 || std::abs(diffHeadTail.second) > 1)
            {
                tailPos = oldHeadPos;
                tailVisited.insert(tailPos);
            }
            moved--;
        }
    }

    long long result = tailVisited.size();
    printf("The solution for part 1 is: %lli \n", result);
}

void day9Part2()
{
    std::string resourcePath = getResourcePath(2022, 9);
    std::vector<Instruction> input;
    readDocument<Instruction>(resourcePath, input);

    std::set<Coord> tailVisited;
    const int numKnots = 10;

    Coord initPos(0, 0);
    std::vector<Coord> ropePos(numKnots, initPos);
    tailVisited.insert(initPos);

    for (auto &inst : input)
    {
        int moved = inst.countMoves;
        while (moved > 0)
        {
            Coord oldPos = ropePos[0];
            ropePos.front().first += inst.dirX;
            ropePos.front().second += inst.dirY;

            for (int i = 1; i < numKnots; ++i)
            {
                Coord auxOldPos = ropePos[i];
                Coord diffToPrev((ropePos[i - 1].first - ropePos[i].first), (ropePos[i - 1].second - ropePos[i].second));
                int diffValue = std::abs(diffToPrev.first) + std::abs(diffToPrev.second);
                if (std::abs(diffToPrev.first) <= 1 && std::abs(diffToPrev.second) <= 1)
                    continue;
                else
                {
                    int moveX = std::min(std::abs(diffToPrev.first), 1);
                    if (diffToPrev.first < 0)
                        moveX *= -1;
                    int moveY = std::min(std::abs(diffToPrev.second), 1);
                    if (diffToPrev.second < 0)
                        moveY *= -1;
                    ropePos[i].first = ropePos[i].first + moveX;
                    ropePos[i].second = ropePos[i].second + moveY;
                }
            }
            tailVisited.insert(ropePos.back());
            moved--;
        }
    }

    long long result = tailVisited.size();
    printf("The solution for part 2 is: %lli \n", result);
}
