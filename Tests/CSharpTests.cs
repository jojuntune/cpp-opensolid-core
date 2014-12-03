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

        Interval c = 3 * a;
        Debug.Assert(c.getLowerBound() == 6);
        Debug.Assert(c.getUpperBound() == 9);
    }

    public static void Main()
    {
        TestInterval();
    }
}
