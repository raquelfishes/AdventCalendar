using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using NUnit.Framework.Constraints;
using Unity.Mathematics;
using Unity.VisualScripting;
using UnityEngine;

public class day06 : MonoBehaviour
{
    string path = "Assets/Resources/day06.txt";

    class Race
    {
        public Race() { }
        public Race(int time, int distanceRecord, int countOfWaysToWin)
        {
            this.time = time;
            this.distanceRecord = distanceRecord;
            this.countOfWaysToWin = countOfWaysToWin;
        }
        public long time                 {get;set;}
        public long distanceRecord       {get;set;}
        public long countOfWaysToWin     {get;set;}
    }
    
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
        List<Race> races = new List<Race>();
        while ((line = reader.ReadLine()) != null) 
        {
            MatchCollection matchesTime = Regex.Matches(line, @"Time:(\s+\d+)+");
            if ( matchesTime.Count > 0)
            {
                MatchCollection matches = Regex.Matches(matchesTime[0].Value, @"\b(\d+)");
                foreach (Match match in matches)
                {
                    Race race = new Race();
                    race.time = Convert.ToInt32(match.Value);
                    races.Add(race);
                }
                continue;
            }

            MatchCollection matchesDistance = Regex.Matches(line, @"Distance:(\s+\d+)+");
            if ( matchesDistance.Count > 0)
            {
                MatchCollection matches = Regex.Matches(matchesDistance[0].Value, @"\b(\d+)");
                int index = 0;
                foreach (Match match in matches)
                {
                    races[index++].distanceRecord = Convert.ToInt32(match.Value);
                }
                continue;
            }
        }

        // max number of uint64 get from system
        long result = 1;
        foreach( Race race  in races )
        {
            for ( int i=1; i<=race.time/2; i++ )
            {
                int distance = i*((int)race.time-i );
                if ( distance > race.distanceRecord )
                    race.countOfWaysToWin+=2;
            }
            if (race.time % 2 == 0)
                race.countOfWaysToWin--;
            result *= race.countOfWaysToWin;
        }

        Debug.Log("Result: " + Convert.ToString(result));
    }


    void part2()
    {
        StreamReader reader = File.OpenText(path);
        string line = null;
        Race race = new Race();
        while ((line = reader.ReadLine()) != null) 
        {
            MatchCollection matchesTime = Regex.Matches(line, @"Time:(.*)");
            if ( matchesTime.Count > 0)
            {
                string time = matchesTime[0].Groups[1].Value.Replace(" ","");
                race.time = Convert.ToInt64(time);
            }

            MatchCollection matchesDistance = Regex.Matches(line, @"Distance:(.*)");
            if ( matchesDistance.Count > 0)
            {
                string time = matchesDistance[0].Groups[1].Value.Replace(" ","");
                race.distanceRecord = Convert.ToInt64(time);
            }
        }

        // max number of uint64 get from system
        long result = 1;
        for ( long i=1; i<=race.time/2; i++ )
        {
            long distance = i*((long)race.time-i );
            if ( distance > race.distanceRecord )
                race.countOfWaysToWin+=2;
        }
        if (race.time % 2 == 0)
            race.countOfWaysToWin--;

        result = race.countOfWaysToWin;
        Debug.Log("Result: " + Convert.ToString(result));
    }


    // Update is called once per frame
    void Update()
    {
        
    }
}
