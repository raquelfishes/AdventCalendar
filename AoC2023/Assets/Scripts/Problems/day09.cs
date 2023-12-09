using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using UnityEngine;
using UnityEngine.Rendering;
public class day09 : MonoBehaviour
{
    string path = "Assets/Resources/day09.txt";

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
            MatchCollection matchesSequence = Regex.Matches(line, @"(\-?\d+)");
            if ( matchesSequence.Count > 0)
            {
                List<long> sequence = new List<long>();
                foreach(Match c in matchesSequence)
                {
                    sequence.Add(Convert.ToInt64(c.ToString()));
                }
                long auxResult = ComputeNextInSequence(sequence);
                result += auxResult;
                continue;   
            }
        }

        Debug.Log("Result: " + Convert.ToString(result));
    }

    long ComputeNextInSequence(List<long> sequence)
    {
        if (sequence.TrueForAll( x => x == 0 )) 
        { 
            return 0; 
        }

        List<long> nextLevelSequence = new List<long>();
        for ( int i=0; i < sequence.Count-1; i++ )
        {
            nextLevelSequence.Add(sequence[i + 1] - sequence[i]);
        }
        long auxResult = ComputeNextInSequence(nextLevelSequence);
        return sequence[sequence.Count-1] + auxResult;
    }
    
    long ComputePreviousInSequence(List<long> sequence)
    {
        if (sequence.TrueForAll( x => x == 0 )) 
        { 
            return 0; 
        }

        List<long> nextLevelSequence = new List<long>();
        for ( int i=0; i < sequence.Count-1; i++ )
        {
            nextLevelSequence.Add(sequence[i + 1] - sequence[i]);
        }
        long auxResult = ComputePreviousInSequence(nextLevelSequence);
        return sequence[0] - auxResult;
    }

    void part2()
    {
       StreamReader reader = File.OpenText(path);
        string line = null;
        long result = 0;
        while ((line = reader.ReadLine()) != null) 
        {
            MatchCollection matchesSequence = Regex.Matches(line, @"(\-?\d+)");
            if ( matchesSequence.Count > 0)
            {
                List<long> sequence = new List<long>();
                foreach(Match c in matchesSequence)
                {
                    sequence.Add(Convert.ToInt64(c.ToString()));
                }
                long auxResult = ComputePreviousInSequence(sequence);
                result += auxResult;
                continue;   
            }
        }

        Debug.Log("Result: " + Convert.ToString(result));
    }

    
    // Update is called once per frame
    void Update()
    {
        
    }
}

