using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using UnityEngine;
using UnityEngine.Rendering;

class Card:IComparable<Card>, IEquatable<Card>
{
    //List<char> codeValueSortOrderPart1 = new List<char>{ 'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2' };
    List<char> codeValueSortOrderPart2 = new List<char>{ 'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J' };
    public char value;
    public int CompareTo(Card other)
    {
        if (value == other.value)
            return 0;

        if (codeValueSortOrderPart2.IndexOf(value)<0)
        {
            int i=0;
        }
        if (codeValueSortOrderPart2.IndexOf(other.value)<0)
        {
            int i=0;
        }

        if (codeValueSortOrderPart2.IndexOf(value) > codeValueSortOrderPart2.IndexOf(other.value))
            return 1;
        return -1;
    }
    
    public bool Equals(Card other)
    {
        return value == other.value;
    }
}

class Hand:IComparable<Hand>
{
    public List<Card> cards;
    public long bid;
    public int type;
    public int CompareTo(Hand other) 
    {
        int result = type.CompareTo(other.type);
        if ( result == 0 )
        {
            for (int i = 0; i < 5; i++)
            {
                result = cards[i].CompareTo(other.cards[i]);
                if (result != 0)
                    break;
            }
        }
        return result;
    }
}

public class day07 : MonoBehaviour
{
    string path = "Assets/Resources/day07.txt";

    // Start is called before the first frame update
    void Start()
    {
        //part1();
        part2();
    }

    int ComputeTypePart1(List<Card> cards)
    {
        // Sort cards
        cards = cards.OrderBy(c => c).ToList();

        // 7 - Five of a kind, where all five cards have the same label: AAAAA
        if ( cards[0].value == cards[4].value )
            return 1;
        // 6 - Four of a kind, where four cards have the same label and one card has a different label: AA8AA
        if ( ( cards[0].value == cards[3].value ) || ( cards[1].value == cards[4].value ) )
            return 2;
        // 5 - Full house, where three cards have the same label, and the remaining two cards share a different label: 23332
        if ( ( cards[0].value == cards[2].value && cards[3].value == cards[4].value ) || ( cards[0].value == cards[1].value && cards[2].value == cards[4].value ) )
            return 3;
        // 4 - Three of a kind, where three cards have the same label, and the remaining two cards are each different from any other card in the hand: TTT98
        if ( ( cards[0].value == cards[2].value ) || ( cards[1].value == cards[3].value ) || ( cards[2].value == cards[4].value ) )
            return 4;
        // 3 - Two pair, where two cards share one label, two other cards share a second label, and the remaining card has a third label: 23432
        if ((cards[0].value == cards[1].value && cards[2].value == cards[3].value) || (cards[0].value == cards[1].value && cards[3].value == cards[4].value) || (cards[1].value == cards[2].value && cards[3].value == cards[4].value))
            return 5;
        // 2 - One pair, where two cards share one label, and the other three cards have a different label from the pair and each other: A23A4
        if (cards[0].value == cards[1].value || cards[1].value == cards[2].value || cards[2].value == cards[3].value || cards[3].value == cards[4].value)
            return 6;
        // 1 - High card
        return 7;
    }

    int ComputeTypePart2( in List<Card> cards)
    {
        // For Part 2
        // count J in cards
        int countJ = cards.Count(c => c.value == 'J');
        if ( countJ == 0 ) return ComputeTypePart1(cards);
        if (countJ >= 4) return 1;

        List<Card> cards2 = new List<Card>(cards);
        cards2.RemoveAll(c => c.value == 'J');

        // Sort cards
        cards2 = cards2.OrderBy(c => c).ToList();
        if ( cards2[0].value == cards2[cards2.Count-1].value )
            return 1;   

        if ( countJ == 3 )
            return 2;
        
        if ( countJ == 2 )
        {
            if (cards2[0].value == cards2[1].value || cards2[1].value == cards2[2].value)
                return 2;
            else
                return 4;
        }
        if ( countJ == 1 ) 
        {
            if (cards2[0].value == cards2[2].value || cards2[1].value == cards2[3].value)
                return 2;
            else if (cards2[0].value == cards2[1].value && cards2[2].value == cards2[3].value)
                return 3;
            else if (cards2[0].value == cards2[1].value || cards2[1].value == cards2[2].value || cards2[2].value == cards2[3].value)
                return 4;
            else
                return 6;
        }
        return 7;
        

        //// 1 - Five of a kind, where all five cards have the same label: AAAAA
        //if ( cards[0].value == cards[4].value )
        //    return 1;
        //// 2 - Four of a kind, where four cards have the same label and one card has a different label: AA8AA
        //if ( ( cards[0].value == cards[3].value ) || ( cards[1].value == cards[4].value ) )
        //    return 2;
        //// 3 - Full house, where three cards have the same label, and the remaining two cards share a different label: 23332
        //if ( ( cards[0].value == cards[2].value && cards[3].value == cards[4].value ) || ( cards[0].value == cards[1].value && cards[2].value == cards[4].value ) )
        //    return 3;
        //// 4 - Three of a kind, where three cards have the same label, and the remaining two cards are each different from any other card in the hand: TTT98
        //if ( ( cards[0].value == cards[2].value ) || ( cards[1].value == cards[3].value ) || ( cards[2].value == cards[4].value ) )
        //    return 4;
        //// 5 - Two pair, where two cards share one label, two other cards share a second label, and the remaining card has a third label: 23432
        //if ((cards[0].value == cards[1].value && cards[2].value == cards[3].value) || (cards[0].value == cards[1].value && cards[3].value == cards[4].value) || (cards[1].value == cards[2].value && cards[3].value == cards[4].value))
        //    return 5;
        //// 6 - One pair, where two cards share one label, and the other three cards have a different label from the pair and each other: A23A4
        //if (cards[0].value == cards[1].value || cards[1].value == cards[2].value || cards[2].value == cards[3].value || cards[3].value == cards[4].value)
        //    return 6;
        //// 7 - High card
        //return 7;
    }

    void part1()
    {
        StreamReader reader = File.OpenText(path);
        string line = null;
        List<Hand> hands = new List<Hand>();
        while ((line = reader.ReadLine()) != null) 
        {
            MatchCollection matches = Regex.Matches(line, @"(.+)\s+(\d+)");
            if ( matches.Count > 0)
            {
                Hand hand = new Hand();
                // convert string to array of char
                hand.cards = new List<Card>(new Card[5]);
                for( int i=0; i<5; i++ )
                {
                    hand.cards[i] = new Card();
                    hand.cards[i].value = matches[0].Groups[1].Value[i];
                }
                hand.bid = Convert.ToInt64(matches[0].Groups[2].Value);
                hand.type = ComputeTypePart1(hand.cards);
                hands.Add(hand);
            }
        }

        hands.Sort();
        // max number of uint64 get from system
        long result = 0;
        for( int i=hands.Count-1; i>=0; i-- )
        {
            result += hands[i].bid*(hands.Count - i);
        }

        Debug.Log("Result: " + Convert.ToString(result));
    }


    void part2()
    {
        StreamReader reader = File.OpenText(path);
        string line = null;
        List<Hand> hands = new List<Hand>();
        while ((line = reader.ReadLine()) != null) 
        {
            MatchCollection matches = Regex.Matches(line, @"(.+)\s+(\d+)");
            if ( matches.Count > 0)
            {
                Hand hand = new Hand();
                // convert string to array of char
                hand.cards = new List<Card>(new Card[5]);
                for( int i=0; i<5; i++ )
                {
                    hand.cards[i] = new Card();
                    hand.cards[i].value = matches[0].Groups[1].Value[i];
                }
                hand.bid = Convert.ToInt64(matches[0].Groups[2].Value);
                hand.type = ComputeTypePart2(hand.cards);
                hands.Add(hand);
            }
        }

        hands.Sort();

        // max number of uint64 get from system
        long result = 0;
        for( int i=hands.Count-1; i>=0; i-- )
        {
            result += hands[i].bid*(hands.Count - i);
        }

        Debug.Log("Result: " + Convert.ToString(result));
    }


    // Update is called once per frame
    void Update()
    {
        
    }
}

