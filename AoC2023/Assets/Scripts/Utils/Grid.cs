using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using UnityEngine;
using static UnityEngine.Rendering.DebugUI;

public class Grid<T>
{
    public int Width{ get; set; }
    public int Height{ get; set; }

    public List<T> gridArray;

    // x = row, y = column (excel style)
    
    // Default constructor
    public Grid()
    {
        gridArray = new List<T>();
        this.Width = 0;
        this.Height = 0;
    }
    public Grid(int width, int height)
    {
        this.Width = width;
        this.Height = height;
        gridArray = new List<T>(width*height);
    }

    public Grid(int width, int height, T initValue)
    {
        this.Width = width;
        this.Height = height;
        //gridArray = new List<T>(width*height);
        gridArray = Enumerable.Repeat(initValue, this.Width*this.Height).ToList();
    }

    public Grid(Grid<T> g)
    {
        this.Width = g.Width;
        this.Height = g.Height;
        //gridArray = new List<T>(width*height);
        gridArray = new List<T>(g.gridArray);
    }

    public T this[int x, int y]
    {
        get => gridArray[GetIndex(x,y)];
        set => gridArray[GetIndex(x,y)] = value;
    }

    public static bool operator ==(Grid<T> a, Grid<T> b)
    {
        if (a.Width != b.Width || a.Height != b.Height)
        {
            return false;
        }
        for (int i = 0; i < a.gridArray.Count; i++)
        {
            if (!a.gridArray[i].Equals(b.gridArray[i]))
            {
                return false;
            }
        }
        return true;
    }

    public static bool operator !=(Grid<T> a, Grid<T> b)
    {
        return !(a == b);
    }

    public override string ToString()
    {
        string aux = "";
        for (int i = 0; i < Height; i++)
        {
            for (int j = 0; j < Width; j++) 
            {
                aux += $"{System.Convert.ToString(gridArray[GetIndex(j,i)]),3}";
            }
            aux += "\n";
        }
        return aux;
    }

    public override bool Equals(object o)
    {
       if(o == null)
           return false;

       var second = o as Grid<T>;
       
       return second != null && this == second;
    }

    public override int GetHashCode()
    {
        int result = 1;
        foreach (var item in gridArray)
        {
            result = result * 31 + item.GetHashCode();
        }
        return result;
    }

    public void ResizeGrid(in int width, in int height)
    {
        this.Width = width;
        this.Height = height;
        gridArray = new List<T>(width*height);
    }

    public void SetWidth(in int width)
    {
        this.Width = width;
    }

    public void setHeight(in int height)
    {
        this.Height = height;
    }

    public void AddRow(in T[] row)
    {
        if ( Width == 0)
        {
            this.Width = row.Length;
        }

        if ( row.Length != Width)
        {
            Debug.LogError("Row lenght is not equal to grid width");
            return;
        }

        for (int y = 0; y < row.Length; y++)
        {
            gridArray.Add(row[y]);
        }
        this.Height++;
    }

    public void SetRow(in int x, in T[] row)
    {
        for (int y = 0; y < row.Length; y++)
        {
            gridArray[GetIndex(x,y)] = row[y];
        }
    }

    public void GetCoord(in int pos, out Vector2Int value)
    {
        value = new Vector2Int();
        int auxX, auxY;
        GetCoord(pos, out auxX, out auxY);
        value.x = auxX;
        value.y = auxY;
    }

    public void GetCoord(in int pos, out int x, out int y)
    {
        y = pos / Width;
        x = pos % Width;
    }

    public bool IsValidCoord(in Vector2Int coord)
    {
        return IsValidCoord((int)coord.x, (int)coord.y);
    }

    public bool IsValidCoord(in int x, in int y)
    {
        return x >= 0 && x < Width && y >= 0 && y < Height;
    }

    public int GetIndex(in Vector2Int coord)
    {
        return GetIndex(coord.x, coord.y);
    }

    public int GetIndex(in int x, in int y)
    {
        return y * Width + x;
    }

    public T GetValue(in Vector2Int coord)
    {
        return GetValue(coord.x, coord.y);
    }

    public T GetValue(in int x, in int y)
    {
        return gridArray[GetIndex(x,y)];
    }
    public void SetValue(in Vector2Int coord, in T value)
    {
        SetValue(coord.x, coord.y, value);
    }

    public void SetValue(in int x, in int y, in T value)
    {
        gridArray[GetIndex(x,y)] = value;
    }

    public void AddValue( in T value)
    {
        gridArray.Add(value);
    }
    
    public void printGrid()
    {
        string grid = "";
        for (int i=0; i<Height; i++)
        {
            for (int j=0; j<Width; j++)
            {
                grid += $"{System.Convert.ToString(GetValue(j,i)),3}";
            }
            grid+= "\n";
        }
        UnityEngine.Debug.Log(grid);
    }
}
