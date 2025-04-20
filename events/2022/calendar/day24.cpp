#include "std_includes.h"
#include "resources.h"
#include "utils_2022.h"
#include "grid.h"
#include "vector2.h"

struct Blizzard
{
    Blizzard() = default;
    Vector2I pos;
    Vector2I dir;
};

struct BoundingBox
{
    BoundingBox() = default;
    bool isInside(const Vector2I &v) const
    {
        return (v.x > min.x && v.x < max.x) && (v.y > min.y && v.y < max.y);
    }
    Vector2I min;
    Vector2I max;
};

void parseInput(const std::vector<std::string> input, std::vector<Blizzard> &blizzards, BoundingBox &bbox, Vector2I &init, Vector2I &end)
{
    // Parse blizzards
    blizzards.clear();
    for (int i = 1; i < input.size() - 1; ++i)
    {
        for (int j = 1; j < input.front().size() - 1; ++j)
        {
            if (input[i][j] != '.')
            {
                Blizzard aux;
                aux.pos = Vector2I(j, i);
                if (input[i][j] == '>')
                    aux.dir = Vector2I(1, 0);
                if (input[i][j] == '<')
                    aux.dir = Vector2I(-1, 0);
                if (input[i][j] == '^')
                    aux.dir = Vector2I(0, -1);
                if (input[i][j] == 'v')
                    aux.dir = Vector2I(0, 1);
                blizzards.push_back(aux);
            }
        }
    }

    // Parse Bounding Box
    bbox.min = Vector2I(0, 0);
    bbox.max = Vector2I(input.front().size() - 1, input.size() - 1);

    // Parse initPosition
    auto itInit = std::find(input.front().begin(), input.front().end(), '.');
    int aux = std::distance(input.front().begin(), itInit);
    init = Vector2I(aux, 0);

    // Parse endPosition
    auto itEnd = std::find(input.back().begin(), input.back().end(), '.');
    aux = std::distance(input.back().begin(), itEnd);
    end = Vector2I(aux, input.size() - 1);
}

int reachGoal(const Vector2I &initPos, const Vector2I &endPos, std::vector<Blizzard> &blizzards, const BoundingBox &box)
{
    std::vector<Vector2I> typeMoves = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {0, 0}};
    std::set<Vector2I> currentPositions;
    currentPositions.insert(initPos);

    int countSteps = 0;
    while (!currentPositions.contains(endPos))
    {
        std::set<Vector2I> nextPositions;
        std::set<Vector2I> blizzardsPos;
        for (auto &bli : blizzards)
        {
            bli.pos += bli.dir;
            if (bli.pos.x == box.min.x)
                bli.pos.x = box.max.x - 1;
            if (bli.pos.y == box.min.y)
                bli.pos.y = box.max.y - 1;
            if (bli.pos.x == box.max.x)
                bli.pos.x = box.min.x + 1;
            if (bli.pos.y == box.max.y)
                bli.pos.y = box.min.y + 1;
            blizzardsPos.insert(bli.pos);
        }

        for (auto &pos : currentPositions)
        {
            for (auto &move : typeMoves)
            {
                Vector2I newPos = pos + move;
                if (!blizzardsPos.contains(newPos) &&
                    (box.isInside(newPos) || newPos == initPos || newPos == endPos))
                {
                    nextPositions.insert(newPos);
                }
            }
        }

        currentPositions = nextPositions;
        countSteps++;
    }
    return countSteps;
}

void day24Part1()
{
    std::string resourcePath = getResourcePath(2022, 24);
    std::vector<std::string> input;
    readDocument(resourcePath, input);

    // Read info
    std::vector<Blizzard> blizzards;
    Vector2I initPosition, endPosition;
    BoundingBox bbox;
    parseInput(input, blizzards, bbox, initPosition, endPosition);

    int countSteps = reachGoal(initPosition, endPosition, blizzards, bbox);

    long long result = countSteps;
    printf("The solution for part 1 is: %lli \n", result);
}

void day24Part2()
{
    std::string resourcePath = getResourcePath(2022, 24);
    std::vector<std::string> input;
    readDocument(resourcePath, input);

    // Read info
    std::vector<Blizzard> blizzards;
    Vector2I initPosition, endPosition;
    BoundingBox bbox;
    parseInput(input, blizzards, bbox, initPosition, endPosition);

    int countSteps = reachGoal(initPosition, endPosition, blizzards, bbox);
    countSteps += reachGoal(endPosition, initPosition, blizzards, bbox);
    countSteps += reachGoal(initPosition, endPosition, blizzards, bbox);

    long long result = countSteps;
    printf("The solution for part 2 is: %lli \n", result);
}
