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
