using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using UnityEngine;
using UnityEngine.Rendering;
using static UnityEngine.Rendering.DebugUI.Table;

public class day13 : MonoBehaviour
{
    string path = "Assets/Resources/day13.txt";

    // Start is called before the first frame update
    void Start()
    {
        part1();
        part2();
    }

    bool CheckEqual( string a, string b, ref int tolerance)
    {
        int count = 0;
        for ( int i = 0; i < a.Length; i++ )
        {
            if (a[i] != b[i])
            {
                count++;
            }
            if (count > tolerance)
            {
                return false;
            }
        }
        tolerance -= count;
        return true;
    }

    long FindReflectionRow(List<List<char>> pattern, int tolerance)
    {
        int savedTolerance = tolerance;
        const int multiplier = 100;
        int height = pattern.Count;
        Stack<string> stack = new Stack<string>();
        for ( int i = 0; i < height; i++ )
        {
            tolerance = savedTolerance;
            string row = new string(pattern[i].ToArray());
            if (stack.Count > 0 && CheckEqual(row, stack.First(), ref tolerance))
            {
                tolerance = savedTolerance;
                Stack<string> auxStack = new Stack<string>(stack.Reverse());
                int j = i;
                bool validStack = true;
                while (auxStack.Count > 0 && j<height && tolerance >= 0)
                {
                    if (!CheckEqual(auxStack.Pop(), new string(pattern[j].ToArray()), ref tolerance))
                    {
                        validStack = false;
                        break;
                    }
                    j++;
                }
                if (validStack && tolerance == 0)
                {
                    return stack.Count * multiplier;
                }
            }
            stack.Push(row);
        }
        return 0;
    }

    long FindReflectionColumn(List<List<char>> pattern, int tolerance)
    {
        int savedTolerance = tolerance;
        int width = pattern[0].Count;
        int height = pattern.Count;
        Stack<string> stack = new Stack<string>();
        for ( int i = 0; i < width; i++ )
        {
            tolerance = savedTolerance;
            string column = "";
            for (int j = 0; j < height; j++)
            {
                column += pattern[j][i];
            }
            if (stack.Count > 0 && CheckEqual(column, stack.First(), ref tolerance))
            {
                tolerance = savedTolerance;
                Stack<string> auxStack = new Stack<string>(stack.Reverse());
                int j = i;
                bool validStack = true;
                while (auxStack.Count > 0 && j<width && tolerance >= 0)
                {
                    string auxColumn = "";
                    for (int k = 0; k < height; k++)
                    {
                        auxColumn += pattern[k][j];
                    }
                    if (!CheckEqual(auxStack.Pop(), auxColumn, ref tolerance))
                    {
                        validStack = false;
                        break;
                    }
                    j++;
                }
                if (validStack && tolerance == 0)
                {
                    return (long)stack.Count;
                }
            }
            stack.Push(column);
        }
        return 0;        
    }

    long FindReflection(List<List<char>> pattern, int tolerance = 0)
    {
        long resultRow = FindReflectionRow(pattern, tolerance);
        if (resultRow > 0)
        {
            return resultRow;
        }
        long resultColumn = FindReflectionColumn(pattern, tolerance);
        if (resultColumn > 0)
        {
            return resultColumn;
        }
        return 0;        
    }

    void part1()
    {
        StreamReader reader = File.OpenText(path);
        string line = null;
        long result = 0;
        List<List<char>> pattern = new List<List<char>>();
        while ((line = reader.ReadLine()) != null) 
        {
            if ( line.Length == 0 )
            {
                // check current 
                result += FindReflection(pattern);
                pattern.Clear();
            }
            else
            {
                List<char> row = new List<char>();
                line.ToList().ForEach(c => row.Add(c));
                pattern.Add(row);
            }
        }
        if (pattern.Count > 0)
        {
            result += FindReflection(pattern);
        }

        
        Debug.Log("Result: " + Convert.ToString(result));
    }

    void part2()
    {
        StreamReader reader = File.OpenText(path);
        string line = null;
        long result = 0;
        List<List<char>> pattern = new List<List<char>>();
        while ((line = reader.ReadLine()) != null) 
        {
            if ( line.Length == 0 )
            {
                // check current 
                result += FindReflection(pattern, 1);
                pattern.Clear();
            }
            else
            {
                List<char> row = new List<char>();
                line.ToList().ForEach(c => row.Add(c));
                pattern.Add(row);
            }
        }
        if (pattern.Count > 0)
        {
            result += FindReflection(pattern, 1);
        }

        
        Debug.Log("Result: " + Convert.ToString(result));
    }
    // 39281 too high

    
    // Update is called once per frame
    void Update()
    {
        
    }
}

