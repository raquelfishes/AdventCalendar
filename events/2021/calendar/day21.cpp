
#include <vector>
#include <string>

#include "resources.h"
#include "utils_2021.h"

static const int numRollsDice = 3;
static const int trackSize = 10;
static const int numSidesDice = 100;
static const int winnerValue = 1000;

struct Player
{
    Player(const std::string s)
    {
        std::vector<std::string> values;
        std::string exp("Player (\\d) starting position: (\\d)");
        splitByRegex(s, exp, values);
        id = std::stoi(values[1]);
        initPosition = std::stoi(values[2]);
        currentPosition = initPosition;
        score = 0;
    }

    bool isWinner()
    {
        return score >= winnerValue;
    }

    void moveForward(int &diceValue)
    {
        for (int i = 0; i < numRollsDice; ++i)
        {
            auto auxPos = (currentPosition + diceValue) % trackSize;
            auto auxDice = (diceValue + 1) % numSidesDice;
            currentPosition = auxPos > 0 ? auxPos : 10;
            diceValue = auxDice > 0 ? auxDice : 100;
        }
        score += currentPosition;
    }

    int id = -1;
    int initPosition;
    int currentPosition;
    int score;
};

void diracDicePart1()
{
    std::string resourcePath = getResourcePath(2021, 21);

    std::vector<Player> players;
    readDocument<Player>(resourcePath, players);

    bool hasWinner = false;
    int diceValue = 1;
    int rollsDiceCount = 0;

    while (!hasWinner)
    {
        for (auto &player : players)
        {
            player.moveForward(diceValue);
            rollsDiceCount += numRollsDice;
            hasWinner = player.isWinner();
            if (hasWinner)
            {
                break;
            }
        }
    }

    long long scoreLooser = 0;
    for (auto &player : players)
    {
        if (player.isWinner())
            continue;
        scoreLooser = player.score * rollsDiceCount;
    }

    long long result = scoreLooser;
    printf("The solution for part 2 is: %lld \n", result);
}

void diracDicePart2()
{

    int result = 0;

    printf("The solution for part 2 is: %lld \n", result);
}
