/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
*  ian.e.mackenzie@gmail.com                                                        *
*                                                                                   *
*  This library is free software; you can redistribute it and/or                    *
*  modify it under the terms of the GNU Lesser General Public                       *
*  License as published by the Free Software Foundation; either                     *
*  version 2.1 of the License, or (at your option) any later version.               *
*                                                                                   *
*  This library is distributed in the hope that it will be useful,                  *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
*  Lesser General Public License for more details.                                  *
*                                                                                   *
*  You should have received a copy of the GNU Lesser General Public                 *
*  License along with this library; if not, write to the Free Software              *
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
*                                                                                   *
************************************************************************************/

#include <OpenSolid/Core/Interval.hpp>

#include <catch/catch.hpp>

#include <cmath>
#include <cfloat>

using namespace opensolid;

TEST_CASE("Basic functionality") {
    Interval five(5.0);
    REQUIRE(five.lowerBound() == 5.0);
    REQUIRE(five.upperBound() == 5.0);
    REQUIRE(five.width() == 0.0);
    REQUIRE(five.median() == 5.0);
}

TEST_CASE("Negation") {
    Interval two_three(2.0, 3.0);
    
    Interval negated = -two_three;
    REQUIRE(negated.lowerBound() == -3.0);
    REQUIRE(negated.upperBound() == -2.0);
    REQUIRE(negated.width() == 1.0);
    REQUIRE(negated.median() == -2.5);

    Interval cancelled = -negated;
    REQUIRE(cancelled.lowerBound() == 2.0);
    REQUIRE(cancelled.upperBound() == 3.0);
    REQUIRE(cancelled.width() == 1.0);
    REQUIRE(cancelled.median() == 2.5);
}

TEST_CASE("Addition") {
    Interval two_three(2.0, 3.0);
    Interval constant_sum = 1.0 + two_three;
    REQUIRE(constant_sum.lowerBound() == 3.0);
    REQUIRE(constant_sum.upperBound() == 4.0);
}

TEST_CASE("Subtraction") {
    Interval two_three(2.0, 3.0);
    Interval constant_difference = 1.0 - two_three;
    REQUIRE(constant_difference.lowerBound() == -2.0);
    REQUIRE(constant_difference.upperBound() == -1.0);
}

TEST_CASE("Squaring") {
    Interval two_three(2.0, 3.0);
    Interval four_nine = two_three.squared();
    REQUIRE(four_nine.lowerBound() == 4.0);
    REQUIRE(four_nine.upperBound() == 9.0);
}

TEST_CASE("Bisection") {
    Interval x(4, 5);
    std::pair<Interval, Interval> bisected = x.bisected();
    REQUIRE(bisected.first.lowerBound() == 4);
    REQUIRE(bisected.first.upperBound() == 4.5);
    REQUIRE(bisected.second.lowerBound() == 4.5);
    REQUIRE(bisected.second.upperBound() == 5);
}

TEST_CASE("Random generation") {
    Interval interval(-2, 3);
    for (int i = 0; i < 100; ++i) {
        double random = interval.randomValue();
        REQUIRE(interval.lowerBound() <= random);
        REQUIRE(random <= interval.upperBound());
    }
}

TEST_CASE("Tolerant equality") {
    Interval squares(16.0, 81.0);
    REQUIRE(sqrt(squares).equals(Interval(4.0, 9.0)));
}

TEST_CASE("Sine") {
    auto test = [] (double xLower, double xUpper, double yLower, double yUpper) {
        CAPTURE(xLower);
        CAPTURE(xUpper);
        CAPTURE(yLower);
        CAPTURE(yUpper);
        Interval x(xLower, xUpper);
        Interval y = sin(x);
        CAPTURE(y);
        REQUIRE((y.lowerBound() - yLower) == Zero());
        REQUIRE((y.upperBound() - yUpper) == Zero());
    };

    test(-0.5, 0.5, sin(-0.5), sin(0.5));
    test(1.25, 2.5, sin(2.5), 1.0);
    test(4.0, 4.1, sin(4.1), sin(4.0));
    test(4.0, 6.0, -1.0, sin(6.0));
    test(4.0, 8.0, -1.0, 1.0);
    test(-6.0, -4.0, sin(-6.0), 1.0);
    test(-1.0, 3.5, sin(-1.0), 1.0);
}

TEST_CASE("Cosine") {
    auto test = [] (double xLower, double xUpper, double yLower, double yUpper) {
        CAPTURE(xLower);
        CAPTURE(xUpper);
        CAPTURE(yLower);
        CAPTURE(yUpper);
        Interval x(xLower, xUpper);
        Interval y = cos(x);
        CAPTURE(y);
        REQUIRE((y.lowerBound() - yLower) == Zero());
        REQUIRE((y.upperBound() - yUpper) == Zero());
    };

    test(-0.5, 0.5, cos(0.5), 1.0);
    test(1.25, 2.5, cos(2.5), cos(1.25));
    test(4.0, 4.1, cos(4.0), cos(4.1));
    test(4.0, 6.0, cos(4.0), cos(6.0));
    test(4.0, 8.0, cos(4.0), 1.0);
    test(-6.0, -4.0, cos(-4.0), cos(-6.0));
    test(-1.0, 3.5, -1.0, 1.0);

}

TEST_CASE("Tangent") {
    auto test = [] (double xLower, double xUpper, double yLower, double yUpper) {
        CAPTURE(xLower);
        CAPTURE(xUpper);
        CAPTURE(yLower);
        CAPTURE(yUpper);
        Interval x(xLower, xUpper);
        Interval y = tan(x);
        CAPTURE(y);
        REQUIRE((y.lowerBound() - yLower) == Zero());
        REQUIRE((y.upperBound() - yUpper) == Zero());
    };

    auto testInfinite = [] (double xLower, double xUpper) {
        CAPTURE(xLower);
        CAPTURE(xUpper);
        Interval x(xLower, xUpper);
        Interval y = tan(x);
        CAPTURE(y);
        REQUIRE(y.lowerBound() < -DBL_MAX);
        REQUIRE(y.upperBound() > DBL_MAX);
    };

    test(-0.5, 0.5, tan(-0.5), tan(0.5));
    testInfinite(1.25, 2.5);
    test(4.0, 4.1, tan(4.0), tan(4.1));
    testInfinite(4.0, 6.0);
    testInfinite(4.0, 8.0);
    testInfinite(-6.0, -4.0);
    testInfinite(-1.0, 3.5); 
}
