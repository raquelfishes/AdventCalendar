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

public class day05 : MonoBehaviour
{
    string path = "Assets/Resources/day05.txt";

    struct Redirect
    {
        public long source;
        public long destination;
        public long rangeLength;
    }
    struct AlmanacMap
    {
        public string source;
        public string destination;
        public List<Redirect> redirects;
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
        List<ulong> seedList = new List<ulong>();
        List<AlmanacMap> almanacList = new List<AlmanacMap>();
        while ((line = reader.ReadLine()) != null) 
        {
            MatchCollection matchesSeed = Regex.Matches(line, @"seeds:(\s\d+)+");
            if ( matchesSeed.Count > 0)
            {
                MatchCollection matches = Regex.Matches(matchesSeed[0].Value, @"\b(\d+)");
                foreach (Match match in matches)
                {
                    seedList.Add(Convert.ToUInt64(match.Value));
                }
                continue;
            }

            MatchCollection matchesMap = Regex.Matches(line, @"(\w+)-to-(\w+)\smap\:");
            if ( matchesMap.Count > 0 )
            {
                AlmanacMap almanacMap = new AlmanacMap();
                almanacMap.redirects = new List<Redirect>();
                almanacMap.source = matchesMap[0].Groups[1].Value;
                almanacMap.destination = matchesMap[0].Groups[2].Value;
                while((line = reader.ReadLine()) != null && line.Length > 0)
                {
                    Redirect redirect = new Redirect();
                    MatchCollection matchesRedirect = Regex.Matches(line, @"(\d+)");
                    if ( matchesRedirect.Count > 0)
                    {
                        redirect.destination = Convert.ToInt64(matchesRedirect[0].Value);
                        redirect.source = Convert.ToInt64(matchesRedirect[1].Value);
                        redirect.rangeLength = Convert.ToInt64(matchesRedirect[2].Value);
                        almanacMap.redirects.Add(redirect);
                    }
                }
                almanacList.Add(almanacMap);
            }
        }

        // max number of uint64 get from system
        long result = long.MaxValue;
        foreach (long seed in seedList)
        {
            string currentSource = "seed";
            result = Math.Min(result, GetSeed(currentSource, (long)seed, almanacList));
        }

        Debug.Log("Result: " + Convert.ToString(result));
    }

    long GetSeed(string source, long tempIndex, List<AlmanacMap> almanacList)
    {
        //Debug.Log(source + " " + Convert.ToString(tempIndex));
        if ( source == "location")
        {
            return tempIndex;
        }

        foreach (AlmanacMap almanacMap in almanacList)
        {
            if (almanacMap.source == source)
            {
                foreach(Redirect redirect in almanacMap.redirects)
                {
                    if (tempIndex >= redirect.source && tempIndex < redirect.source + redirect.rangeLength)
                    {
                        long newIndex = tempIndex-redirect.source+redirect.destination;
                        return GetSeed(almanacMap.destination, newIndex, almanacList);
                    }
                }
                return GetSeed(almanacMap.destination, tempIndex, almanacList);
            }
        }
        return tempIndex;
    }   


    void part2()
    {
        StreamReader reader = File.OpenText(path);
        string line = null;
        List<long> seedList = new List<long>();
        List<AlmanacMap> almanacList = new List<AlmanacMap>();
        while ((line = reader.ReadLine()) != null) 
        {
            MatchCollection matchesSeed = Regex.Matches(line, @"seeds:(\s\d+)+");
            if ( matchesSeed.Count > 0)
            {
                MatchCollection matches = Regex.Matches(matchesSeed[0].Value, @"\b(\d+)");
                foreach (Match match in matches)
                {
                    seedList.Add(Convert.ToInt64(match.Value));
                }
                continue;
            }

            MatchCollection matchesMap = Regex.Matches(line, @"(\w+)-to-(\w+)\smap\:");
            if ( matchesMap.Count > 0 )
            {
                AlmanacMap almanacMap = new AlmanacMap();
                almanacMap.redirects = new List<Redirect>();
                almanacMap.source = matchesMap[0].Groups[1].Value;
                almanacMap.destination = matchesMap[0].Groups[2].Value;
                while((line = reader.ReadLine()) != null && line.Length > 0)
                {
                    Redirect redirect = new Redirect();
                    MatchCollection matchesRedirect = Regex.Matches(line, @"(\d+)");
                    if ( matchesRedirect.Count > 0)
                    {
                        redirect.destination = Convert.ToInt64(matchesRedirect[0].Value);
                        redirect.source = Convert.ToInt64(matchesRedirect[1].Value);
                        redirect.rangeLength = Convert.ToInt64(matchesRedirect[2].Value);
                        almanacMap.redirects.Add(redirect);
                    }
                }
                almanacList.Add(almanacMap);
            }
        }

        // max number of uint64 get from system
        long result = long.MaxValue;
        for (int i = 0; i < seedList.Count; i=i+2)
        {
            for (long j=seedList[i];j<seedList[i]+seedList[i+1];++j)
            {
                string currentSource = "seed";
                result = Math.Min(result, GetSeed(currentSource, (long)j, almanacList));
            }
        }

        Debug.Log("Result: " + Convert.ToString(result));
    }

    void getSeedRange(string source, long initIndex, long endIndex, List<AlmanacMap> almanacList)
    {

    }


    // Update is called once per frame
    void Update()
    {
        
    }
}
