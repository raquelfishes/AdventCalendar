#include "std_includes.h"
#include "resources.h"
#include "utils_2022.h"

struct Movement
{
    Movement(const std::string &s)
    {
        std::vector<std::string> values;
        std::string regExp = "move (\\d+) from (\\d+) to (\\d+)";
        splitByRegex(s, regExp, values);
        count = std::stoi(values[1]);
        fromCol = std::stoi(values[2]) - 1;
        toCol = std::stoi(values[3]) - 1;
    }

    int count;
    int fromCol;
    int toCol;
};

struct Ship
{
    Ship(const std::vector<std::string> &vs)
    {
        int countChars = vs.front().length() + 1;
        int countStacks = countChars / 4;
        stacks.resize(countStacks);
        for (int i = vs.size() - 2; i >= 0; --i)
        {
            for (int j = 0; j < countStacks; ++j)
            {
                char aux = vs[i][1 + 4 * j];
                if (aux != ' ')
                    stacks[j].push(vs[i][1 + 4 * j]);
            }
        }
    }

    std::vector<std::stack<char>> stacks;
};

void day5Part1()
{
    std::string resourcePath = getResourcePath(2022, 5);
    std::vector<std::string> input;
    readDocumentUntilEmptyLine(resourcePath, input);
    Ship ship(input);
    std::vector<Movement> movements;
    readDocumentFromEmptyLine<Movement>(resourcePath, movements);

    for (auto &move : movements)
    {
        for (int i = 0; i < move.count; ++i)
        {
            int aux = ship.stacks[move.fromCol].top();
            ship.stacks[move.fromCol].pop();
            ship.stacks[move.toCol].push(aux);
        }
    }

    std::string result = "";
    for (auto &stack : ship.stacks)
    {
        result.push_back(stack.top());
    }

    printf("The solution for part 1 is: %s \n", result.c_str());
}

void day5Part2()
{
    std::string resourcePath = getResourcePath(2022, 5);
    std::vector<std::string> input;
    readDocumentUntilEmptyLine(resourcePath, input);
    Ship ship(input);
    std::vector<Movement> movements;
    readDocumentFromEmptyLine<Movement>(resourcePath, movements);

    for (auto &move : movements)
    {
        std::stack<char> auxStack;
        for (int i = 0; i < move.count; ++i)
        {
            char aux = ship.stacks[move.fromCol].top();
            auxStack.push(aux);
            ship.stacks[move.fromCol].pop();
        }
        for (int i = 0; i < move.count; ++i)
        {
            char aux = auxStack.top();
            auxStack.pop();
            ship.stacks[move.toCol].push(aux);
        }
    }

    std::string result = "";
    for (auto &stack : ship.stacks)
    {
        result.push_back(stack.top());
    }

    printf("The solution for part 2 is: %s \n", result.c_str());
}
