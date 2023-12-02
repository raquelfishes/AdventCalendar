using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;
using UnityEngine;
using System.Linq;

public class day01 : MonoBehaviour
{
    string path = "Assets/Resources/day01.txt";

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
        while ((line = reader.ReadLine()) != null) 
        {
            //Debug.Log(line);
            //string pattern = @"\b\d\b";
            MatchCollection matches = Regex.Matches(line, @"\d");
            if (matches.Count == 0)
            {
                Console.Error.WriteLine("No number found in line");
                return;
            }
            else
            {
                string firstNum = matches[0].Value;
                string lastNum = matches[matches.Count - 1].Value;

                string fullNum = firstNum + lastNum;
                //Debug.Log(fullNum);

                int num = Convert.ToInt32(fullNum);
                result += num;
            }
        }
        Debug.Log("Result: " + Convert.ToString(result));
    }

    void part2()
    {
        StreamReader reader = File.OpenText(path);
        string line = null;
        long result = 0;
        List<(string predicate, int numeral)> candidates = new List<(string, int)>();
        candidates.AddRange(new List<(string, int)> { ("1", 1), ("2", 2), ("3", 3), ("4", 4), ("5", 5), ("6", 6), ("7", 7), ("8", 8), ("9", 9) });
        candidates.AddRange(new List<(string, int)> { ("one", 1), ("two", 2), ("three", 3), ("four", 4), ("five", 5), ("six", 6), ("seven", 7), ("eight", 8), ("nine", 9) });
        while ((line = reader.ReadLine()) != null) 
        {
            int firstDigit = candidates.Select(candidate => new { Index = line.IndexOf(candidate.predicate), Value = candidate.numeral }).Where(x => x.Index >= 0).OrderBy(x => x.Index).First().Value;
            int lastDigit = candidates.Select(candidate => new { Index = line.LastIndexOf(candidate.predicate), Value = candidate.numeral }).Where(x => x.Index >= 0).OrderBy(x => x.Index).Last().Value;

            int num = firstDigit*10 + lastDigit;
            result += num;
        }
        Debug.Log("Result: " + Convert.ToString(result));
    }

    // Update is called once per frame
    void Update()
    {

    }
}
