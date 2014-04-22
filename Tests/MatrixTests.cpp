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

#include <catch/catch.hpp>

#include <typeinfo>
#include <vector>

using namespace opensolid;

TEST_CASE("Compact layout") {
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

TEST_CASE("2D matrix inversion") {
    for (int i = 0; i < 1000; ++i) {
        Matrix2x2 matrix = Matrix2x2::Random();
        if (matrix.determinant() != Zero(1e-3)) {
            Matrix2x2 inverse = matrix.inverse();
            REQUIRE((matrix * inverse).isIdentity());
            REQUIRE((inverse * matrix).isIdentity());
        }
    }
}

TEST_CASE("3D matrix inversion") {
    for (int i = 0; i < 1000; ++i) {
        Matrix3x3 matrix = Matrix3x3::Random();
        if (matrix.determinant() != Zero(1e-3)) {
            Matrix3x3 inverse = matrix.inverse();
            REQUIRE((matrix * inverse).isIdentity());
            REQUIRE((inverse * matrix).isIdentity());
        }
    }
}

TEST_CASE("2D Interval matrix inversion") {
    for (int i = 0; i < 1000; ++i) {
        IntervalMatrix2x2 matrix = IntervalMatrix2x2::Random();
        IntervalMatrix2x2 inverse = matrix.inverse();
        auto containsFunction = [] (Interval testComponent, double identityComponent) -> bool {
            return testComponent.contains(identityComponent);
        };
        REQUIRE((matrix * inverse).binaryAll(Matrix2x2::Identity(), containsFunction));
        REQUIRE((inverse * matrix).binaryAll(Matrix2x2::Identity(), containsFunction));
    }
}

TEST_CASE("3D Interval matrix inversion") {
    for (int i = 0; i < 1000; ++i) {
        IntervalMatrix3x3 matrix = IntervalMatrix3x3::Random();
        IntervalMatrix3x3 inverse = matrix.inverse();
        auto containsFunction = [] (Interval testComponent, double identityComponent) -> bool {
            return testComponent.contains(identityComponent);
        };
        REQUIRE((matrix * inverse).binaryAll(Matrix3x3::Identity(), containsFunction));
        REQUIRE((inverse * matrix).binaryAll(Matrix3x3::Identity(), containsFunction));
    }
}

TEST_CASE("Matrix folding") {
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
    REQUIRE(product == 60);
    REQUIRE(product == values.prod());
}

TEST_CASE("Binary matrix folding") {
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
    REQUIRE(containmentCount == 2);
}

TEST_CASE("Coefficient-wise squaring") {
    SECTION("Double matrices") {  
        ColMatrix2x1 doubleMatrix;
        doubleMatrix(0) = -1;
        doubleMatrix(1) = 3;

        ColMatrix2x1 squaredDoubles = doubleMatrix.cwiseSquared();
        REQUIRE(squaredDoubles(0) == 1);
        REQUIRE(squaredDoubles(1) == 9);
    }

    SECTION("Interval matrices") {
        IntervalColMatrix2x1 intervalMatrix;
        intervalMatrix(0) = Interval(2, 3);
        intervalMatrix(1) = Interval(-1, 1);

        IntervalColMatrix2x1 squaredIntervals = intervalMatrix.cwiseSquared();
        REQUIRE(squaredIntervals(0).lowerBound() == 4);
        REQUIRE(squaredIntervals(0).upperBound() == 9);
        REQUIRE(squaredIntervals(1).lowerBound() == 0);
        REQUIRE(squaredIntervals(1).upperBound() == 1);
    }
}

TEST_CASE("Coefficient-wise quotient") {
    RowMatrix1x2 doubleMatrix;
    doubleMatrix(0) = 1;
    doubleMatrix(1) = 2;

    IntervalRowMatrix1x2 intervalMatrix;
    intervalMatrix(0) = Interval(2, 3);
    intervalMatrix(1) = Interval(4, 5);
    
    IntervalRowMatrix1x2 quotients = doubleMatrix.cwiseQuotient(intervalMatrix);
    REQUIRE((quotients(0).lowerBound() - 1.0 / 3.0) == Zero());
    REQUIRE((quotients(0).upperBound() - 1.0 / 2.0) == Zero());
    REQUIRE((quotients(1).lowerBound() - 2.0 / 5.0) == Zero());
    REQUIRE((quotients(1).upperBound() - 1.0 / 2.0) == Zero());
}

TEST_CASE("Matrix product") {
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

    REQUIRE((c(0, 0) - 22) == Zero());
    REQUIRE((c(1, 0) - 28) == Zero());
    REQUIRE((c(0, 1) - 49) == Zero());
    REQUIRE((c(1, 1) - 64) == Zero());
}

TEST_CASE("Static/dynamic matrix conversion") {
    SECTION("Static to dynamic") {
        Matrix2x3 a;
        a(0, 0) = 1;
        a(1, 0) = 2;
        a(0, 1) = 3;
        a(1, 1) = 4;
        a(0, 2) = 5;
        a(1, 2) = 6;

        MatrixXxX b = a;
        REQUIRE(b.numRows() == 2);
        REQUIRE(b.numColumns() == 3);
        REQUIRE(b(0, 0) == 1);
        REQUIRE(b(1, 0) == 2);
        REQUIRE(b(0, 1) == 3);
        REQUIRE(b(1, 1) == 4);
        REQUIRE(b(0, 2) == 5);
        REQUIRE(b(1, 2) == 6);
    }

    SECTION("Dynamic to static") {
        MatrixXxX a(2, 2);
        a(0, 0) = 1;
        a(1, 0) = 2;
        a(0, 1) = 3;
        a(1, 1) = 4;

        Matrix2x2 b = a;
        REQUIRE(b(0, 0) == 1);
        REQUIRE(b(1, 0) == 2);
        REQUIRE(b(0, 1) == 3);
        REQUIRE(b(1, 1) == 4);
    }
}

TEST_CASE("Dynamic matrix row access") {
    MatrixXxX matrix(3, 11);
    for (int i = 0; i <= 10; ++i) {
        matrix(0, i) = 1 + i / 10.0;
        matrix(1, i) = 2 + i / 10.0;
        matrix(2, i) = 3 + i / 10.0;
    }

    RowMatrix1xX row = matrix.row(1);
    for (int i = 0; i <= 10; ++i) {
        REQUIRE((row(i) - (2 + i / 10.0)) == Zero());
    }
}

TEST_CASE("Dynamic matrix inversion") {
    MatrixXxX matrix(3, 3);
    matrix(0, 0) = 1;
    matrix(0, 1) = 1;
    matrix(1, 1) = 1;
    matrix(0, 2) = 1;
    matrix(1, 2) = 1;
    matrix(2, 2) = 1;

    MatrixXxX inverse = matrix.inverse();
    REQUIRE(inverse.numRows() == 3);
    REQUIRE(inverse.numColumns() == 3);

    MatrixXxX identity = inverse * matrix;
    REQUIRE(identity.numRows() == 3);
    REQUIRE(identity.numColumns() == 3);
    REQUIRE(identity.isIdentity());
}

TEST_CASE("Dynamic matrix map") {
    MatrixXxX matrix(3, 3);
    for (int index = 0; index < 9; ++index) {
        matrix(index) = index;
    }
    RowMatrix1x3 mappedRow = matrix.row(1).map(
        [] (double coeff) {
            return 2 * coeff;
        }
    );
    REQUIRE((mappedRow(0) - 2) == Zero());
    REQUIRE((mappedRow(1) - 8) == Zero());
    REQUIRE((mappedRow(2) - 14) == Zero());
}

TEST_CASE("Dynamic matrix binary map") {
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
        REQUIRE((meanMatrix(index) - 1.5 * index) == Zero());
    }
}

TEST_CASE("Dynamic matrix product") {
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
    REQUIRE(result.numRows() == 2);
    REQUIRE(result.numColumns() == 2);
    REQUIRE((result(0, 0) - 22) == Zero());
    REQUIRE((result(1, 0) - 28) == Zero());
    REQUIRE((result(0, 1) - 49) == Zero());
    REQUIRE((result(1, 1) - 64) == Zero());
}

TEST_CASE("Block assignment") {
    Matrix3x3 matrix;
    matrix.block<2, 2>(1, 1) = Matrix2x2::Ones();
    REQUIRE(matrix(0, 0) == 0);
    REQUIRE(matrix(1, 0) == 0);
    REQUIRE(matrix(2, 0) == 0);
    REQUIRE(matrix(0, 1) == 0);
    REQUIRE(matrix(1, 1) == 1);
    REQUIRE(matrix(2, 1) == 1);
    REQUIRE(matrix(0, 2) == 0);
    REQUIRE(matrix(1, 2) == 1);
    REQUIRE(matrix(2, 2) == 1);
}

TEST_CASE("Dynamic matrix block assignment") {
    MatrixXxX matrix(10, 10);
    matrix.block(2, 3, 4, 5).setOnes();
    for (int colIndex = 0; colIndex < 10; ++colIndex) {
        for (int rowIndex = 0; rowIndex < 10; ++rowIndex) {
            if (rowIndex >= 2 && rowIndex < 6 && colIndex >= 3 && colIndex < 8) {
                REQUIRE(matrix(rowIndex, colIndex) == 1);
            } else {
                REQUIRE(matrix(rowIndex, colIndex) == 0);
            }
        }
    }
}

TEST_CASE("Block-to-block assignment") {
    Matrix3x3 matrix;
    matrix.block<2, 2>(0, 1) = Matrix3x3::Identity().block(1, 0, 2, 2);
    for (int colIndex = 0; colIndex < 3; ++colIndex) {
        for (int rowIndex = 0; rowIndex < 3; ++rowIndex) {
            if (rowIndex == 0 && colIndex == 2) {
                REQUIRE(matrix(rowIndex, colIndex) == 1);
            } else {
                REQUIRE(matrix(rowIndex, colIndex) == 0);
            }
        }
    }
}
