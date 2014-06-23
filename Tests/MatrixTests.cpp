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
    for (int i = 0; i < 100; ++i) {
        Matrix2d matrix = Matrix2d::random();
        if (matrix.determinant() != Zero(1e-3)) {
            Matrix2d inverse = matrix.inverse();
            REQUIRE((matrix * inverse).isIdentity());
            REQUIRE((inverse * matrix).isIdentity());
        }
    }
}

TEST_CASE("3D matrix inversion") {
    for (int i = 0; i < 100; ++i) {
        Matrix3d matrix = Matrix3d::random();
        if (matrix.determinant() != Zero(1e-3)) {
            Matrix3d inverse = matrix.inverse();
            REQUIRE((matrix * inverse).isIdentity());
            REQUIRE((inverse * matrix).isIdentity());
        }
    }
}

TEST_CASE("2D Interval matrix inversion") {
    for (int i = 0; i < 100; ++i) {
        IntervalMatrix2d matrix = IntervalMatrix2d::random();
        IntervalMatrix2d inverse = matrix.inverse();
        auto containsFunction = [] (Interval testComponent, double identityComponent) -> bool {
            return testComponent.contains(identityComponent);
        };
        REQUIRE((matrix * inverse).binaryAll(Matrix2d::identity(), containsFunction));
        REQUIRE((inverse * matrix).binaryAll(Matrix2d::identity(), containsFunction));
    }
}

TEST_CASE("3D Interval matrix inversion") {
    for (int i = 0; i < 100; ++i) {
        IntervalMatrix3d matrix = IntervalMatrix3d::random();
        IntervalMatrix3d inverse = matrix.inverse();
        auto containsFunction = [] (Interval testComponent, double identityComponent) -> bool {
            return testComponent.contains(identityComponent);
        };
        REQUIRE((matrix * inverse).binaryAll(Matrix3d::identity(), containsFunction));
        REQUIRE((inverse * matrix).binaryAll(Matrix3d::identity(), containsFunction));
    }
}

TEST_CASE("Min component") {
    SECTION("Square matrices") {
        for (int i = 0; i < 100; ++i) {
            Matrix3d matrix = Matrix3d::random();
            int rowIndex = 0;
            int columnIndex = 0;
            double minComponent = matrix.minComponent(&rowIndex, &columnIndex);
            REQUIRE(matrix(rowIndex, columnIndex) == minComponent);
            REQUIRE(
                matrix.all(
                    [minComponent] (double component) -> bool {
                        return component >= minComponent;
                    }
                )
            );
        }
    }
    SECTION("Row matrices") {
        for (int i = 0; i < 100; ++i) {
            RowMatrix3d matrix = RowMatrix3d::random();
            int index = 0;
            double minComponent = matrix.minComponent(&index);
            REQUIRE(matrix(index) == minComponent);
            REQUIRE(
                matrix.all(
                    [minComponent] (double component) -> bool {
                        return component >= minComponent;
                    }
                )
            );
        }
    }
}

TEST_CASE("Max component") {
    SECTION("Square matrices") {
        for (int i = 0; i < 100; ++i) {
            Matrix3d matrix = Matrix3d::random();
            int rowIndex = 0;
            int columnIndex = 0;
            double maxComponent = matrix.maxComponent(&rowIndex, &columnIndex);
            REQUIRE(matrix(rowIndex, columnIndex) == maxComponent);
            REQUIRE(
                matrix.all(
                    [maxComponent] (double component) -> bool {
                        return component <= maxComponent;
                    }
                )
            );
        }
    }
    SECTION("Row matrices") {
        for (int i = 0; i < 100; ++i) {
            RowMatrix3d matrix = RowMatrix3d::random();
            int index = 0;
            double maxComponent = matrix.maxComponent(&index);
            REQUIRE(matrix(index) == maxComponent);
            REQUIRE(
                matrix.all(
                    [maxComponent] (double component) -> bool {
                        return component <= maxComponent;
                    }
                )
            );
        }
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
        ColumnMatrix2d matrix;
        matrix(0) = -1;
        matrix(1) = 3;

        ColumnMatrix2d squaredComponents = matrix.cwiseSquared();
        REQUIRE(squaredComponents(0) == 1);
        REQUIRE(squaredComponents(1) == 9);
    }

    SECTION("Interval matrices") {
        IntervalColumnMatrix2d matrix;
        matrix(0) = Interval(2, 3);
        matrix(1) = Interval(-1, 1);

        IntervalColumnMatrix2d squaredComponents = matrix.cwiseSquared();
        REQUIRE(squaredComponents(0).lowerBound() == 4);
        REQUIRE(squaredComponents(0).upperBound() == 9);
        REQUIRE(squaredComponents(1).lowerBound() == 0);
        REQUIRE(squaredComponents(1).upperBound() == 1);
    }
}

TEST_CASE("Coefficient-wise absolute value") {
    SECTION("Double matrices") {  
        ColumnMatrix2d matrix;
        matrix(0) = -1;
        matrix(1) = 3;

        ColumnMatrix2d absoluteComponents = matrix.cwiseAbs();
        REQUIRE(absoluteComponents(0) == 1);
        REQUIRE(absoluteComponents(1) == 3);
    }

    SECTION("Interval matrices") {
        Matrix<Interval, 4, 1> matrix;
        matrix(0) = Interval(2, 3);
        matrix(1) = Interval(-1, 2);
        matrix(2) = Interval(-3, 1);
        matrix(3) = Interval(-4, -3);

        Matrix<Interval, 4, 1> absoluteComponents = matrix.cwiseAbs();
        REQUIRE(absoluteComponents(0).lowerBound() == 2);
        REQUIRE(absoluteComponents(0).upperBound() == 3);
        REQUIRE(absoluteComponents(1).lowerBound() == 0);
        REQUIRE(absoluteComponents(1).upperBound() == 2);
        REQUIRE(absoluteComponents(2).lowerBound() == 0);
        REQUIRE(absoluteComponents(2).upperBound() == 3);
        REQUIRE(absoluteComponents(3).lowerBound() == 3);
        REQUIRE(absoluteComponents(3).upperBound() == 4);
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
        MatrixXd a(std::pair<int, int>(2, 2));
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
    MatrixXd matrix(std::pair<int, int>(3, 11));
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
    MatrixXd matrix(std::pair<int, int>(3, 3));
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
    MatrixXd matrix(std::pair<int, int>(3, 3));
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
    MatrixXd firstMatrix(std::pair<int, int>(2, 3));
    for (int index = 0; index < 6; ++index) {
        firstMatrix(index) = index;
    }
    
    MatrixXd secondMatrix(std::pair<int, int>(2, 3));
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
    MatrixXd firstMatrix(std::pair<int, int>(2, 3));
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
    matrix.block<2, 2>(1, 1) = Matrix2d::ones();
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
    MatrixXd matrix(std::pair<int, int>(10, 10));
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
    matrix.block<2, 2>(0, 1) = Matrix3d::identity().block(1, 0, 2, 2);
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
    Matrix3d matrix = Matrix3d::identity();
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
        RowMatrixXd matrix(std::pair<int, int>(1, 3));
        stream << matrix;
        checkTypeName(stream.str(), "RowMatrixXd");
    }
    SECTION("IntervalMatrix3d") {
        IntervalMatrix3d matrix;
        stream << matrix;
        checkTypeName(stream.str(), "IntervalMatrix3d");
    }
    SECTION("MatrixXd") {
        MatrixXd matrix(std::pair<int, int>(3,3));
        stream << matrix;
        checkTypeName(stream.str(), "MatrixXd");
    }
}

TEST_CASE("2D Eigen decomposition") {
    for (int i = 0; i < 100; ++i) {
        Matrix2d randomMatrix = Matrix2d::random();
        Matrix2d symmetricMatrix = 0.5 * (randomMatrix + randomMatrix.transpose());

        CAPTURE(symmetricMatrix);

        auto decomposition = symmetricMatrix.eigenDecomposition();
        REQUIRE(decomposition.exists());
   
        ColumnMatrix2d eigenvalues = decomposition.eigenvalues();
        Matrix2d eigenvectors = decomposition.eigenvectors();
        CAPTURE(eigenvalues);
        CAPTURE(eigenvectors);

        for (int j = 0; j < 2; ++j) {
            double eigenvalue = eigenvalues(j);
            ColumnMatrix2d eigenvector = eigenvectors.column(j);
            CAPTURE(eigenvalue);
            CAPTURE(eigenvector);
            CAPTURE(symmetricMatrix * eigenvector);
            CAPTURE(eigenvalue * eigenvector);
            CAPTURE(symmetricMatrix * eigenvector - eigenvalue * eigenvector);
            REQUIRE((symmetricMatrix * eigenvector - eigenvalue * eigenvector).isZero());
        }
    }
}

TEST_CASE("3D Eigen decomposition") {
    for (int i = 0; i < 100; ++i) {
        Matrix3d randomMatrix = Matrix3d::random();
        Matrix3d symmetricMatrix = 0.5 * (randomMatrix + randomMatrix.transpose());

        CAPTURE(symmetricMatrix);

        auto decomposition = symmetricMatrix.eigenDecomposition();
        REQUIRE(decomposition.exists());
   
        ColumnMatrix3d eigenvalues = decomposition.eigenvalues();
        Matrix3d eigenvectors = decomposition.eigenvectors();
        CAPTURE(eigenvalues);
        CAPTURE(eigenvectors);

        for (int j = 0; j < 3; ++j) {
            double eigenvalue = eigenvalues(j);
            ColumnMatrix3d eigenvector = eigenvectors.column(j);
            CAPTURE(eigenvalue);
            CAPTURE(eigenvector);
            CAPTURE(symmetricMatrix * eigenvector);
            CAPTURE(eigenvalue * eigenvector);
            CAPTURE(symmetricMatrix * eigenvector - eigenvalue * eigenvector);
            REQUIRE((symmetricMatrix * eigenvector - eigenvalue * eigenvector).isZero());
        }
    }
}
