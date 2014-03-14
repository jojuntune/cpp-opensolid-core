/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
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
#include <OpenSolid/Core/Matrix.hpp>

#include <cxxtest/TestSuite.h>

#include <typeinfo>
#include <vector>

using namespace opensolid;

class MatrixTests : public CxxTest::TestSuite
{
public:
    void testInversion2d() {
        for (int i = 0; i < 1000; ++i) {
            Matrix2x2 matrix = Matrix2x2::Random();
            if (matrix.determinant() != Zero(1e-3)) {
                Matrix2x2 inverse = matrix.inverse();
                TS_ASSERT((matrix * inverse).isIdentity());
                TS_ASSERT((inverse * matrix).isIdentity());
            }
        }
    }

    void testInversion3d() {
        for (int i = 0; i < 1000; ++i) {
            Matrix3x3 matrix = Matrix3x3::Random();
            if (matrix.determinant() != Zero(1e-3)) {
                Matrix3x3 inverse = matrix.inverse();
                TS_ASSERT((matrix * inverse).isIdentity());
                TS_ASSERT((inverse * matrix).isIdentity());
            }
        }
    }

    void testIntervalInversion2d() {
        for (int i = 0; i < 1000; ++i) {
            IntervalMatrix2x2 matrix = IntervalMatrix2x2::Random();
            IntervalMatrix2x2 inverse = matrix.inverse();
            auto containsFunction = [] (Interval testComponent, double identityComponent) -> bool {
                return testComponent.contains(identityComponent);
            };
            TS_ASSERT((matrix * inverse).binaryAll(Matrix2x2::Identity(), containsFunction));
            TS_ASSERT((inverse * matrix).binaryAll(Matrix2x2::Identity(), containsFunction));
        }
    }

    void testIntervalInversion3d() {
        for (int i = 0; i < 1000; ++i) {
            IntervalMatrix3x3 matrix = IntervalMatrix3x3::Random();
            IntervalMatrix3x3 inverse = matrix.inverse();
            auto containsFunction = [] (Interval testComponent, double identityComponent) -> bool {
                return testComponent.contains(identityComponent);
            };
            TS_ASSERT((matrix * inverse).binaryAll(Matrix3x3::Identity(), containsFunction));
            TS_ASSERT((inverse * matrix).binaryAll(Matrix3x3::Identity(), containsFunction));
        }
    }

    void testFold() {
        Matrix3x1 values(3, 4, 5);
        double product = values.fold(
            1.0,
            [] (double result, double value) -> double {
                return result * value;
            }
        );
        TS_ASSERT_EQUALS(product, 60);
        TS_ASSERT_EQUALS(product, values.product());
    }

    void testBinaryFold() {
        Matrix3x1 values(10, 20, 30);
        IntervalMatrix3x1 intervals(Interval(9, 11), Interval(18, 19), Interval(29, 31));
        int containmentCount = intervals.binaryFold(
            values,
            0,
            [] (int result, Interval interval, double value) -> int {
                return result + (interval.contains(value) ? 1 : 0);
            }
        );
        TS_ASSERT_EQUALS(containmentCount, 2);
    }

    void testCwiseSquared() {
        Matrix2x1 doubleMatrix(-1, 3);
        Matrix2x1 squaredDoubles = doubleMatrix.cwiseSquared();
        TS_ASSERT_EQUALS(squaredDoubles(0), 1);
        TS_ASSERT_EQUALS(squaredDoubles(1), 9);

        IntervalMatrix2x1 intervalMatrix(Interval(2, 3), Interval(-1, 1));
        IntervalMatrix2x1 squaredIntervals = intervalMatrix.cwiseSquared();
        TS_ASSERT_EQUALS(squaredIntervals(0).lowerBound(), 4);
        TS_ASSERT_EQUALS(squaredIntervals(0).upperBound(), 9);
        TS_ASSERT_EQUALS(squaredIntervals(1).lowerBound(), 0);
        TS_ASSERT_EQUALS(squaredIntervals(1).upperBound(), 1);
    }

    void testCwiseQuotient() {
        Matrix1x2 doubleMatrix(1, 2);
        IntervalMatrix1x2 intervalMatrix(Interval(2, 3), Interval(4, 5));
        IntervalMatrix1x2 quotients = doubleMatrix.cwiseQuotient(intervalMatrix);
        TS_ASSERT(quotients(0).lowerBound() - 1.0 / 3.0 == Zero());
        TS_ASSERT(quotients(0).upperBound() - 1.0 / 2.0 == Zero());
        TS_ASSERT(quotients(1).lowerBound() - 2.0 / 5.0 == Zero());
        TS_ASSERT(quotients(1).upperBound() - 1.0 / 2.0 == Zero());
    }

    void testMatrixProduct() {
        // 1 3 5
        // 2 4 6
        Matrix2x3 a = Matrix2x3::FromColumns(
            Matrix2x1(1, 2),
            Matrix2x1(3, 4),
            Matrix2x1(5, 6)
        );

        // 1 4
        // 2 5
        // 3 6
        Matrix3x2 b = Matrix3x2::FromColumns(
            Matrix3x1(1, 2, 3),
            Matrix3x1(4, 5, 6)
        );

        // 22 49
        // 28 64
        Matrix2x2 c = a * b;

        TS_ASSERT(c(0, 0) - 22 == Zero());
        TS_ASSERT(c(1, 0) - 28 == Zero());
        TS_ASSERT(c(0, 1) - 49 == Zero());
        TS_ASSERT(c(1, 1) - 64 == Zero());
    }
};
