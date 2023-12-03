using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;
using Unity.Mathematics;
using UnityEngine;

public class day03 : MonoBehaviour
{
    string path = "Assets/Resources/day03.txt";

    // Start is called before the first frame update
    void Start()
    {
        //part1();
        part2();
    }

    void part1()
    {
        StreamReader reader = File.OpenText(path);
        string line = null;
        long result = 0;
        int x = 0;
        Grid<char> grid = new Grid<char>();
        while ((line = reader.ReadLine()) != null) 
        {
            grid.SetWidth(line.Length);
            for (int y = 0; y < line.Length; y++)
            {
                grid.AddValue(line[y]);
            }
            x++;
        }

        grid.setHeight(x);

        //grid.printGrid();

        for (int i = 0; i < grid.gridArray.Count; i++)
        {
            if (grid.gridArray[i] != '.' && !char.IsDigit(grid.gridArray[i]))
            {
                int cur_x,cur_y;
                grid.GetCoord(i, out cur_x, out cur_y);
                if (grid.IsValidCoord(cur_x-1, cur_y-1) && char.IsDigit(grid.GetValue(cur_x-1, cur_y-1)))
                {
                    //check top left and extract number
                    int number = getFullNumber(cur_x-1, cur_y-1, ref grid);
                    result += number;
                }
                if (grid.IsValidCoord(cur_x-1, cur_y) && char.IsDigit(grid.GetValue(cur_x-1, cur_y)))
                {
                    //check top and extract number
                    int number = getFullNumber(cur_x-1, cur_y, ref grid);
                    result += number;
                }
                if (grid.IsValidCoord(cur_x-1, cur_y+1) && char.IsDigit(grid.GetValue(cur_x-1, cur_y+1)))
                {
                    //check top right and extract number
                    int number = getFullNumber(cur_x-1, cur_y+1, ref grid);
                    result += number;
                }
                if (grid.IsValidCoord(cur_x, cur_y-1) && char.IsDigit(grid.GetValue(cur_x, cur_y-1)))
                {
                    //check left and extract number
                    int number = getFullNumber(cur_x, cur_y-1, ref grid);
                    result += number;
                }
                if (grid.IsValidCoord(cur_x, cur_y+1) && char.IsDigit(grid.GetValue(cur_x, cur_y+1)))
                {
                    //check right and extract number
                    int number = getFullNumber(cur_x, cur_y+1, ref grid);
                    result += number;
                }
                if (grid.IsValidCoord(cur_x+1, cur_y-1) && char.IsDigit(grid.GetValue(cur_x+1, cur_y-1)))
                {
                    //check bottom left and extract number
                    int number = getFullNumber(cur_x+1, cur_y-1, ref grid);
                    result += number;
                }
                if (grid.IsValidCoord(cur_x+1, cur_y) && char.IsDigit(grid.GetValue(cur_x+1, cur_y)))
                {
                    //check bottom and extract number
                    int number = getFullNumber(cur_x+1, cur_y, ref grid);
                    result += number;
                }
                if (grid.IsValidCoord(cur_x+1, cur_y+1) && char.IsDigit(grid.GetValue(cur_x+1, cur_y+1)))
                {
                    //check bottom right and extract number
                    int number = getFullNumber(cur_x+1, cur_y+1, ref grid);
                    result += number;
                }
            }
        }

        Debug.Log("Result: " + Convert.ToString(result));
    }

    int getFullNumber(int x, int y, ref Grid<char> grid)
    {
        while(grid.IsValidCoord(x,y) && char.IsDigit(grid.GetValue(x,y)))
        {
            y--;
        }
        if (!grid.IsValidCoord(x,y) || !char.IsDigit(grid.GetValue(x,y)))
                   {
            y++;
        }
        int result = 0;
        while(grid.IsValidCoord(x,y) && char.IsDigit(grid.GetValue(x, y)))
        {
            result = result*10 + (int)(grid.GetValue(x,y)-'0');
            grid.SetValue(x,y,'.');
            y++;
        }

        //Debug.Log(result);
        //grid.printGrid();

        return result;
    }

    void part2()
    {
        StreamReader reader = File.OpenText(path);
        string line = null;
        long result = 0;
        int x = 0;
        Grid<char> grid = new Grid<char>();
        while ((line = reader.ReadLine()) != null) 
        {
            grid.SetWidth(line.Length);
            for (int y = 0; y < line.Length; y++)
            {
                grid.AddValue(line[y]);
            }
            x++;
        }

        grid.setHeight(x);

        //grid.printGrid();

        for (int i = 0; i < grid.gridArray.Count; i++)
        {
            if (grid.gridArray[i] == '*' )
            {
                int cur_x,cur_y;
                grid.GetCoord(i, out cur_x, out cur_y);
                int temp_result = 1;
                int count_found = 0;
                if (grid.IsValidCoord(cur_x-1, cur_y-1) && char.IsDigit(grid.GetValue(cur_x-1, cur_y-1)))
                {
                    //check top left and extract number
                    int number = getFullNumber(cur_x-1, cur_y-1, ref grid);
                    temp_result *= number;
                    count_found++;
                }
                if (grid.IsValidCoord(cur_x-1, cur_y) && char.IsDigit(grid.GetValue(cur_x-1, cur_y)))
                {
                    //check top and extract number
                    int number = getFullNumber(cur_x-1, cur_y, ref grid);
                    temp_result *= number;
                    count_found++;
                }
                if (grid.IsValidCoord(cur_x-1, cur_y+1) && char.IsDigit(grid.GetValue(cur_x-1, cur_y+1)))
                {
                    //check top right and extract number
                    int number = getFullNumber(cur_x-1, cur_y+1, ref grid);
                    temp_result *= number;
                    count_found++;
                }
                if (grid.IsValidCoord(cur_x, cur_y-1) && char.IsDigit(grid.GetValue(cur_x, cur_y-1)))
                {
                    //check left and extract number
                    int number = getFullNumber(cur_x, cur_y-1, ref grid);
                    temp_result *= number;
                    count_found++;
                }
                if (grid.IsValidCoord(cur_x, cur_y+1) && char.IsDigit(grid.GetValue(cur_x, cur_y+1)))
                {
                    //check right and extract number
                    int number = getFullNumber(cur_x, cur_y+1, ref grid);
                    temp_result *= number;
                    count_found++;
                }
                if (grid.IsValidCoord(cur_x+1, cur_y-1) && char.IsDigit(grid.GetValue(cur_x+1, cur_y-1)))
                {
                    //check bottom left and extract number
                    int number = getFullNumber(cur_x+1, cur_y-1, ref grid);
                    temp_result *= number;
                    count_found++;
                }
                if (grid.IsValidCoord(cur_x+1, cur_y) && char.IsDigit(grid.GetValue(cur_x+1, cur_y)))
                {
                    //check bottom and extract number
                    int number = getFullNumber(cur_x+1, cur_y, ref grid);
                    temp_result *= number;
                    count_found++;
                }
                if (grid.IsValidCoord(cur_x+1, cur_y+1) && char.IsDigit(grid.GetValue(cur_x+1, cur_y+1)))
                {
                    //check bottom right and extract number
                    int number = getFullNumber(cur_x+1, cur_y+1, ref grid);
                    temp_result *= number;
                    count_found++;
                }
                if (count_found == 2)
                {
                    result += temp_result;
                }
            }
        }

        Debug.Log("Result: " + Convert.ToString(result));
    }


    // Update is called once per frame
    void Update()
    {
        
    }
}
