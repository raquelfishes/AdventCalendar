using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using UnityEngine;
using UnityEngine.Rendering;
using static UnityEngine.Rendering.DebugUI.Table;

public class day14 : MonoBehaviour
{
    string path = "Assets/Resources/day14.txt";

    // Start is called before the first frame update
    void Start()
    {
        part1();
        part2();
    }

    void part1()
    {
        StreamReader reader = File.OpenText(path);
        string line = null;
        long result = 0;
        Grid<char> grid = new Grid<char>();
        while ((line = reader.ReadLine()) != null) 
        {
            List<char> row = new List<char>();
            line.ToList().ForEach(c => row.Add(c));
            grid.AddRow(row.ToArray());
        }
        //grid.printGrid();
        RollStonesNorth(grid, -Vector2Int.up);
        //grid.printGrid();
        result = ComputeLoad(grid);
        
        Debug.Log("Result: " + Convert.ToString(result));
    }

    void RollStonesNorth(Grid<char> grid, Vector2Int direction)
    {
        for (int i = 0; i < grid.Height; i++)
        {
            for (int j = 0; j < grid.Width; j++)
            {
                if (grid[j,i] == 'O')
                {
                    int y = i;
                    int x = j;
                    while (grid.IsValidCoord(x+direction.x,y+direction.y) && grid[x+direction.x, y+direction.y] == '.')
                    {
                        grid[x+direction.x, y+direction.y] = 'O';
                        grid[x, y] = '.';
                        x += direction.x;
                        y += direction.y;
                    }
                }
            }
        }
    }

    void RollStonesSouth(Grid<char> grid, Vector2Int direction)
    {
        for (int i = grid.Height-1; i >= 0; i--)
        {
            for (int j = 0; j < grid.Width; j++)
            {
                if (grid[j,i] == 'O')
                {
                    int y = i;
                    int x = j;
                    while (grid.IsValidCoord(x+direction.x,y+direction.y) && grid[x+direction.x, y+direction.y] == '.')
                    {
                        grid[x+direction.x, y+direction.y] = 'O';
                        grid[x, y] = '.';
                        x += direction.x;
                        y += direction.y;
                    }
                }
            }
        }
    }

    void RollStonesWest(Grid<char> grid, Vector2Int direction)
    {
        for (int i = 0; i < grid.Height; i++)
        {
            for (int j = 0; j < grid.Width; j++)
            {
                if (grid[j,i] == 'O')
                {
                    int y = i;
                    int x = j;
                    while (grid.IsValidCoord(x+direction.x,y+direction.y) && grid[x+direction.x, y+direction.y] == '.')
                    {
                        grid[x+direction.x, y+direction.y] = 'O';
                        grid[x, y] = '.';
                        x += direction.x;
                        y += direction.y;
                    }
                }
            }
        }
    }

    void RollStonesEast(Grid<char> grid, Vector2Int direction)
    {
        for (int i = 0; i < grid.Height; i++)
        {
            for (int j = grid.Width-1; j >= 0; j--)
            {
                if (grid[j,i] == 'O')
                {
                    int y = i;
                    int x = j;
                    while (grid.IsValidCoord(x+direction.x,y+direction.y) && grid[x+direction.x, y+direction.y] == '.')
                    {
                        grid[x+direction.x, y+direction.y] = 'O';
                        grid[x, y] = '.';
                        x += direction.x;
                        y += direction.y;
                    }
                }
            }
        }
    }

    void RollStonesCycle(Grid<char> grid)
    {
        //grid.printGrid();
        RollStonesNorth(grid, -Vector2Int.up);
        //grid.printGrid();
        RollStonesWest(grid, Vector2Int.left);
        //grid.printGrid();
        RollStonesSouth(grid, -Vector2Int.down);
        //grid.printGrid();
        RollStonesEast(grid, Vector2Int.right);
        //grid.printGrid();
    }

    long ComputeLoad(Grid<char> grid)
    {
        long result = 0;
        for (int i = 0; i < grid.Height; i++)
        {
            for (int j = 0; j < grid.Width; j++)
            {
                if (grid[j, i] == 'O')
                {
                    result += grid.Height - i;
                }
            }
        }
        return result;
    }

    void FindFirstRepeat(Grid<char> grid, long iterationsCount, out int cycleLength)
    {
        //grid.printGrid();
        // Find first repeated state
        HashSet<string> seen = new HashSet<string>();
        int count = 0;
        do
        {
            //if (count < 4)
            //{
            //    next.printGrid();
            //}
            //next.printGrid();
            seen.Add(grid.ToString());
            RollStonesCycle(grid);
            //next.printGrid();
            count++;
        }
        while (!seen.Contains(grid.ToString()) && count < iterationsCount);
        cycleLength = count;
    }

    void part2()
    {
        StreamReader reader = File.OpenText(path);
        string line = null;
        long result = 0;
        Grid<char> grid = new Grid<char>();
        while ((line = reader.ReadLine()) != null) 
        {
            List<char> row = new List<char>();
            line.ToList().ForEach(c => row.Add(c));
            grid.AddRow(row.ToArray());
        }
        //grid.printGrid();
        long iterationsCount = 1000000000;
        //long iterationsCount = 10;

        // Find first repeated state
        int preamble = 0;
        Grid<char> firstRepeat;
        FindFirstRepeat(grid, iterationsCount, out preamble);
        firstRepeat = new Grid<char>(grid);
        int cycleLenght = 0;            
        Grid<char> cycleGrid;
        FindFirstRepeat(grid, iterationsCount, out cycleLenght);
        cycleGrid = new Grid<char>(grid);
        if ( firstRepeat != cycleGrid)
        {
            Debug.Log("First repeat is not the same as the grid");
        }

        int stepsToComputePastCycle = (int)((iterationsCount - preamble) % cycleLenght);
        for (int i = 0; i < stepsToComputePastCycle; i++)
        {
            RollStonesCycle(cycleGrid);
        }

        result = ComputeLoad(cycleGrid);
        
        Debug.Log("Result: " + Convert.ToString(result));
    }
    //33183 too low
    
    // Update is called once per frame
    void Update()
    {
        
    }
}


