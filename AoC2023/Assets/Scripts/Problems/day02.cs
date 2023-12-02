using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;
using Unity.Mathematics;
using UnityEngine;

public class day02 : MonoBehaviour
{
    string path = "Assets/Resources/day02.txt";
    const int MAX_GREEN=13;
    const int MAX_BLUE=14;
    const int MAX_RED=12;

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
            Debug.Log(line);
            string[] gameInfo = line.Split(':');
            if (gameInfo.Length == 0)
            {
                Console.Error.WriteLine("No number found in line");
                return;
            }

            MatchCollection matches2 = Regex.Matches(gameInfo[gameInfo.Length - 1], @"\b(\d+ \w+)");
            if (matches2.Count == 0)
            {
                Console.Error.WriteLine("No valid game");
                return;
            }
            bool valid = true;
            foreach (Match match in matches2)
            {
                Debug.Log(match.Value);
                string[] ballInfo = match.Value.Split(' ');
                switch (ballInfo[1])
                {
                    case "green":
                        if (Convert.ToInt32(ballInfo[0]) > MAX_GREEN)
                        {
                            valid = false;
                        }
                        break;
                    case "blue":
                        if (Convert.ToInt32(ballInfo[0]) > MAX_BLUE)
                        {
                            valid = false;
                        }
                        break;
                    case "red":
                        if (Convert.ToInt32(ballInfo[0]) > MAX_RED)
                        {
                            valid = false;
                        }
                        break;
                    default:
                        Console.Error.WriteLine("No valid color");
                        return;
                }
                if (!valid)
                {
                    Console.Error.WriteLine("Invalid game");
                    break;
                }
            }
            if (valid)
            {
                MatchCollection matches = Regex.Matches(gameInfo[0], @"(\d+)");               
                result+=Convert.ToInt32(matches[0].Value);
            }
        }
        Debug.Log("Result: " + Convert.ToString(result));
    }

    void part2()
    {
        StreamReader reader = File.OpenText(path);
        string line = null;
        long result = 0;
        while ((line = reader.ReadLine()) != null) 
        {
            //Debug.Log(line);
            string[] gameInfo = line.Split(':');
            if (gameInfo.Length == 0)
            {
                Console.Error.WriteLine("No number found in line");
                return;
            }

            MatchCollection matches2 = Regex.Matches(gameInfo[gameInfo.Length - 1], @"\b(\d+ \w+)");
            if (matches2.Count == 0)
            {
                Console.Error.WriteLine("No valid game");
                return;
            }

            int temp_min_green = 0;
            int temp_min_blue = 0;
            int temp_min_red = 0;
            int temp_result = 1;
            foreach (Match match in matches2)
            {
                string[] ballInfo = match.Value.Split(' ');
                int tempBallCount = Convert.ToInt32(ballInfo[0]);
                switch (ballInfo[1])
                {
                    case "green":
                        if ( tempBallCount > temp_min_green)
                        {
                            temp_min_green = tempBallCount;
                        }
                        break;
                    case "blue":
                        if ( tempBallCount > temp_min_blue)
                        {
                            temp_min_blue = tempBallCount;
                        }
                        break;
                    case "red":
                        if (tempBallCount > temp_min_red)
                        {
                            temp_min_red = tempBallCount;
                        }
                        break;
                    default:
                        Console.Error.WriteLine("No valid color");
                        return;
                }
                
                temp_result = temp_min_green * temp_min_blue * temp_min_red;
            }
            result+=temp_result;
        }
        Debug.Log("Result: " + Convert.ToString(result));
    }


    // Update is called once per frame
    void Update()
    {
        
    }
}
