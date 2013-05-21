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
        Console.WriteLine("a - 2: {0}", a - 2);
        Debug.Assert(a.IsNotZero());
        Debug.Assert((a - 2).IsGreaterThanOrEqualToZero());
        Debug.Assert(!(a - 2).IsGreaterThanZero());

        Interval c = 3 * a;
        Debug.Assert(c.LowerBound == 6);
        Debug.Assert(c.UpperBound == 9);
        Debug.Assert((c.Median - 7.5).IsZero());
    }

    public static void Main()
    {
        TestInterval();
    }
}
