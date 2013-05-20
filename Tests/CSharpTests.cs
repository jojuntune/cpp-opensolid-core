using System;
using System.Diagnostics;
using OpenSolid;

public class CSharpTests
{
    static void TestInterval()
    {
        Interval a = new Interval(2, 3);
        Interval b = 3.0;
        Console.WriteLine("a: {0}", a);
        Console.WriteLine("b: {0}", b);

        Interval c = 3.0 * a;
        Debug.Assert(c.LowerBound == 6.0);
        Debug.Assert(c.UpperBound == 9.0);
        Debug.Assert(c.Median - 7.5 == new Zero());
    }

    public static void Main()
    {
        TestInterval();
    }
}
