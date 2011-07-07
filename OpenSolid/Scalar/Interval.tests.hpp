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

#include <OpenSolid/Scalar/Interval.hpp>

using namespace OpenSolid;

class IntervalTestSuite : public CxxTest::TestSuite
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
        Interval four_nine = two_three.squaredNorm();
        TS_ASSERT_EQUALS(four_nine.lower(), 4.0);
        TS_ASSERT_EQUALS(four_nine.upper(), 9.0);
    }
    
    void testBisected() {
        Interval x(4, 5);
        std::pair<Interval, Interval> bisected = x.bisected();
        TS_ASSERT_EQUALS(bisected.first, Interval(4.0, 4.5));
        TS_ASSERT_EQUALS(bisected.second, Interval(4.5, 5.0));
    }
};
