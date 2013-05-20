using System;
using OpenSolid;

public class HelloOpenSolid
{
    public static void Main()
    {
        Interval a = new Interval(2, 3);
        Interval b = new Interval(4, 5);
        Console.WriteLine("Sum: {0}", a + b);
    }
}
