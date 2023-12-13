using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using UnityEngine;
using UnityEngine.Rendering;
public class day10 : MonoBehaviour
{
    string path = "Assets/Resources/day10_test2.txt";

    // Start is called before the first frame update
    void Start()
    {
        //part1();
        part2();
    }

    public void myPrintGrid(Grid<char> grid)
    {
        string gridText = "";
        for (int i=0; i<grid.Height; i++)
        {
            for (int j=0; j<grid.Width; j++)
            {
                gridText += grid.GetValue(j,i);
            }
            gridText+= "\n";
        }
        UnityEngine.Debug.Log(gridText);
    }

    public void myPrintGrid(Grid<int> grid)
    {
        string gridText = "";
        for (int i=0; i<grid.Height; i++)
        {
            for (int j=0; j<grid.Width; j++)
            {
                gridText += Convert.ToString(grid.GetValue(j,i));
            }
            gridText+= "\n";
        }
        UnityEngine.Debug.Log(gridText);
    }

    void part1()
    {
        StreamReader reader = File.OpenText(path);
        string line = null;
        long result = 0;
        Vector2Int startPosition = new Vector2Int(0,0);
        Grid<char> grid = new Grid<char>();
        while ((line = reader.ReadLine()) != null) 
        {
            if (line.Length > 0)
            {
                if (grid.Width == 0)
                {
                    grid.SetWidth(line.Length);
                }
                grid.AddRow(line.ToCharArray());
                MatchCollection matchesStart = Regex.Matches(line, @"[S]");
                if ( matchesStart.Count > 0)
                {
                    // find position in line of first S
                    startPosition = new Vector2Int(matchesStart[0].Index, grid.Height-1);
                }
            }
        }

        grid.printGrid();

        Grid<int> distanceGrid = new Grid<int>(grid.Width, grid.Height, -1);
        distanceGrid.SetValue(startPosition.x, startPosition.y, 0);
        int maxDistance = 0;
        TraverseGrid(distanceGrid, grid, startPosition, ref maxDistance);
        distanceGrid.printGrid();
        result = maxDistance;

        Debug.Log("Result: " + Convert.ToString(result));
    }

    bool IsConnected(Vector2Int position, Vector2Int neighbour, Grid<char> grid)
    {
        Vector2Int direction = neighbour - position;
        if ( direction == -Vector2Int.up )
        {
            bool checkNeighbour = grid.GetValue(position) == '|' || grid.GetValue(position) == 'L' || grid.GetValue(position) == 'J' ;
            if (checkNeighbour || grid.GetValue(position) == 'S')
            {
                return grid.GetValue(neighbour) == '|' || grid.GetValue(neighbour) == 'F' || grid.GetValue(neighbour) == '7';
            }
        }
        if ( direction == -Vector2Int.down )
        {
            bool checkNeighbour = grid.GetValue(position) == '|' || grid.GetValue(position) == 'F' || grid.GetValue(position) == '7';
            if (checkNeighbour || grid.GetValue(position) == 'S')
            {
                return grid.GetValue(neighbour) == '|' || grid.GetValue(neighbour) == 'L' || grid.GetValue(neighbour) == 'J';
            }
        }
        if ( direction == Vector2Int.right )
        {
            bool checkNeighbour = grid.GetValue(position) == '-' || grid.GetValue(position) == 'L' || grid.GetValue(position) == 'F';
            if (checkNeighbour || grid.GetValue(position) == 'S')
            {
                return grid.GetValue(neighbour) == '-' || grid.GetValue(neighbour) == '7' || grid.GetValue(neighbour) == 'J';
            }
        }
        if ( direction == Vector2Int.left )
        {
            bool checkNeighbour = grid.GetValue(position) == '-' || grid.GetValue(position) == 'J' || grid.GetValue(position) == '7';
            if (checkNeighbour || grid.GetValue(position) == 'S')
            {
                return grid.GetValue(neighbour) == '-' || grid.GetValue(neighbour) == 'F' || grid.GetValue(neighbour) == 'L';
            }
        }

        return false;
    }

    void AddNeighboursToVisit(Vector2Int position, Grid<char> grid, Grid<int> distanceGrid, ref Queue<Tuple<Vector2Int, List<Vector2Int>>> nextNeighboursToVisit)
    {
        List<Vector2Int> neighbours = new List<Vector2Int>();
        neighbours.Add(new Vector2Int(position.x, position.y+1)); 
        neighbours.Add(new Vector2Int(position.x, position.y-1)); 
        neighbours.Add(new Vector2Int(position.x+1, position.y)); 
        neighbours.Add(new Vector2Int(position.x-1, position.y)); 
        Tuple<Vector2Int, List<Vector2Int>> neighboursToVisit = new Tuple<Vector2Int, List<Vector2Int>>(position, new List<Vector2Int>());
        foreach(Vector2Int neighbour in neighbours)
        {
            if (grid.IsValidCoord(neighbour) && distanceGrid.GetValue(neighbour) == -1)
            {
                neighboursToVisit.Item2.Add(neighbour);
            }
        }
        nextNeighboursToVisit.Enqueue(neighboursToVisit);
    }

    void TraverseGrid(Grid<int> distanceGrid, Grid<char> grid, Vector2Int initialosition, ref int maxDistance)
    {
        Queue<Tuple<Vector2Int, List<Vector2Int>>> nextNeighboursToVisit = new Queue<Tuple<Vector2Int, List<Vector2Int>>>();
        AddNeighboursToVisit(initialosition, grid, distanceGrid, ref nextNeighboursToVisit);

        while( nextNeighboursToVisit.Count > 0 )
        {
            Tuple<Vector2Int, List<Vector2Int>> nextNeighbourToVisit = nextNeighboursToVisit.Dequeue();
            Vector2Int position = nextNeighbourToVisit.Item1;
            foreach(Vector2Int neighbour in nextNeighbourToVisit.Item2)
            {
                if (IsConnected(position, neighbour, grid))
                {
                    int newDistance = distanceGrid.GetValue(position) + 1;
                    distanceGrid.SetValue(neighbour, newDistance);
                    maxDistance = Mathf.Max(maxDistance, newDistance);
                    AddNeighboursToVisit(neighbour, grid, distanceGrid, ref nextNeighboursToVisit);
                }
            }
        }
    }
    
    void part2()
    {
       StreamReader reader = File.OpenText(path);
        string line = null;
        long result = 0;
        Vector2Int startPosition = new Vector2Int(0,0);
        Grid<char> grid = new Grid<char>();
        while ((line = reader.ReadLine()) != null) 
        {
            if (line.Length > 0)
            {
                if (grid.Width == 0)
                {
                    grid.SetWidth(line.Length);
                }
                grid.AddRow(line.ToCharArray());
                MatchCollection matchesStart = Regex.Matches(line, @"[S]");
                if ( matchesStart.Count > 0)
                {
                    // find position in line of first S
                    startPosition = new Vector2Int(matchesStart[0].Index, grid.Height-1);
                }
            }
        }
        
        Grid<int> distanceGrid = new Grid<int>(grid.Width, grid.Height, -1);
        distanceGrid.SetValue(startPosition.x, startPosition.y, 0);
        int maxDistance = 0;
        TraverseGrid(distanceGrid, grid, startPosition, ref maxDistance);
        distanceGrid.printGrid();

        // Convert S for her char symbol
        {
            if ( ( distanceGrid.IsValidCoord(startPosition.x-1, startPosition.y) && 
                   distanceGrid.IsValidCoord(startPosition.x+1, startPosition.y) ) && 
                 ( distanceGrid.GetValue(new Vector2Int(startPosition.x-1, startPosition.y) ) != -1 &&
                   distanceGrid.GetValue(new Vector2Int(startPosition.x+1, startPosition.y) ) != -1 ) )
            {
                grid.SetValue(startPosition, '-');
            }
            if ( ( distanceGrid.IsValidCoord(startPosition.x, startPosition.y-1) && 
                   distanceGrid.IsValidCoord(startPosition.x, startPosition.y+1) ) && 
                 ( distanceGrid.GetValue(new Vector2Int(startPosition.x, startPosition.y-1) ) != -1 &&
                   distanceGrid.GetValue(new Vector2Int(startPosition.x, startPosition.y+1) ) != -1 ) )
            {
                grid.SetValue(startPosition, '|');
            }
            if ( ( distanceGrid.IsValidCoord(startPosition.x-1, startPosition.y) && 
                   distanceGrid.IsValidCoord(startPosition.x, startPosition.y+1) ) && 
                 ( distanceGrid.GetValue(new Vector2Int(startPosition.x-1, startPosition.y) ) != -1 &&
                   distanceGrid.GetValue(new Vector2Int(startPosition.x, startPosition.y+1) ) != -1 ) )
            {
                grid.SetValue(startPosition, '7');
            }
            if ( ( distanceGrid.IsValidCoord(startPosition.x-1, startPosition.y) && 
                   distanceGrid.IsValidCoord(startPosition.x, startPosition.y-1) ) && 
                 ( distanceGrid.GetValue(new Vector2Int(startPosition.x-1, startPosition.y) ) != -1 &&
                   distanceGrid.GetValue(new Vector2Int(startPosition.x, startPosition.y-1) ) != -1 ) )
            {
                grid.SetValue(startPosition, 'J');
            }
            if ( ( distanceGrid.IsValidCoord(startPosition.x+1, startPosition.y) && 
                   distanceGrid.IsValidCoord(startPosition.x, startPosition.y+1) ) && 
                 ( distanceGrid.GetValue(new Vector2Int(startPosition.x+1, startPosition.y) ) != -1 &&
                   distanceGrid.GetValue(new Vector2Int(startPosition.x, startPosition.y+1) ) != -1 ) )
            {
                grid.SetValue(startPosition, 'F');
            }
            if ( ( distanceGrid.IsValidCoord(startPosition.x+1, startPosition.y) && 
                   distanceGrid.IsValidCoord(startPosition.x, startPosition.y-1) ) && 
                 ( distanceGrid.GetValue(new Vector2Int(startPosition.x+1, startPosition.y) ) != -1 &&
                   distanceGrid.GetValue(new Vector2Int(startPosition.x, startPosition.y-1) ) != -1 ) )
            {
                grid.SetValue(startPosition, 'L');
            }
        }

        grid.printGrid();

        // Create a colorGrid with 1 for all the points in the loop
        // 0 for initialize all the points
        // 1 for all the points in the loop
        // 1 will be outside the loop

        // Add an extra ring of . around the grid
        Grid<char> grid2 = new Grid<char>(grid.Width+2, grid.Height+2, '.');
        for(int i=0; i<grid.Width; ++i)
        {
            for(int j=0; j<grid.Height; ++j)
            {
                grid2.SetValue(i+1,j+1, grid.GetValue(i,j));
            }
        }

        Grid<int> colorGrid = new Grid<int>(grid.Width+2, grid.Height+2, -1);
        for(int i=0; i<grid.Width; ++i)
        {
            for(int j=0; j<grid.Height; ++j)
            {
                if (distanceGrid.GetValue(i,j) != -1)
                {
                    colorGrid.SetValue(i+1,j+1, 1);
                }
            }
        }

        Debug.Log("Initial colorGrid");
        colorGrid.printGrid();
        colorGrid.SetValue(Vector2Int.zero, 0);

        // Initial position from the borders
        FloodGrid(colorGrid, grid2, Vector2Int.zero);

        // Sum all the negative values in the colorGrid
        result = colorGrid.gridArray.Sum(x => x < 0 ? 1 : 0);

        Debug.Log("Result: " + Convert.ToString(result));
    }

    void AddNeighboursToVisit2(Vector2Int position, Grid<char> grid, Grid<int> colorGrid, ref Queue<Tuple<Vector2Int, List<Vector2Int>>> nextNeighboursToVisit)
    {
        List<Vector2Int> neighbours = new List<Vector2Int>();
        neighbours.Add(new Vector2Int(position.x, position.y+1)); 
        neighbours.Add(new Vector2Int(position.x, position.y-1)); 
        neighbours.Add(new Vector2Int(position.x+1, position.y)); 
        neighbours.Add(new Vector2Int(position.x-1, position.y)); 
        Tuple<Vector2Int, List<Vector2Int>> neighboursToVisit = new Tuple<Vector2Int, List<Vector2Int>>(position, new List<Vector2Int>());
        foreach(Vector2Int neighbour in neighbours)
        {
            if ( grid.IsValidCoord(neighbour) )
            {
                if ( colorGrid.GetValue(neighbour) == -1 || ( colorGrid.GetValue(neighbour) == 1 && CanPassColor(position, neighbour, grid) ) )
                    neighboursToVisit.Item2.Add(neighbour);
            }
        }
        nextNeighboursToVisit.Enqueue(neighboursToVisit);
    }

    bool CanPassColor(Vector2Int position, Vector2Int neighbour, Grid<char> grid)
    {
        Vector2Int direction = neighbour - position;
        if ( direction == -Vector2Int.up || direction == -Vector2Int.down )
        {
            return grid.GetValue(position) != '-';
        }
        if ( direction == Vector2Int.right || direction == Vector2Int.left )
        {
            return grid.GetValue(position) != '|';
        }

        return false;
    }

    void FloodGrid(Grid<int> colorGrid, Grid<char> grid, Vector2Int startPosition)
    {
        Queue<Tuple<Vector2Int, List<Vector2Int>>> nextNeighboursToVisit = new Queue<Tuple<Vector2Int, List<Vector2Int>>>();
        AddNeighboursToVisit(startPosition, grid, colorGrid, ref nextNeighboursToVisit);

        // Color grid = 1 for all points
        while( nextNeighboursToVisit.Count > 0 )
        {
            Tuple<Vector2Int, List<Vector2Int>> nextNeighbourToVisit = nextNeighboursToVisit.Dequeue();
            Vector2Int position = nextNeighbourToVisit.Item1;
            foreach(Vector2Int neighbour in nextNeighbourToVisit.Item2)
            {
                if ( colorGrid.GetValue(neighbour) == -1 )
                {
                    colorGrid.SetValue(neighbour, 0);
                    AddNeighboursToVisit2(neighbour, grid, colorGrid, ref nextNeighboursToVisit);
                    continue;
                }
                if ( colorGrid.GetValue(neighbour) == 1 && CanPassColor(position, neighbour, grid) )
                {
                    colorGrid.SetValue(neighbour, 2);
                    AddNeighboursToVisit2(neighbour, grid, colorGrid, ref nextNeighboursToVisit);
                    continue;
                }
            }
            colorGrid.printGrid();
        }
    }

    
    // Update is called once per frame
    void Update()
    {
        
    }
}

