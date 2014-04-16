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
    void testLayout() {
        static_assert(sizeof(Matrix1x1) == sizeof(double), "Matrix1x1 is not compact");
        static_assert(sizeof(RowMatrix1x3) == 3 * sizeof(double), "RowMatrix1x3 is not compact");
        static_assert(sizeof(ColMatrix3x1) == 3 * sizeof(double), "ColMatrix3x1 is not compact");
        static_assert(sizeof(Matrix3x3) == 9 * sizeof(double), "Matrix3x3 is not compact");

        static_assert(
            sizeof(IntervalMatrix1x1) == sizeof(Interval),
            "IntervalMatrix1x1 is not compact"
        );
        static_assert(
            sizeof(IntervalRowMatrix1x3) == 3 * sizeof(Interval),
            "IntervalRowMatrix1x3 is not compact"
        );
        static_assert(
            sizeof(IntervalColMatrix3x1) == 3 * sizeof(Interval),
            "IntervalColMatrix3x1 is not compact"
        );
        static_assert(
            sizeof(IntervalMatrix3x3) == 9 * sizeof(Interval),
            "IntervalMatrix3x3 is not compact"
        );
    }

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

    void testDynamicMatrixConversion1() {
        Matrix2x3 a;
        a(0, 0) = 1;
        a(1, 0) = 2;
        a(0, 1) = 3;
        a(1, 1) = 4;
        a(0, 2) = 5;
        a(1, 2) = 6;

        MatrixXxX b = a;
        TS_ASSERT_EQUALS(b.rows(), 2);
        TS_ASSERT_EQUALS(b.cols(), 3);
        TS_ASSERT_EQUALS(b(0, 0), 1);
        TS_ASSERT_EQUALS(b(1, 0), 2);
        TS_ASSERT_EQUALS(b(0, 1), 3);
        TS_ASSERT_EQUALS(b(1, 1), 4);
        TS_ASSERT_EQUALS(b(0, 2), 5);
        TS_ASSERT_EQUALS(b(1, 2), 6);
    }

    void testDynamicMatrixConversion2() {
        MatrixXxX a(2, 2);
        a(0, 0) = 1;
        a(1, 0) = 2;
        a(0, 1) = 3;
        a(1, 1) = 4;

        Matrix2x2 b = a;
        TS_ASSERT_EQUALS(b(0, 0), 1);
        TS_ASSERT_EQUALS(b(1, 0), 2);
        TS_ASSERT_EQUALS(b(0, 1), 3);
        TS_ASSERT_EQUALS(b(1, 1), 4);
    }

    void testDynamicMatrixRow() {
        MatrixXxX matrix(3, 11);
        for (int i = 0; i <= 10; ++i) {
            matrix(0, i) = 1 + i / 10.0;
            matrix(1, i) = 2 + i / 10.0;
            matrix(2, i) = 3 + i / 10.0;
        }

        RowMatrix1xX row = matrix.row(1);
        for (int i = 0; i <= 10; ++i) {
            TS_ASSERT(row(i) - (2 + i / 10.0) == Zero());
        }
    }

    void testDynamicMatrixInversion() {
        MatrixXxX matrix(3, 3);
        matrix(0, 0) = 1;
        matrix(0, 1) = 1;
        matrix(1, 1) = 1;
        matrix(0, 2) = 1;
        matrix(1, 2) = 1;
        matrix(2, 2) = 1;

        MatrixXxX inverse = matrix.inverse();
        TS_ASSERT_EQUALS(inverse.rows(), 3);
        TS_ASSERT_EQUALS(inverse.cols(), 3);

        MatrixXxX identity = inverse * matrix;
        TS_ASSERT_EQUALS(identity.rows(), 3);
        TS_ASSERT_EQUALS(identity.cols(), 3);
        TS_ASSERT(identity.isIdentity());
    }

    void testDynamicMap() {
        MatrixXxX matrix(3, 3);
        for (int index = 0; index < 9; ++index) {
            matrix(index) = index;
        }
        RowMatrix1x3 mappedRow = matrix.row(1).map(
            [] (double coeff) {
                return 2 * coeff;
            }
        );
        TS_ASSERT(mappedRow(0) - 2 == Zero());
        TS_ASSERT(mappedRow(1) - 8 == Zero());
        TS_ASSERT(mappedRow(2) - 14 == Zero());
    }

    void testDynamicBinaryMap() {
        MatrixXxX firstMatrix(2, 3);
        for (int index = 0; index < 6; ++index) {
            firstMatrix(index) = index;
        }
        
        MatrixXxX secondMatrix(2, 3);
        for (int index = 0; index < 6; ++index) {
            secondMatrix(index) = 2 * index;
        }

        Matrix2x3 meanMatrix = firstMatrix.binaryMap(
            secondMatrix,
            [] (double firstCoeff, double secondCoeff) {
                return firstCoeff + (secondCoeff - firstCoeff) / 2;
            }
        );
        for (int index = 0; index < 6; ++index) {
            TS_ASSERT(meanMatrix(index) - 1.5 * index == Zero());
        }
    }

    void testDynamicProduct() {
        // 1 3 5
        // 2 4 6
        MatrixXxX firstMatrix(2, 3);
        for (int index = 0; index < 6; ++index) {
            firstMatrix(index) = index + 1;
        }

        // 1 4
        // 2 5
        // 3 6
        Matrix3x2 secondMatrix;
        for (int index = 0; index < 6; ++index) {
            secondMatrix(index) = index + 1;
        }

        // 22 49
        // 28 64
        MatrixXxX result = firstMatrix * secondMatrix;
        TS_ASSERT_EQUALS(result.rows(), 2);
        TS_ASSERT_EQUALS(result.cols(), 2);
        TS_ASSERT(result(0, 0) - 22 == Zero());
        TS_ASSERT(result(1, 0) - 28 == Zero());
        TS_ASSERT(result(0, 1) - 49 == Zero());
        TS_ASSERT(result(1, 1) - 64 == Zero());
    }
};
