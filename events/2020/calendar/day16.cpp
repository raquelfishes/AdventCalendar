#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <regex>
#include <numeric>
#include <limits>

#include "resources.h"

struct TicketRule
{
    std::string name;
    std::vector<std::pair<int, int>> validRule;
    std::vector<int> validPositions;

    bool isValid(int id)
    {
        for (auto &rule : validRule)
        {
            if (id >= rule.first && id <= rule.second)
                return true;
        }
        return false;
    }
};

void adventDay16()
{
    std::string resourcePath = getResourcePath(2020, 16);
    // Open numbers file
    std::ifstream myfile(resourcePath);
    if (!myfile.is_open())
    {
        std::cout << "Error, no file found" << std::endl;
        return;
    }

    std::vector<TicketRule> rules;
    std::string line;
    std::regex fieldExpr("(.*): (\\d+)-(\\d+) or (\\d+)-(\\d+)");
    std::smatch sm;
    bool nearbyTickets = false;
    std::vector<int> mySeat;
    std::vector<std::vector<int>> nearbySeats;
    while (getline(myfile, line))
    {
        if (std::regex_search(line, sm, fieldExpr))
        {
            TicketRule rule;
            rule.name = sm[1];
            std::pair<int, int> vR1(std::stoi(sm[2].str()), std::stoi(sm[3].str()));
            rule.validRule.push_back(vR1);
            std::pair<int, int> vR2(std::stoi(sm[4].str()), std::stoi(sm[5].str()));
            rule.validRule.push_back(vR2);
            rules.push_back(rule);
        }
        else if (line == "your ticket:")
        {
            getline(myfile, line);
            std::stringstream ss(line);
            std::string value;
            while (getline(ss, value, ','))
            {
                mySeat.push_back(std::stoi(value));
            }
        }
        else if (line == "nearby tickets:")
        {
            nearbyTickets = true;
        }
        else if (nearbyTickets)
        {
            std::stringstream ss(line);
            std::string value;
            std::vector<int> seats;
            while (getline(ss, value, ','))
            {
                seats.push_back(std::stoi(value));
            }
            nearbySeats.push_back(seats);
        }
    }

    std::vector<std::vector<int>> allTickets = {mySeat};

    std::vector<int> invalidSeats;
    for (auto &nearbySeat : nearbySeats)
    {
        auto sizeInvalidSeats = invalidSeats.size();
        for (auto &seat : nearbySeat)
        {
            bool validSeat = false;
            for (auto &rule : rules)
            {
                if (rule.isValid(seat))
                {
                    validSeat = true;
                    break;
                }
            }
            if (!validSeat)
            {
                invalidSeats.push_back(seat);
                break;
            }
        }
        if (invalidSeats.size() == sizeInvalidSeats)
        {
            allTickets.push_back(nearbySeat);
        }
    }

    int scanningError = std::accumulate(invalidSeats.begin(), invalidSeats.end(), 0);
    std::cout << "Par1: The result is: " << scanningError << std::endl;

    std::vector<std::string> orderedFields;
    orderedFields.resize(mySeat.size());
    for (auto i = 0; i < mySeat.size(); ++i)
    {
        for (auto &rule : rules)
        {
            bool validRule = true;
            for (auto &ticket : allTickets)
            {
                if (!rule.isValid(ticket[i]))
                {
                    validRule = false;
                    break;
                }
            }
            if (validRule)
            {
                rule.validPositions.push_back(i);
            }
        }
    }

    std::sort(rules.begin(), rules.end(), [](TicketRule &ruleA, TicketRule &ruleB)
              { return ruleA.validPositions.size() < ruleB.validPositions.size(); });

    for (auto i = 0; i < rules.size(); ++i)
    {
        for (auto j = i + 1; j < rules.size(); ++j)
        {
            auto it = std::find(rules[j].validPositions.begin(), rules[j].validPositions.end(), rules[i].validPositions[0]);
            rules[j].validPositions.erase(it);
        }
    }

    long long departureFields = 1;
    for (auto &rule : rules)
    {
        if (rule.name.find("departure") != std::string::npos)
        {
            departureFields *= mySeat[rule.validPositions[0]];
        }
    }
    std::cout << "Par2: The result is: " << departureFields << std::endl;
}
