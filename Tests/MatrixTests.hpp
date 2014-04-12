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
        ColMatrix3x1 values;
        values(0) = 3;
        values(1) = 4;
        values(2) = 5;

        double product = values.fold(
            1.0,
            [] (double result, double value) -> double {
                return result * value;
            }
        );
        TS_ASSERT_EQUALS(product, 60);
        TS_ASSERT_EQUALS(product, values.prod());
    }

    void testBinaryFold() {
        ColMatrix3x1 values;
        values(0) = 10;
        values(1) = 20;
        values(2) = 30;

        IntervalColMatrix3x1 intervals;
        intervals(0) = Interval(9, 11);
        intervals(1) = Interval(18, 19);
        intervals(2) = Interval(29, 31);
        
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
        ColMatrix2x1 doubleMatrix;
        doubleMatrix(0) = -1;
        doubleMatrix(1) = 3;

        ColMatrix2x1 squaredDoubles = doubleMatrix.cwiseSquared();
        TS_ASSERT_EQUALS(squaredDoubles(0), 1);
        TS_ASSERT_EQUALS(squaredDoubles(1), 9);

        IntervalColMatrix2x1 intervalMatrix;
        intervalMatrix(0) = Interval(2, 3);
        intervalMatrix(1) = Interval(-1, 1);

        IntervalColMatrix2x1 squaredIntervals = intervalMatrix.cwiseSquared();
        TS_ASSERT_EQUALS(squaredIntervals(0).lowerBound(), 4);
        TS_ASSERT_EQUALS(squaredIntervals(0).upperBound(), 9);
        TS_ASSERT_EQUALS(squaredIntervals(1).lowerBound(), 0);
        TS_ASSERT_EQUALS(squaredIntervals(1).upperBound(), 1);
    }

    void testCwiseQuotient() {
        RowMatrix1x2 doubleMatrix;
        doubleMatrix(0) = 1;
        doubleMatrix(1) = 2;

        IntervalRowMatrix1x2 intervalMatrix;
        intervalMatrix(0) = Interval(2, 3);
        intervalMatrix(1) = Interval(4, 5);
        
        IntervalRowMatrix1x2 quotients = doubleMatrix.cwiseQuotient(intervalMatrix);
        TS_ASSERT(quotients(0).lowerBound() - 1.0 / 3.0 == Zero());
        TS_ASSERT(quotients(0).upperBound() - 1.0 / 2.0 == Zero());
        TS_ASSERT(quotients(1).lowerBound() - 2.0 / 5.0 == Zero());
        TS_ASSERT(quotients(1).upperBound() - 1.0 / 2.0 == Zero());
    }

    void testMatrixProduct() {
        // 1 3 5
        // 2 4 6
        Matrix2x3 a;
        a(0, 0) = 1;
        a(1, 0) = 2;
        a(0, 1) = 3;
        a(1, 1) = 4;
        a(0, 2) = 5;
        a(1, 2) = 6;

        // 1 4
        // 2 5
        // 3 6
        Matrix3x2 b;
        b(0, 0) = 1;
        b(1, 0) = 2;
        b(2, 0) = 3;
        b(0, 1) = 4;
        b(1, 1) = 5;
        b(2, 1) = 6;

        // 22 49
        // 28 64
        Matrix2x2 c = a * b;

        TS_ASSERT(c(0, 0) - 22 == Zero());
        TS_ASSERT(c(1, 0) - 28 == Zero());
        TS_ASSERT(c(0, 1) - 49 == Zero());
        TS_ASSERT(c(1, 1) - 64 == Zero());
    }
};
