
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <numeric>
#include <memory>

#include "resources.h"
#include "utils_2021.h"

#define STARTNODE "start"
#define ENDNODE "end"

struct Edge
{
    Edge(std::string s)
    {
        std::vector<std::string> splited;
        splitString(s, '-', splited);
        n1 = splited[0];
        n2 = splited[1];
    }
    std::string n1;
    std::string n2;
};

struct Node
{
    Node(std::string name, int visited)
        : name(name), visited(visited)
    {
    }

    bool isUpper()
    {
        return isUppercase(name);
    }

    std::string name;
    std::set<std::string> connections;
    int visited;
};

struct Graph
{
    Graph() {};

    void addNode(const std::string &n)
    {
        if (nodes.count(n) == 0)
        {
            // This node name doesnt exist in the graph
            auto nptr = std::make_shared<Node>(n, false);
            std::pair<std::string, std::shared_ptr<Node>> nodePair(n, nptr);
            nodes.insert(nodePair);
        }
    }

    void addEdge(const Edge &e)
    {
        // Add nodes to graph
        addNode(e.n1);
        addNode(e.n2);
        // Add connections betwenn them
        nodes[e.n1]->connections.insert(e.n2);
        nodes[e.n2]->connections.insert(e.n1);
    }

    int visitNode(const std::string s)
    {
        int count = 0;
        if (s == ENDNODE)
        {
            return 1;
        }

        if (!nodes[s]->isUpper() && nodes[s]->visited)
        {
            return 0;
        }

        nodes[s]->visited = true;

        for (auto &n : nodes[s]->connections)
        {
            count += visitNode(n);
        }
        nodes[s]->visited = false;
        return count;
    }

    bool checkIfDoubleVisited()
    {
        for (auto &node : nodes)
        {
            if (!node.second->isUpper())
            {
                if (node.second->visited > 1)
                    return true;
            }
        }
        return false;
    }

    bool availableToVisit(const std::string s)
    {
        if (s == STARTNODE && nodes[s]->visited)
            return false;

        bool isLowerNode = (!nodes[s]->isUpper() && nodes[s]->visited);
        if (!nodes[s]->isUpper())
        {
            if (nodes[s]->visited == 0)
                return true;
            else if (nodes[s]->visited == 2)
                return false;
            else if (checkIfDoubleVisited())
                return false;
        }

        return true;
    }

    int visitNode2(const std::string s)
    {
        int count = 0;
        if (s == ENDNODE)
        {
            // printf("%s \n", ENDNODE);
            return 1;
        }

        if (!availableToVisit(s))
        {
            // printf("ERRROORRRRRRRR\n");
            return 0;
        }

        bool isSecondTime = (!nodes[s]->isUpper() && nodes[s]->visited);

        ++nodes[s]->visited;
        // printf("%s,", s.c_str());

        for (auto &n : nodes[s]->connections)
        {
            count += visitNode2(n);
        }
        --nodes[s]->visited;
        return count;
    }

    std::shared_ptr<Node> root;
    std::map<std::string, std::shared_ptr<Node>> nodes;
};

Graph buildGraph(const std::vector<Edge> edges)
{
    Graph g;
    std::for_each(edges.begin(), edges.end(), [&g](Edge e)
                  { g.addEdge(e); });
    return g;
}

void passagePathingPart1()
{
    std::string resourcePath = getResourcePath(2021, 12);
    std::vector<Edge> edges;
    readDocument<Edge>(resourcePath, edges);

    int countPaths = 0;
    Graph graph = buildGraph(edges);
    countPaths = graph.visitNode(STARTNODE);

    long long result = countPaths;
    printf("The solution for part 1 is: %i \n", result);
}

void passagePathingPart2()
{
    std::string resourcePath = getResourcePath(2021, 12);
    std::vector<Edge> edges;
    readDocument<Edge>(resourcePath, edges);

    int countPaths = 0;
    Graph graph = buildGraph(edges);
    countPaths = graph.visitNode2(STARTNODE);

    long long result = countPaths;
    printf("The solution for part 2 is: %lld \n", result);
}
