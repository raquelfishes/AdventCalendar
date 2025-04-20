#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <regex>
#include <numeric>

#include "resources.h"

struct Bag
{
    std::string color;
    std::map<std::string, int> containsBags;
};

void findValidBags(const std::vector<Bag> bags, std::set<std::string> &validBags)
{
    const int numberOfValids = validBags.size();
    for (auto bag : bags)
    {
        for (auto containBag : bag.containsBags)
        {
            if (std::find(validBags.begin(), validBags.end(), containBag.first) != validBags.end())
            {
                validBags.insert(bag.color);
                break;
            }
        }
    }
    if (numberOfValids == validBags.size())
        return;
    findValidBags(bags, validBags);
}

int countBags(const std::vector<Bag> bags, const std::string &color)
{
    int count = 0;
    for (auto bag : bags)
    {
        if (bag.color == color)
        {
            for (auto containBag : bag.containsBags)
            {
                count += containBag.second + containBag.second * countBags(bags, containBag.first);
            }
        }
    }
    return count;
}

void adventDay7()
{
    std::string resourcePath = getResourcePath(2020, 7);
    // Open numbers file
    std::ifstream myfile(resourcePath);
    if (!myfile.is_open())
    {
        std::cout << "Error, no file found" << std::endl;
        return;
    }

    std::vector<Bag> bags;
    std::string line;
    std::regex noBag("(.*) bags contain no other bags");
    // std::regex validBag( "(.*) bags contain( (\\d+)* (\\w+\\s\\w+) bag(s)*(,|.))+" );
    std::regex validBag("(.*) bags contain (\\d+)* (\\w+\\s\\w+) bag(s)*");
    std::regex restBag("(\\d+) (\\w+\\s\\w+) bag(s)*");
    std::smatch sm;

    while (getline(myfile, line))
    {
        // Bag contains nothing
        if (std::regex_search(line, sm, noBag))
            continue;

        if (std::regex_search(line, sm, validBag))
        {
            Bag bag;
            bag.color = sm[1];

            int number = std::stoi(sm[2].str());
            std::string color = sm[3].str();
            bag.containsBags.insert(std::pair<std::string, int>(color, number));
            std::string aux = sm.suffix().str();
            while (std::regex_search(aux, sm, restBag))
            {
                int number = std::stoi(sm[1].str());
                std::string color = sm[2].str();
                bag.containsBags.insert(std::pair<std::string, int>(color, number));
                aux = sm.suffix().str();
            }

            bags.push_back(bag);
        }
    }
    if (bags.empty())
    {
        std::cout << "Error, no valid bags at file" << std::endl;
    }

    std::set<std::string> validBags = {"shiny gold"};
    findValidBags(bags, validBags);
    std::cout << "Part1: The number of bages can contain my bag are: " << validBags.size() - 1 << std::endl;

    int count = countBags(bags, "shiny gold");

    std::cout << "Part2: My shiny gold bag has inside all this bags: " << count << std::endl;
}
