using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using UnityEngine;
using UnityEngine.Rendering;
using static UnityEngine.Rendering.DebugUI.Table;

public class day15 : MonoBehaviour
{
    string path = "Assets/Resources/day15.txt";

    // Start is called before the first frame update
    void Start()
    {
        part1();
        part2();
    }

    void part1()
    {
        StreamReader reader = File.OpenText(path);
        string line = reader.ReadLine();
        List<string> steps = line.Split(',').ToList();
        long result = 0;
        foreach (string step in steps)
        {
            result += ComputeHash(step);
        }

        Debug.Log("Result: " + Convert.ToString(result));
    }

    int ComputeHash(string step)
    {
        int hash = 0;
        foreach (char c in step)
        {
            hash += (int)c;
            hash *= 17;
            hash %= 256;
        }
        return hash;
    }

    void part2()
    {
        StreamReader reader = File.OpenText(path);
        string line = reader.ReadLine();
        List<string> steps = line.Split(',').ToList();
        long result = 0;
        List<Tuple<string,int>>[] boxes = new List<Tuple<string,int>>[256];
        foreach (string step in steps)
        {
            MatchCollection matches = Regex.Matches(step, @"(\w+)(\=|\-)(\d+)?");
            if ( matches.Count > 0 )
            {
                int hash = ComputeHash(matches[0].Groups[1].Value);
                if (matches[0].Groups[2].Value == "-")
                {
                    if (boxes[hash] != null && boxes[hash].Any(m => m.Item1 == matches[0].Groups[1].Value))
                    {
                        boxes[hash].RemoveAll(m => m.Item1 == matches[0].Groups[1].Value);
                    }
                }
                else
                {
                    Tuple<string,int> lens = new Tuple<string,int>(matches[0].Groups[1].Value, Convert.ToInt32(matches[0].Groups[3].Value));
                    if (boxes[hash] == null)
                    {
                        boxes[hash] = new List<Tuple<string,int>>();
                    }
                    if (!boxes[hash].Any(m => m.Item1 ==lens.Item1))
                    {
                        boxes[hash].Add(lens);
                    }
                    else
                    {
                        int index = boxes[hash].IndexOf(boxes[hash].First(m => m.Item1 == lens.Item1));
                        boxes[hash][index] = lens;
                    }
                }
            }
        }

        result = ComputeFocusingPower(boxes);

        Debug.Log("Result: " + Convert.ToString(result));
    }

    long ComputeFocusingPower(List<Tuple<string,int>>[] boxes)
    {
        long result = 0;
        for (int i = 0; i < boxes.Length; i++)
        {
            if (boxes[i] != null && boxes[i].Count > 0)
            {
                for (int j=0; j < boxes[i].Count; j++)
                {
                    result += (i+1) * (j+1) * boxes[i][j].Item2;
                }
            }
        }
        return result;
    }
    
    // Update is called once per frame
    void Update()
    {
        
    }
}


