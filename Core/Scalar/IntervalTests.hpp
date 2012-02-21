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

#include <cxxtest/TestSuite.h>

#include <OpenSolid/Core/Scalar/Interval.hpp>
#include <OpenSolid/Core/Domain/Domain.hpp>

using namespace OpenSolid;

class IntervalTests : public CxxTest::TestSuite
{
public:
    void testInterval() {
        Interval five(5.0);
        TS_ASSERT_EQUALS(five.lower(), 5.0);
        TS_ASSERT_EQUALS(five.upper(), 5.0);
        TS_ASSERT_EQUALS(five.width(), 0.0);
        TS_ASSERT_EQUALS(five.median(), 5.0);
    }

    void testScalarNegation() {
        Interval two_three(2.0, 3.0);
        Interval negated = -two_three;
        TS_ASSERT_EQUALS(negated.lower(), -3.0);
        TS_ASSERT_EQUALS(negated.upper(), -2.0);
        TS_ASSERT_EQUALS(negated.width(), 1.0);
        TS_ASSERT_EQUALS(negated.median(), -2.5);

        Interval cancelled = -negated;
        TS_ASSERT_EQUALS(cancelled.lower(), 2.0);
        TS_ASSERT_EQUALS(cancelled.upper(), 3.0);
        TS_ASSERT_EQUALS(cancelled.width(), 1.0);
        TS_ASSERT_EQUALS(cancelled.median(), 2.5);
    }

    void testScalarAddition() {
        Interval two_three(2.0, 3.0);
        Interval constant_sum = 1.0 + two_three;
        TS_ASSERT_EQUALS(constant_sum.lower(), 3.0);
        TS_ASSERT_EQUALS(constant_sum.upper(), 4.0);
    }

    void testScalarSubtraction() {
        Interval two_three(2.0, 3.0);
        Interval constant_difference = 1.0 - two_three;
        TS_ASSERT_EQUALS(constant_difference.lower(), -2.0);
        TS_ASSERT_EQUALS(constant_difference.upper(), -1.0);
    }

    void testSquare() {
        Interval two_three(2.0, 3.0);
        Interval four_nine = two_three.squared();
        TS_ASSERT_EQUALS(four_nine.lower(), 4.0);
        TS_ASSERT_EQUALS(four_nine.upper(), 9.0);
    }
    
    void testBisected() {
        Interval x(4, 5);
        std::pair<Interval, Interval> bisected = x.bisected();
        TS_ASSERT_EQUALS(bisected.first.lower(), 4);
        TS_ASSERT_EQUALS(bisected.first.upper(), 4.5);
        TS_ASSERT_EQUALS(bisected.second.lower(), 4.5);
        TS_ASSERT_EQUALS(bisected.second.upper(), 5);
    }

    void testInterpolated() {
        Interval x(6, 10);
        TS_ASSERT(x.interpolated(0.5) - 8 == Zero());
        Interval interpolated = x.interpolated(Interval(0.25, 0.75));
        TS_ASSERT(interpolated.lower() - 7 == Zero());
        TS_ASSERT(interpolated.upper() - 9 == Zero());
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
        TS_ASSERT_EQUALS(clamped.lower(), 2);
        TS_ASSERT_EQUALS(clamped.upper(), 2);
        clamped = interval.clamp(Interval(1, 3));
        TS_ASSERT_EQUALS(clamped.lower(), 2);
        TS_ASSERT_EQUALS(clamped.upper(), 3);
        clamped = interval.clamp(Interval(2.5, 3.5));
        TS_ASSERT_EQUALS(clamped.lower(), 2.5);
        TS_ASSERT_EQUALS(clamped.upper(), 3.5);
    }

    void testConversion() {
        Interval interval(2, 3);
        Domain domain(interval);
        Interval converted = domain.as<Interval>();
        TS_ASSERT_EQUALS(converted.lower(), 2);
        TS_ASSERT_EQUALS(converted.upper(), 3);
    }

    void testRandom() {
        Interval interval(-2, 3);
        for (int i = 0; i < 100; ++i) {
            double random = interval.random();
            TS_ASSERT_LESS_THAN_EQUALS(interval.lower(), random);
            TS_ASSERT_LESS_THAN_EQUALS(random, interval.upper());
        }
    }

    void testSerialization() {
        Interval original(2, 3);
        Serialization<Interval> serializer;
        Deserialization<Interval> deserializer;
        std::string serialized = serializer(original);
        Interval final = deserializer(serialized);
        TS_ASSERT_EQUALS(original.lower(), final.lower());
        TS_ASSERT_EQUALS(original.upper(), final.upper());
    }
};
