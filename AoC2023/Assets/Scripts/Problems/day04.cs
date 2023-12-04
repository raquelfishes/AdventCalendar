using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using Unity.Mathematics;
using UnityEngine;

public class day04 : MonoBehaviour
{
    string path = "Assets/Resources/day04.txt";

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
            string[] cardInfo = line.Split(':');
            if (cardInfo.Length < 2)
            {
                Console.Error.WriteLine("No valid card info");
                return;
            }
            string[] cardPlay = cardInfo[1].Split('|');
            if (cardPlay.Length < 2)
            {
                Console.Error.WriteLine("No valid card play");
                return;
            }
            MatchCollection matchesPrizes = Regex.Matches(cardPlay[0], @"\b(\d+)");
            MatchCollection matchesPlay = Regex.Matches(cardPlay[1], @"\b(\d+)");
            if (matchesPrizes.Count == 0 || matchesPlay.Count == 0)
            {
                Console.Error.WriteLine("No valid card play");
                return;
            }
            
            var intersection = matchesPrizes.Cast<Match>().Select(m => m.Value).Intersect(matchesPlay.Cast<Match>().Select(m => m.Value));
            result += (long)Math.Pow(2, intersection.Count() - 1);
        }

        Debug.Log("Result: " + Convert.ToString(result));
    }


    void part2()
    {
        StreamReader reader = File.OpenText(path);
        string line = null;
        long result = 0;
        Stack extraCards = new Stack();
        while ((line = reader.ReadLine()) != null) 
        {
            string[] cardInfo = line.Split(':');
            if (cardInfo.Length < 2)
            {
                Console.Error.WriteLine("No valid card info");
                return;
            }
            string[] cardPlay = cardInfo[1].Split('|');
            if (cardPlay.Length < 2)
            {
                Console.Error.WriteLine("No valid card play");
                return;
            }
            MatchCollection matchesPrizes = Regex.Matches(cardPlay[0], @"\b(\d+)");
            MatchCollection matchesPlay = Regex.Matches(cardPlay[1], @"\b(\d+)");
            if (matchesPrizes.Count == 0 || matchesPlay.Count == 0)
            {
                Console.Error.WriteLine("No valid card play");
                return;
            }
            
            var intersection = matchesPrizes.Cast<Match>().Select(m => m.Value).Intersect(matchesPlay.Cast<Match>().Select(m => m.Value));
            int winCards = intersection.Count();
            int countCards = extraCards.Count > 0 ? 1 + (int)extraCards.Pop() : 1;
            Stack auxStack = new Stack();
            if (winCards>0)
            {
                for(int i=0; i<winCards;++i)
                {
                    if ( extraCards.Count > 0)
                    {
                        auxStack.Push((int)extraCards.Pop() + countCards);
                    }
                    else
                    {
                        auxStack.Push(countCards);
                    }
                }

            }
            while (auxStack.Count > 0)
            {
                extraCards.Push(auxStack.Pop());
            }
            
            result += countCards;
        }

        Debug.Log("Result: " + Convert.ToString(result));
    }


    // Update is called once per frame
    void Update()
    {
        
    }
}
