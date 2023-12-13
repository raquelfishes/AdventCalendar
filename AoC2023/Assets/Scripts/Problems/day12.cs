using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using UnityEngine;
using UnityEngine.Rendering;
public class day12 : MonoBehaviour
{
    string path = "Assets/Resources/day12_test.txt";

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
        while ((line = reader.ReadLine()) != null) 
        {
            MatchCollection matches = Regex.Matches(line, @"([\.\?#]+)\s+(\d+)");
            if ( matches.Count > 0)
            {

            }
        }
        
        Debug.Log("Result: " + Convert.ToString(result));
    }

    void part2()
    {
    }

    
    // Update is called once per frame
    void Update()
    {
        
    }
}

