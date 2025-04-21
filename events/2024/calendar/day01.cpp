#include <ranges>
#include <list>

#include "day_base.h"

#include "std_includes.h"
#include "resources.h"
#include "string_utils.h"
#include "read_documents_utils.h"

struct Line
{
    Line() = default;
    Line(const std::string &s)
    {
        std::vector<std::string> aux;
        splitStringByString(s, "   ", aux);
        for (auto &p : aux)
        {
            std::vector<std::string> aux2;
            splitStringByChar(p, ',', aux2);
            if (aux2.size() != 2)
                return;
            value.first = std::stoi(aux2.front());
            value.second = std::stoi(aux2.back());
        }
    }

    std::pair<int, int> value;
};


DEFINE_PROBLEM(2024, 01, 1)
//void problemEvent2024Day01Part1(ResourceType resourceType)
{
    std::cout << "Resolviendo Problema: Año 2021, Día 01, Parte 1" << std::endl;

    std::string resourcePath = getResourcePath(2024, 1, resourceType);
    std::vector<Line> lines;
    readDocument(resourcePath, lines);

    std::vector<int> values_right;
    std::vector<int> values_left;
    std::for_each(lines.begin(), lines.end(), [&](Line &line)
    { 
        values_right.push_back(line.value.first);
        values_right.push_back(line.value.second);
    });

    std::sort(values_right.begin(), values_right.end());
    std::sort(values_left.begin(), values_left.end());

    
    long long int result = 0;
    for(int i = 0; i < values_right.size(); ++i)
    {
        result += std::abs(values_right[i]-values_left[i]);
    }
    printf("The solution for part 1 is: %lli \n", result);

    // I
}