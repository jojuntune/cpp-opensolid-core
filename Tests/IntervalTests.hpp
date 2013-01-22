/*****************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                     *
 *   ian.e.mackenzie@gmail.com                                               *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************/

#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/Domain.hpp>

#include <cxxtest/TestSuite.h>

using namespace opensolid;

class IntervalTests : public CxxTest::TestSuite
{
public:
    void testInterval() {
        Interval five(5.0);
        TS_ASSERT_EQUALS(five.lowerBound(), 5.0);
        TS_ASSERT_EQUALS(five.upperBound(), 5.0);
        TS_ASSERT_EQUALS(five.width(), 0.0);
        TS_ASSERT_EQUALS(five.median(), 5.0);
    }

    void testScalarNegation() {
        Interval two_three(2.0, 3.0);
        Interval negated = -two_three;
        TS_ASSERT_EQUALS(negated.lowerBound(), -3.0);
        TS_ASSERT_EQUALS(negated.upperBound(), -2.0);
        TS_ASSERT_EQUALS(negated.width(), 1.0);
        TS_ASSERT_EQUALS(negated.median(), -2.5);

        Interval cancelled = -negated;
        TS_ASSERT_EQUALS(cancelled.lowerBound(), 2.0);
        TS_ASSERT_EQUALS(cancelled.upperBound(), 3.0);
        TS_ASSERT_EQUALS(cancelled.width(), 1.0);
        TS_ASSERT_EQUALS(cancelled.median(), 2.5);
    }

    void testScalarAddition() {
        Interval two_three(2.0, 3.0);
        Interval constant_sum = 1.0 + two_three;
        TS_ASSERT_EQUALS(constant_sum.lowerBound(), 3.0);
        TS_ASSERT_EQUALS(constant_sum.upperBound(), 4.0);
    }

    void testScalarSubtraction() {
        Interval two_three(2.0, 3.0);
        Interval constant_difference = 1.0 - two_three;
        TS_ASSERT_EQUALS(constant_difference.lowerBound(), -2.0);
        TS_ASSERT_EQUALS(constant_difference.upperBound(), -1.0);
    }

    void testSquare() {
        Interval two_three(2.0, 3.0);
        Interval four_nine = two_three.squared();
        TS_ASSERT_EQUALS(four_nine.lowerBound(), 4.0);
        TS_ASSERT_EQUALS(four_nine.upperBound(), 9.0);
    }
    
    void testBisected() {
        Interval x(4, 5);
        std::pair<Interval, Interval> bisected = x.bisected();
        TS_ASSERT_EQUALS(bisected.first.lowerBound(), 4);
        TS_ASSERT_EQUALS(bisected.first.upperBound(), 4.5);
        TS_ASSERT_EQUALS(bisected.second.lowerBound(), 4.5);
        TS_ASSERT_EQUALS(bisected.second.upperBound(), 5);
    }

    void testInterpolated() {
        Interval x(6, 10);
        TS_ASSERT(x.interpolated(0.5) - 8 == Zero());
        Interval interpolated = x.interpolated(Interval(0.25, 0.75));
        TS_ASSERT(interpolated.lowerBound() - 7 == Zero());
        TS_ASSERT(interpolated.upperBound() - 9 == Zero());
    }

    void testClamp() {
        Interval interval(2, 4);
        TS_ASSERT_EQUALS(interval.clamp(1), 2);
        TS_ASSERT_EQUALS(interval.clamp(2), 2);
        TS_ASSERT_EQUALS(interval.clamp(3), 3);
        TS_ASSERT_EQUALS(interval.clamp(4), 4);
        TS_ASSERT_EQUALS(interval.clamp(5), 4);
        Interval clamped;
        clamped = interval.clamp(Interval(0, 1));
        TS_ASSERT_EQUALS(clamped.lowerBound(), 2);
        TS_ASSERT_EQUALS(clamped.upperBound(), 2);
        clamped = interval.clamp(Interval(1, 3));
        TS_ASSERT_EQUALS(clamped.lowerBound(), 2);
        TS_ASSERT_EQUALS(clamped.upperBound(), 3);
        clamped = interval.clamp(Interval(2.5, 3.5));
        TS_ASSERT_EQUALS(clamped.lowerBound(), 2.5);
        TS_ASSERT_EQUALS(clamped.upperBound(), 3.5);
    }

    void testConversion() {
        Interval interval(2, 3);
        Domain domain(interval);
        Interval converted = domain.as<Interval>();
        TS_ASSERT_EQUALS(converted.lowerBound(), 2);
        TS_ASSERT_EQUALS(converted.upperBound(), 3);
    }

    void testRandom() {
        Interval interval(-2, 3);
        for (int i = 0; i < 100; ++i) {
            double random = interval.random();
            TS_ASSERT_LESS_THAN_EQUALS(interval.lowerBound(), random);
            TS_ASSERT_LESS_THAN_EQUALS(random, interval.upperBound());
        }
    }
};
