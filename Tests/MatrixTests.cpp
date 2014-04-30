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
#include <OpenSolid/Core/Matrix.hpp>

#include <catch/catch.hpp>

#include <typeinfo>
#include <vector>

using namespace opensolid;

TEST_CASE("Compact layout") {
    static_assert(sizeof(Matrix1d) == sizeof(double), "Matrix1d is not compact");
    static_assert(sizeof(RowMatrix3d) == 3 * sizeof(double), "RowMatrix3d is not compact");
    static_assert(sizeof(ColumnMatrix3d) == 3 * sizeof(double), "ColumnMatrix3d is not compact");
    static_assert(sizeof(Matrix3d) == 9 * sizeof(double), "Matrix3d is not compact");

    static_assert(
        sizeof(IntervalMatrix1d) == sizeof(Interval),
        "IntervalMatrix1d is not compact"
    );
    static_assert(
        sizeof(IntervalRowMatrix3d) == 3 * sizeof(Interval),
        "IntervalRowMatrix3d is not compact"
    );
    static_assert(
        sizeof(IntervalColumnMatrix3d) == 3 * sizeof(Interval),
        "IntervalColumnMatrix3d is not compact"
    );
    static_assert(
        sizeof(IntervalMatrix3d) == 9 * sizeof(Interval),
        "IntervalMatrix3d is not compact"
    );
}

TEST_CASE("2D matrix inversion") {
    for (int i = 0; i < 1000; ++i) {
        Matrix2d matrix = Matrix2d::Random();
        if (matrix.determinant() != Zero(1e-3)) {
            Matrix2d inverse = matrix.inverse();
            REQUIRE((matrix * inverse).isIdentity());
            REQUIRE((inverse * matrix).isIdentity());
        }
    }
}

TEST_CASE("3D matrix inversion") {
    for (int i = 0; i < 1000; ++i) {
        Matrix3d matrix = Matrix3d::Random();
        if (matrix.determinant() != Zero(1e-3)) {
            Matrix3d inverse = matrix.inverse();
            REQUIRE((matrix * inverse).isIdentity());
            REQUIRE((inverse * matrix).isIdentity());
        }
    }
}

TEST_CASE("2D Interval matrix inversion") {
    for (int i = 0; i < 1000; ++i) {
        IntervalMatrix2d matrix = IntervalMatrix2d::Random();
        IntervalMatrix2d inverse = matrix.inverse();
        auto containsFunction = [] (Interval testComponent, double identityComponent) -> bool {
            return testComponent.contains(identityComponent);
        };
        REQUIRE((matrix * inverse).binaryAll(Matrix2d::Identity(), containsFunction));
        REQUIRE((inverse * matrix).binaryAll(Matrix2d::Identity(), containsFunction));
    }
}

TEST_CASE("3D Interval matrix inversion") {
    for (int i = 0; i < 1000; ++i) {
        IntervalMatrix3d matrix = IntervalMatrix3d::Random();
        IntervalMatrix3d inverse = matrix.inverse();
        auto containsFunction = [] (Interval testComponent, double identityComponent) -> bool {
            return testComponent.contains(identityComponent);
        };
        REQUIRE((matrix * inverse).binaryAll(Matrix3d::Identity(), containsFunction));
        REQUIRE((inverse * matrix).binaryAll(Matrix3d::Identity(), containsFunction));
    }
}

TEST_CASE("Matrix folding") {
    ColumnMatrix3d values;
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
    REQUIRE(product == values.product());
}

TEST_CASE("Binary matrix folding") {
    ColumnMatrix3d values;
    values(0) = 10;
    values(1) = 20;
    values(2) = 30;

    IntervalColumnMatrix3d intervals;
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
        ColumnMatrix2d doubleMatrix;
        doubleMatrix(0) = -1;
        doubleMatrix(1) = 3;

        ColumnMatrix2d squaredDoubles = doubleMatrix.cwiseSquared();
        REQUIRE(squaredDoubles(0) == 1);
        REQUIRE(squaredDoubles(1) == 9);
    }

    SECTION("Interval matrices") {
        IntervalColumnMatrix2d intervalMatrix;
        intervalMatrix(0) = Interval(2, 3);
        intervalMatrix(1) = Interval(-1, 1);

        IntervalColumnMatrix2d squaredIntervals = intervalMatrix.cwiseSquared();
        REQUIRE(squaredIntervals(0).lowerBound() == 4);
        REQUIRE(squaredIntervals(0).upperBound() == 9);
        REQUIRE(squaredIntervals(1).lowerBound() == 0);
        REQUIRE(squaredIntervals(1).upperBound() == 1);
    }
}

TEST_CASE("Coefficient-wise quotient") {
    RowMatrix2d doubleMatrix;
    doubleMatrix(0) = 1;
    doubleMatrix(1) = 2;

    IntervalRowMatrix2d intervalMatrix;
    intervalMatrix(0) = Interval(2, 3);
    intervalMatrix(1) = Interval(4, 5);
    
    IntervalRowMatrix2d quotients = doubleMatrix.cwiseQuotient(intervalMatrix);
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
    Matrix2d c = a * b;

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

        MatrixXd b = a;
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
        MatrixXd a(2, 2);
        a(0, 0) = 1;
        a(1, 0) = 2;
        a(0, 1) = 3;
        a(1, 1) = 4;

        Matrix2d b = a;
        REQUIRE(b(0, 0) == 1);
        REQUIRE(b(1, 0) == 2);
        REQUIRE(b(0, 1) == 3);
        REQUIRE(b(1, 1) == 4);
    }
}

TEST_CASE("Dynamic matrix row access") {
    MatrixXd matrix(3, 11);
    for (int i = 0; i <= 10; ++i) {
        matrix(0, i) = 1 + i / 10.0;
        matrix(1, i) = 2 + i / 10.0;
        matrix(2, i) = 3 + i / 10.0;
    }

    RowMatrixXd row = matrix.row(1);
    for (int i = 0; i <= 10; ++i) {
        REQUIRE((row(i) - (2 + i / 10.0)) == Zero());
    }
}

TEST_CASE("Dynamic matrix inversion") {
    MatrixXd matrix(3, 3);
    matrix(0, 0) = 1;
    matrix(0, 1) = 1;
    matrix(1, 1) = 1;
    matrix(0, 2) = 1;
    matrix(1, 2) = 1;
    matrix(2, 2) = 1;

    MatrixXd inverse = matrix.inverse();
    REQUIRE(inverse.numRows() == 3);
    REQUIRE(inverse.numColumns() == 3);

    MatrixXd identity = inverse * matrix;
    REQUIRE(identity.numRows() == 3);
    REQUIRE(identity.numColumns() == 3);
    REQUIRE(identity.isIdentity());
}

TEST_CASE("Dynamic matrix map") {
    MatrixXd matrix(3, 3);
    for (int index = 0; index < 9; ++index) {
        matrix(index) = index;
    }
    RowMatrix3d mappedRow = matrix.row(1).map(
        [] (double component) {
            return 2 * component;
        }
    );
    REQUIRE((mappedRow(0) - 2) == Zero());
    REQUIRE((mappedRow(1) - 8) == Zero());
    REQUIRE((mappedRow(2) - 14) == Zero());
}

TEST_CASE("Dynamic matrix binary map") {
    MatrixXd firstMatrix(2, 3);
    for (int index = 0; index < 6; ++index) {
        firstMatrix(index) = index;
    }
    
    MatrixXd secondMatrix(2, 3);
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
    MatrixXd firstMatrix(2, 3);
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
    MatrixXd result = firstMatrix * secondMatrix;
    REQUIRE(result.numRows() == 2);
    REQUIRE(result.numColumns() == 2);
    REQUIRE((result(0, 0) - 22) == Zero());
    REQUIRE((result(1, 0) - 28) == Zero());
    REQUIRE((result(0, 1) - 49) == Zero());
    REQUIRE((result(1, 1) - 64) == Zero());
}

TEST_CASE("Block assignment") {
    Matrix3d matrix;
    matrix.block<2, 2>(1, 1) = Matrix2d::Ones();
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
    MatrixXd matrix(10, 10);
    matrix.block(2, 3, 4, 5).setOnes();
    for (int columnIndex = 0; columnIndex < 10; ++columnIndex) {
        for (int rowIndex = 0; rowIndex < 10; ++rowIndex) {
            if (rowIndex >= 2 && rowIndex < 6 && columnIndex >= 3 && columnIndex < 8) {
                REQUIRE(matrix(rowIndex, columnIndex) == 1);
            } else {
                REQUIRE(matrix(rowIndex, columnIndex) == 0);
            }
        }
    }
}

TEST_CASE("Block-to-block assignment") {
    Matrix3d matrix;
    matrix.block<2, 2>(0, 1) = Matrix3d::Identity().block(1, 0, 2, 2);
    for (int columnIndex = 0; columnIndex < 3; ++columnIndex) {
        for (int rowIndex = 0; rowIndex < 3; ++rowIndex) {
            if (rowIndex == 0 && columnIndex == 2) {
                REQUIRE(matrix(rowIndex, columnIndex) == 1);
            } else {
                REQUIRE(matrix(rowIndex, columnIndex) == 0);
            }
        }
    }
}

TEST_CASE("Same-type view assignment") {
    Matrix3d matrix = Matrix3d::Identity();
    auto column0 = matrix.column(0);
    auto column1 = matrix.column(1);
    auto column2 = matrix.column(2);
    column2 = column0;
    column2 = column1;
    CHECK(matrix.column(2) == matrix.column(1));
    CHECK_FALSE(matrix.column(0) == matrix.column(1));
}

TEST_CASE("Stream output") {
    auto checkTypeName = [] (const std::string& string, const std::string& typeName) {
        REQUIRE(string.substr(0, typeName.size()) == typeName);
    };
    std::stringstream stream;
    SECTION("Matrix1d") {
        Matrix1d matrix;
        stream << matrix;
        checkTypeName(stream.str(), "Matrix1d");
    }
    SECTION("ColumnMatrix3d") {
        ColumnMatrix3d matrix;
        stream << matrix;
        checkTypeName(stream.str(), "ColumnMatrix3d");
    }
    SECTION("RowMatrixXd") {
        RowMatrixXd matrix(3);
        stream << matrix;
        checkTypeName(stream.str(), "RowMatrixXd");
    }
    SECTION("IntervalMatrix3d") {
        IntervalMatrix3d matrix;
        stream << matrix;
        checkTypeName(stream.str(), "IntervalMatrix3d");
    }
    SECTION("MatrixXd") {
        MatrixXd matrix(3,3);
        stream << matrix;
        checkTypeName(stream.str(), "MatrixXd");
    }
}

TEST_CASE("2D Eigen decomposition") {
    Matrix2d matrix;
    matrix(0, 0) = 2;
    matrix(1, 0) = 1;
    matrix(0, 1) = 1;
    matrix(1, 1) = 3;

    INFO("Matrix:\n" << matrix);

    auto decomposition = matrix.eigenDecomposition();
    REQUIRE(decomposition.exists());
    
    ColumnMatrix2d eigenvalues = decomposition.eigenvalues();
    Matrix2d eigenvectors = decomposition.eigenvectors();
    INFO("Eigenvalues:\n" << eigenvalues);
    INFO("Eigenvectors:\n" << eigenvectors);

    REQUIRE((matrix * eigenvectors.column(0) - eigenvalues(0) * eigenvectors.column(0)).isZero());
    REQUIRE((matrix * eigenvectors.column(1) - eigenvalues(1) * eigenvectors.column(1)).isZero());
}
