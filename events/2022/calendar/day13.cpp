#include "std_includes.h"
#include "resources.h"
#include "utils_2022.h"

struct Packet : std::vector<std::variant<int, Packet>>
{
    using std::vector<std::variant<int, Packet>>::vector;
};

// typedef std::vector<std::variant<int, Packet>> Packet;

Packet convertToPacket(const std::string s)
{
    Packet pac;
    std::stack<Packet> stPac;
    stPac.push(pac);

    for (int i = 0; i < s.length(); ++i)
    {
        const char c = s[i];
        if (c == '[')
        {
            stPac.push(Packet());
        }
        else if (c == ']')
        {
            Packet auxPac = stPac.top();
            stPac.pop();
            stPac.top().emplace_back(auxPac);
        }
        else if (c == ',')
        {
            ;
        }
        else
        {
            if (s[i + 1] == ',' || s[i + 1] == ']')
            {
                stPac.top().push_back(std::stoi(s.substr(i, 1)));
            }
            else if (s[i + 2] == ',' || s[i + 2] == ']')
            {
                stPac.top().push_back(std::stoi(s.substr(i, 2)));
                i++;
            }
        }
    }
    return stPac.top();
}

template <typename... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};
template <typename... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

enum result_enum
{
    e_wrong_order = 0,
    e_correct_order,
    e_equal_order
};

result_enum correctOrderPackets(Packet p1, Packet p2)
{
    result_enum correct = e_equal_order;
    for (int i = 0; i < std::max(p1.size(), p2.size()) && correct == e_equal_order; ++i)
    {
        if (i == p1.size())
            return e_correct_order;
        else if (i == p2.size())
            return e_wrong_order;
        else
        {
            correct = std::visit(overloaded{[](const Packet &p1, const Packet &p2)
                                            { return correctOrderPackets(p1, p2); },
                                            [](const Packet &p1, int p2)
                                            { return correctOrderPackets(p1, {p2}); },
                                            [](int p1, const Packet &p2)
                                            { return correctOrderPackets({p1}, p2); },
                                            [](int p1, int p2)
                                            {
                                                if (p1 < p2)
                                                {
                                                    return e_correct_order;
                                                }
                                                else if (p1 > p2)
                                                {
                                                    return e_wrong_order;
                                                }
                                                else
                                                {
                                                    return e_equal_order;
                                                }
                                            }},
                                 p1[i], p2[i]);
        }
    }

    return correct;
}

struct PacketsPair
{
    PacketsPair(std::vector<std::string> &vs)
    {
        if (vs.size() != 2)
            return;
        pack1 = convertToPacket(vs.front());
        pack2 = convertToPacket(vs.back());
    }

    bool correctOrder()
    {
        return correctOrderPackets(pack1, pack2);
    }

    Packet pack1;
    Packet pack2;
};

void day13Part1()
{
    std::string resourcePath = getResourcePath(2022, 13);
    std::vector<PacketsPair> input;
    readDocumentSeveralLines(resourcePath, 2, input);

    long long sumIndices = 0;
    for (int i = 0; i < input.size(); ++i)
    {
        if (input[i].correctOrder())
        {
            sumIndices += i + 1;
        }
    }

    long long result = sumIndices;
    printf("The solution for part 1 is: %lli \n", result);
}

void day13Part2()
{
    std::string resourcePath = getResourcePath(2022, 13);
    std::vector<std::string> input;
    readDocument(resourcePath, input);

    std::vector<Packet> inputPackets;
    for (auto s : input)
    {
        if (s.empty())
            continue;
        inputPackets.push_back(convertToPacket(s));
    }
    Packet div1 = convertToPacket("[[2]]");
    inputPackets.push_back(div1);
    Packet div2 = convertToPacket("[[6]]");
    inputPackets.push_back(div2);

    std::sort(inputPackets.begin(), inputPackets.end(), correctOrderPackets);

    int indDiv1 = std::distance(inputPackets.begin(), std::find(inputPackets.begin(), inputPackets.end(), div1)) + 1;
    int indDiv2 = std::distance(inputPackets.begin(), std::find(inputPackets.begin(), inputPackets.end(), div2)) + 1;

    long long result = indDiv1 * indDiv2;
    printf("The solution for part 2 is: %lli \n", result);
}
