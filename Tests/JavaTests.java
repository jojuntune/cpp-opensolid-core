package ca.ianmackenzie.tests;

import org.opensolid.*;

class JavaTests {
    static void testInterval() {
        Interval a = new Interval(2, 3);
        Interval b = new Interval(3.0);
        System.out.format("a: %s\n", a);
        System.out.format("b: %s\n", b);
        System.out.format("a.difference(2.0): %s\n", a.difference(2));

        Interval c = a.product(3);
        assert(c.getLowerBound() == 6);
        assert(c.getUpperBound() == 9);
        assert(Math.abs(c.getMedian() - 7.5) < 1e-12);
    }

    public static void main(String[] arguments) {
        testInterval();
    }
}
