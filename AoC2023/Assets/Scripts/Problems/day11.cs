using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using UnityEngine;
using UnityEngine.Rendering;
public class day11 : MonoBehaviour
{
    string path = "Assets/Resources/day11.txt";

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
        long height = 0;
        List<Vector2Int> positions = new List<Vector2Int>();
        //ordered list
        List<long> emptyRow = new List<long>();
        List<long> emptyColumn = new List<long>();
        while ((line = reader.ReadLine()) != null) 
        {
            if ( height == 0)
            {
                emptyColumn = Enumerable.Range(0, line.Length).Select(i => (long)i).ToList();
            }

            MatchCollection matchesGalaxy = Regex.Matches(line, @"[#]");
            if (matchesGalaxy.Count == 0)
            {
                emptyRow.Add(height);
            }
            foreach(Match match in matchesGalaxy)
            {
                Vector2Int point = new Vector2Int(match.Index, (int)height);
                if ( emptyColumn.Contains(point.x))
                {
                    emptyColumn.Remove(point.x);
                }
                positions.Add(point);
            }
            height++;
        }

        for( int i=0; i< positions.Count; ++i)
        {
            for (int j=i+1; j< positions.Count; ++j)
            {
                Vector2Int pointOrigin = positions[i];  
                Vector2Int pointDest = positions[j];
                Vector2Int distance = positions[i] - positions[j];
                Vector2Int direction = new Vector2Int(distance.x > 0 ? -1 : 1, distance.y > 0 ? -1 : 1);
                long distanceX = Math.Abs(distance.x);
                long distanceY = Math.Abs(distance.y);
                while (pointOrigin.x != pointDest.x)
                {
                    if (emptyColumn.Contains(pointOrigin.x + direction.x))
                    {
                        distanceX += 1;
                    }
                    pointOrigin.x += direction.x;
                }
                while (pointOrigin.y != pointDest.y)
                {
                    if (emptyRow.Contains(pointOrigin.y + direction.y))
                    {
                        distanceY += 1;
                    }
                    pointOrigin.y += direction.y;
                }
                result += distanceX + distanceY;
            }
        }

        Debug.Log("Result: " + Convert.ToString(result));
    }

    void part2()
    {
       StreamReader reader = File.OpenText(path);
        string line = null;
        long result = 0;
        long height = 0;
        List<Vector2Int> positions = new List<Vector2Int>();
        //ordered list
        List<long> emptyRow = new List<long>();
        List<long> emptyColumn = new List<long>();
        while ((line = reader.ReadLine()) != null) 
        {
            if ( height == 0)
            {
                emptyColumn = Enumerable.Range(0, line.Length).Select(i => (long)i).ToList();
            }

            MatchCollection matchesGalaxy = Regex.Matches(line, @"[#]");
            if (matchesGalaxy.Count == 0)
            {
                emptyRow.Add(height);
            }
            foreach(Match match in matchesGalaxy)
            {
                Vector2Int point = new Vector2Int(match.Index, (int)height);
                if ( emptyColumn.Contains(point.x))
                {
                    emptyColumn.Remove(point.x);
                }
                positions.Add(point);
            }
            height++;
        }

        for( int i=0; i< positions.Count; ++i)
        {
            for (int j=i+1; j< positions.Count; ++j)
            {
                Vector2Int pointOrigin = positions[i];  
                Vector2Int pointDest = positions[j];
                Vector2Int distance = positions[i] - positions[j];
                Vector2Int direction = new Vector2Int(distance.x > 0 ? -1 : 1, distance.y > 0 ? -1 : 1);
                long distanceX = Math.Abs(distance.x);
                long distanceY = Math.Abs(distance.y);
                while (pointOrigin.x != pointDest.x)
                {
                    if (emptyColumn.Contains(pointOrigin.x + direction.x))
                    {
                        distanceX += 1000000-1;
                    }
                    pointOrigin.x += direction.x;
                }
                while (pointOrigin.y != pointDest.y)
                {
                    if (emptyRow.Contains(pointOrigin.y + direction.y))
                    {
                        distanceY += 1000000-1;
                    }
                    pointOrigin.y += direction.y;
                }
                result += distanceX + distanceY;
            }
        }

        Debug.Log("Result: " + Convert.ToString(result));
    }
    // 603021166712

    
    // Update is called once per frame
    void Update()
    {
        
    }
}

