using System.Collections.Generic;

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
    }
    Grid(int width, int height)
    {
        this.Width = width;
        this.Height = height;
        gridArray = new List<T>(width*height);
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

    public void SetRow(in int x, in T[] row)
    {
        for (int y = 0; y < row.Length; y++)
        {
            gridArray[x*Width+y] = row[y];
        }
    }

    public void GetCoord(in int pos, out int x, out int y)
    {
        x = pos / Width;
        y = pos % Width;
    }

    public bool IsValidCoord(in int x, in int y)
    {
        return x >= 0 && x < Width && y >= 0 && y < Height;
    }

    public T GetValue(in int x, in int y)
    {
        return gridArray[x * Width + y];
    }

    public void SetValue(in int x, in int y, in T value)
    {
        gridArray[x * Width + y] = value;
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
                grid += System.Convert.ToString(GetValue(i,j));
            }
            grid+= "\n";
        }
        UnityEngine.Debug.Log(grid);
    }
}
