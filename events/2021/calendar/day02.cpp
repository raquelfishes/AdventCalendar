
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

#include "resources.h"

struct Instruction
{
    std::string type;
    unsigned int value;

    Instruction(std::string t, std::string val) : type(t)
    {
        value = std::stoi(val);
    }
};

void divePart1()
{
    std::string resourcePath = getResourcePath(2021, 2);
    // Open numbers file
    std::ifstream myfile(resourcePath);
    if (!myfile.is_open())
    {
        std::cout << "Error, no file founded" << std::endl;
        return;
    }

    std::vector<Instruction> commands;
    std::string line;
    std::regex expr("(\\w+) (\\d+)");
    std::smatch sm;

    while (getline(myfile, line))
    {
        if (std::regex_search(line, sm, expr))
        {
            Instruction inst(sm[1], sm[2]);
            commands.push_back(inst);
        }
    }
    if (commands.empty())
    {
        std::cout << "Error, no seats at file" << std::endl;
    }

    // Part 1:
    int x = 0;
    int y = 0;
    for (auto &cmd : commands)
    {
        if (cmd.type == "forward")
            x += cmd.value;
        else if (cmd.type == "down")
            y += cmd.value;
        else if (cmd.type == "up")
            y -= cmd.value;
    }
    int result = x * y;
    printf("The solution for part 1 is: %i \n", result);
}

void divePart2()
{
    std::string resourcePath = getResourcePath(2021, 2);
    std::ifstream myfile(resourcePath);
    if (!myfile.is_open())
    {
        std::cout << "Error, no file founded" << std::endl;
        return;
    }

    std::vector<Instruction> commands;
    std::string line;
    std::regex expr("(\\w+) (\\d+)");
    std::smatch sm;

    while (getline(myfile, line))
    {
        if (std::regex_search(line, sm, expr))
        {
            Instruction inst(sm[1], sm[2]);
            commands.push_back(inst);
        }
    }
    if (commands.empty())
    {
        std::cout << "Error, no seats at file" << std::endl;
    }

    int horizontal = 0;
    int depth = 0;
    int aim = 0;
    for (auto &cmd : commands)
    {
        if (cmd.type == "forward")
        {
            horizontal += cmd.value;
            depth += aim * cmd.value;
        }
        else if (cmd.type == "down")
            aim += cmd.value;
        else if (cmd.type == "up")
            aim -= cmd.value;
    }
    long result = horizontal * depth;

    printf("The solution for part 2 is: %i \n", result);
}
