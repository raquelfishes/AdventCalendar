using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using UnityEngine;
using UnityEngine.Rendering;
public class day08 : MonoBehaviour
{
    string path = "Assets/Resources/day08.txt";

    class Node
    {
        public string origin;
        public string[] destination;
    }

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
        Dictionary<string, Node> nodeMap = new Dictionary<string, Node>();
        List<int> instructionList = new List<int>();

        while ((line = reader.ReadLine()) != null) 
        {
            MatchCollection matchesInstructions = Regex.Matches(line, @"^[LR]+$");
            if ( matchesInstructions.Count > 0)
            {
                foreach(char c in matchesInstructions[0].Value)
                {
                    if ( c == 'L' )
                        instructionList.Add(0);
                    else if ( c == 'R' )
                        instructionList.Add(1);
                }
                continue;   
            }
            MatchCollection matchesMap = Regex.Matches(line, @"(\w+)\s+\=\s+\((\w+),\s(\w+)\)");
            if ( matchesMap.Count > 0)
            {
                Node node = new Node();
                node.origin = matchesMap[0].Groups[1].Value;
                node.destination = new string[2];
                node.destination[0] = matchesMap[0].Groups[2].Value;
                node.destination[1] = matchesMap[0].Groups[3].Value;
                nodeMap.Add(node.origin, node);
                continue;   
            }
        }

        long result = FindDestiny("AAA", nodeMap, 0, instructionList );
        Debug.Log("Result: " + Convert.ToString(result));
    }

    long FindDestiny(string origin, Dictionary<string, Node> nodeMap, int index, List<int> instructionList)
    {
        long result = 0;
        while( origin != "ZZZ" )
        {
            Node node = nodeMap[origin];
            if (index == instructionList.Count)
                index = 0;
            int indexInstruction = instructionList[index];
            origin = node.destination[indexInstruction];
            index++;
            result++;
        }
        return result;
    }


    void part2()
    {
        StreamReader reader = File.OpenText(path);
        string line = null;
        Dictionary<string, Node> nodeMap = new Dictionary<string, Node>();
        List<int> instructionList = new List<int>();

        while ((line = reader.ReadLine()) != null) 
        {
            MatchCollection matchesInstructions = Regex.Matches(line, @"^[LR]+$");
            if ( matchesInstructions.Count > 0)
            {
                foreach(char c in matchesInstructions[0].Value)
                {
                    if ( c == 'L' )
                        instructionList.Add(0);
                    else if ( c == 'R' )
                        instructionList.Add(1);
                }
                continue;   
            }
            MatchCollection matchesMap = Regex.Matches(line, @"(\w+)\s+\=\s+\((\w+),\s(\w+)\)");
            if ( matchesMap.Count > 0)
            {
                Node node = new Node();
                node.origin = matchesMap[0].Groups[1].Value;
                node.destination = new string[2];
                node.destination[0] = matchesMap[0].Groups[2].Value;
                node.destination[1] = matchesMap[0].Groups[3].Value;
                nodeMap.Add(node.origin, node);
                continue;   
            }
        }

        long result = 0;
        foreach(KeyValuePair<string, Node> entry in nodeMap)
        {
            if ( entry.Value.origin[2] == 'A' )
            {
                long tempResult = FindDestiny2(entry.Value.origin, nodeMap, 0, instructionList );
                if ( result != 0)
                    result = MyLCM(result, tempResult);
                else
                    result = tempResult;
            }
        }
        Debug.Log("Result: " + Convert.ToString(result));
    }

    long MyLCM(long a, long b)
    {
        long result = 0;
        long max = Math.Max(a, b);
        long min = Math.Min(a, b);
        long i = 1;
        while ( result == 0 )
        {
            if ( (max * i) % min == 0 )
                result = max * i;
            i++;
        }
        return result;
    }

    long FindDestiny2(string origin, Dictionary<string, Node> nodeMap, int index, List<int> instructionList)
    {
        long result = 0;
        while( origin[2] != 'Z' )
        {
            Node node = nodeMap[origin];
            if (index == instructionList.Count)
                index = 0;
            int indexInstruction = instructionList[index];
            origin = node.destination[indexInstruction];
            index++;
            result++;
        }
        return result;
    }


    // Update is called once per frame
    void Update()
    {
        
    }
}

