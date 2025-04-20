#include "std_includes.h"
#include "resources.h"
#include "utils_2022.h"
#include "grid.h"

long long getManhattanDistance(const CoordL &c1, const CoordL &c2)
{
    CoordL vector = CoordL(c2.first - c1.first, c2.second - c1.second);
    return std::abs(vector.first) + std::abs(vector.second);
}

// void fillLine( std::vector<int>& busyLine, )

struct Sensor
{
    Sensor(const std::string &s)
    {
        std::vector<std::string> values;
        std::string regExp = "Sensor at x=(-?\\d+), y=(-?\\d+): closest beacon is at x=(-?\\d+), y=(-?\\d+)";
        splitByRegex(s, regExp, values);
        position.first = std::stoi(values[1]);
        position.second = std::stoi(values[2]);
        beacon.first = std::stoi(values[3]);
        beacon.second = std::stoi(values[4]);
        distance = getManhattanDistance(position, beacon);
    }

    long long getDistance()
    {
        return getManhattanDistance(position, beacon);
    }

    CoordL position;
    CoordL beacon;
    long long distance;
};

void day15Part1()
{
    std::string resourcePath = getResourcePath(2022, 15);
    std::vector<Sensor> input;
    readDocument<Sensor>(resourcePath, input);

    long long int minX = std::numeric_limits<long long int>::max();
    long long int minY = std::numeric_limits<long long int>::max();
    long long int maxX = std::numeric_limits<long long int>::min();
    long long int maxY = std::numeric_limits<long long int>::min();
    for (auto &sensor : input)
    {
        long long distance = sensor.getDistance();
        minX = std::min(minX, sensor.position.first - distance);
        maxX = std::max(maxX, sensor.position.first + distance);
        minY = std::min(minY, sensor.position.second - distance);
        maxY = std::max(maxY, sensor.position.second + distance);
    }

    long long int sizeX = maxX - minX;
    const long long checkLine = 2000000;
    if (checkLine > maxY || checkLine < minY)
        return;

    std::vector<int> busyLine(sizeX + 1, 0);
    for (auto &sensor : input)
    {
        // long long distance = sensor.getDistance();
        CoordL auxC(sensor.position.first, checkLine);
        long long auxDistance = getManhattanDistance(sensor.position, auxC);
        if (auxDistance <= sensor.distance)
        {
            for (int i = 0; i <= sensor.distance - auxDistance; ++i)
            {
                // Busy from -2 to 24
                long long posR = (auxC.first + i) - minX;
                busyLine[posR] = 1;
                long long posL = (auxC.first - i) - minX;
                busyLine[posL] = 1;
            }
        }
    }
    for (auto &sensor : input)
    {
        if (sensor.position.second == checkLine)
        {
            long long pos = sensor.position.first - minX;
            busyLine[pos] = 0;
        }
        if (sensor.beacon.second == checkLine)
        {
            long long pos = sensor.beacon.first - minX;
            busyLine[pos] = 0;
        }
    }

    long long result = std::accumulate(busyLine.begin(), busyLine.end(), 0);
    printf("The solution for part 1 is: %lli \n", result);
}

void day15Part2()
{
    std::string resourcePath = getResourcePath(2022, 15);
    std::vector<Sensor> input;
    readDocument<Sensor>(resourcePath, input);

    long long int minX = 0;
    long long int minY = 0;
    long long int maxX = 4000000;
    long long int maxY = 4000000;

    long long x, y;

    /// Brute force algorithm
    // for ( int i = 0; i <= maxX; ++i )
    //{
    //   bool free = true;
    //   if ( i % 10000 == 0 ) std::cout << i << std::endl;
    //   for ( int j = 0; j <= maxY; ++j )
    //   {
    //     free = true;
    //     for ( auto& sensor : input )
    //     {
    //       CoordL c = CoordL( i, j );
    //       long long auxD = getManhattanDistance( c, sensor.position );
    //       if ( auxD <= sensor.distance )
    //       {
    //         free = false;
    //         break;
    //       }
    //     }
    //     if ( free )
    //     {
    //       x = i;
    //       y = j;
    //       break;
    //     }
    //   }
    //   if ( free ) break;
    // }

    long long sizeX = maxX - minX;
    long long sizeY = maxY - minY;
    for (int checkLine = 0; checkLine <= maxY; ++checkLine)
    {
        std::vector<CoordL> busyLine;
        for (auto &sensor : input)
        {
            long long distance = sensor.getDistance();
            CoordL auxC(sensor.position.first, checkLine);
            long long auxDistance = getManhattanDistance(sensor.position, auxC);
            if (auxDistance <= sensor.distance)
            {
                const int delta = distance - auxDistance;
                CoordL rang(sensor.position.first - delta, sensor.position.first + delta);
                busyLine.push_back(rang);
            }
        }
        std::sort(busyLine.begin(), busyLine.end());
        long long init = busyLine.front().first < minX ? minX : busyLine.front().first;
        long long end = busyLine.front().second < minX ? minX : busyLine.front().second;
        for (int i = 1; i < busyLine.size(); ++i)
        {
            if (busyLine[i].first <= end)
            {
                long long newMax = std::max(end, busyLine[i].second);
                end = newMax > maxX ? maxX : newMax;
            }
            else
                break;
        }
        if (init != 0)
            x = 0;
        if (end != maxX)
            x = end + 1;
        if (init != 0 || end != maxX)
        {
            y = checkLine;
            break;
        }
    }

    const long long baseFrequency = 4000000;
    long long result = (x * baseFrequency) + y;
    printf("The solution for part 2 is: %lli \n", result);
}
