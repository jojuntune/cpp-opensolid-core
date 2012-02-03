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

#include <OpenSolid/config.hpp>

#include <OpenSolid/Common/Error.hpp>
#include <OpenSolid/Python/PythonModule.hpp>

using namespace boost::python;

namespace OpenSolid
{
    void bindFunction();
    void bindDatum();
    void bindSimplex();
    void bindMatrixConstructors();
    void bindMatrix();
    void bindComparison();
    void bindInterval();
    void bindDouble();
    void bindError();

    void PythonModule::initialize() {
        bindFunction();
        bindDatum();
        bindSimplex();
        bindMatrix();
        bindMatrixConstructors();
        bindComparison();
        bindInterval();
        bindDouble();
        bindError();
    }

    BOOST_PYTHON_MODULE(opensolid) {PythonModule::initialize();}

    // UnaryMatrixError

    template <class MatrixType>
    UnaryMatrixError<MatrixType>::UnaryMatrixError(const MatrixType& matrix) : _matrix(matrix) {}

    template <class MatrixType>
    MatrixType UnaryMatrixError<MatrixType>::matrix() const {return _matrix;}

    template class UnaryMatrixError<MatrixXd>;
    template class UnaryMatrixError<MatrixXI>;

    // BinaryMatrixError

    template <class FirstMatrixType, class SecondMatrixType>
    BinaryMatrixError<FirstMatrixType, SecondMatrixType>::BinaryMatrixError(
        const FirstMatrixType& first_matrix,
        const SecondMatrixType& second_matrix
    ) : _first_matrix(first_matrix), _second_matrix(second_matrix) {}

    template <class FirstMatrixType, class SecondMatrixType>
    FirstMatrixType BinaryMatrixError<FirstMatrixType, SecondMatrixType>::firstMatrix() const {
        return _first_matrix;
    }

    template <class FirstMatrixType, class SecondMatrixType>
    SecondMatrixType BinaryMatrixError<FirstMatrixType, SecondMatrixType>::secondMatrix() const {
        return _second_matrix;
    }

    template class BinaryMatrixError<MatrixXd, MatrixXd>;
    template class BinaryMatrixError<MatrixXd, MatrixXI>;
    template class BinaryMatrixError<MatrixXI, MatrixXd>;
    template class BinaryMatrixError<MatrixXI, MatrixXI>;

    // VectorComponentError

    template <class MatrixType>
    VectorComponentError<MatrixType>::VectorComponentError(const MatrixType& matrix, int index) :
        UnaryMatrixError<MatrixType>(matrix), _index(index) {}

    template VectorComponentError<MatrixXd>::VectorComponentError(const MatrixXd&, int);
    template VectorComponentError<MatrixXI>::VectorComponentError(const MatrixXI&, int);

    template <>
    const char* VectorComponentError<MatrixXd>::what() const {
        return "VectorComponentError<MatrixXd>";
    }

    template <>
    const char* VectorComponentError<MatrixXI>::what() const {
        return "VectorComponentError<MatrixXI>";
    }

    template <class MatrixType>
    int VectorComponentError<MatrixType>::index() const {return _index;}

    template int VectorComponentError<MatrixXd>::index() const;
    template int VectorComponentError<MatrixXI>::index() const;

    // VectorIndexError

    template <class MatrixType>
    VectorIndexError<MatrixType>::VectorIndexError(
        const MatrixType& matrix,
        boost::python::object index
    ) : UnaryMatrixError<MatrixType>(matrix), _index(index) {}

    template VectorIndexError<MatrixXd>::VectorIndexError(const MatrixXd&, boost::python::object);
    template VectorIndexError<MatrixXI>::VectorIndexError(const MatrixXI&, boost::python::object);

    template <>
    const char* VectorIndexError<MatrixXd>::what() const {
        return "VectorIndexError<MatrixXd>";
    }

    template <>
    const char* VectorIndexError<MatrixXI>::what() const {
        return "VectorIndexError<MatrixXI>";
    }

    template <class MatrixType>
    boost::python::object VectorIndexError<MatrixType>::index() const {return _index;}

    template boost::python::object VectorIndexError<MatrixXd>::index() const;
    template boost::python::object VectorIndexError<MatrixXI>::index() const;

    // MatrixIndexError

    template <class MatrixType>
    MatrixIndexError<MatrixType>::MatrixIndexError(
        const MatrixType& matrix,
        boost::python::object row_index,
        boost::python::object col_index
    ) : UnaryMatrixError<MatrixType>(matrix), _row_index(row_index), _col_index(col_index) {}

    template MatrixIndexError<MatrixXd>::MatrixIndexError(const MatrixXd&, boost::python::object, boost::python::object);
    template MatrixIndexError<MatrixXI>::MatrixIndexError(const MatrixXI&, boost::python::object, boost::python::object);

    template <>
    const char* MatrixIndexError<MatrixXd>::what() const {
        return "MatrixIndexError<MatrixXd>";
    }

    template <>
    const char* MatrixIndexError<MatrixXI>::what() const {
        return "MatrixIndexError<MatrixXI>";
    }

    template <class MatrixType>
    boost::python::object MatrixIndexError<MatrixType>::rowIndex() const {return _row_index;}

    template boost::python::object MatrixIndexError<MatrixXd>::rowIndex() const;
    template boost::python::object MatrixIndexError<MatrixXI>::rowIndex() const;

    template <class MatrixType>
    boost::python::object MatrixIndexError<MatrixType>::colIndex() const {return _col_index;}

    template boost::python::object MatrixIndexError<MatrixXd>::colIndex() const;
    template boost::python::object MatrixIndexError<MatrixXI>::colIndex() const;

    // VectorAssignmentError

    template <class MatrixType>
    VectorAssignmentError<MatrixType>::VectorAssignmentError(
        const MatrixType& first_matrix,
        boost::python::object index,
        const MatrixType& second_matrix
    ) : BinaryMatrixError<MatrixType, MatrixType>(first_matrix, second_matrix), _index(index) {}

    template VectorAssignmentError<MatrixXd>::VectorAssignmentError(const MatrixXd&, boost::python::object, const MatrixXd&);
    template VectorAssignmentError<MatrixXI>::VectorAssignmentError(const MatrixXI&, boost::python::object, const MatrixXI&);

    template <>
    const char* VectorAssignmentError<MatrixXd>::what() const {
        return "VectorAssignmentError<MatrixXd>";
    }

    template <>
    const char* VectorAssignmentError<MatrixXI>::what() const {
        return "VectorAssignmentError<MatrixXI>";
    }

    template <class MatrixType>
    boost::python::object VectorAssignmentError<MatrixType>::index() const {return _index;}

    template boost::python::object VectorAssignmentError<MatrixXd>::index() const;
    template boost::python::object VectorAssignmentError<MatrixXI>::index() const;

    // MatrixAssignmentError

    template <class MatrixType>
    MatrixAssignmentError<MatrixType>::MatrixAssignmentError(
        const MatrixType& first_matrix,
        boost::python::object row_index,
        boost::python::object col_index,
        const MatrixType& second_matrix
    ) : BinaryMatrixError<MatrixType, MatrixType>(first_matrix, second_matrix),
        _row_index(row_index),
        _col_index(col_index) {}

    template MatrixAssignmentError<MatrixXd>::MatrixAssignmentError(const MatrixXd&, boost::python::object, boost::python::object, const MatrixXd&);
    template MatrixAssignmentError<MatrixXI>::MatrixAssignmentError(const MatrixXI&, boost::python::object, boost::python::object, const MatrixXI&);

    template <>
    const char* MatrixAssignmentError<MatrixXd>::what() const {
        return "MatrixAssignmentError<MatrixXd>";
    }

    template <>
    const char* MatrixAssignmentError<MatrixXI>::what() const {
        return "MatrixAssignmentError<MatrixXI>";
    }

    template <class MatrixType>
    boost::python::object MatrixAssignmentError<MatrixType>::rowIndex() const {return _row_index;}

    template boost::python::object MatrixAssignmentError<MatrixXd>::rowIndex() const;
    template boost::python::object MatrixAssignmentError<MatrixXI>::rowIndex() const;

    template <class MatrixType>
    boost::python::object MatrixAssignmentError<MatrixType>::colIndex() const {return _col_index;}

    template boost::python::object MatrixAssignmentError<MatrixXd>::colIndex() const;
    template boost::python::object MatrixAssignmentError<MatrixXI>::colIndex() const;

    // VectorSquaredNormError

    template <class MatrixType>
    VectorSquaredNormError<MatrixType>::VectorSquaredNormError(const MatrixType& matrix) :
        UnaryMatrixError<MatrixType>(matrix) {}

    template VectorSquaredNormError<MatrixXd>::VectorSquaredNormError(const MatrixXd&);
    template VectorSquaredNormError<MatrixXI>::VectorSquaredNormError(const MatrixXI&);

    template <>
    const char* VectorSquaredNormError<MatrixXd>::what() const {
        return "VectorSquaredNormError<MatrixXd>";
    }

    template <>
    const char* VectorSquaredNormError<MatrixXI>::what() const {
        return "VectorSquaredNormError<MatrixXI>";
    }

    // VectorNormError

    template <class MatrixType>
    VectorNormError<MatrixType>::VectorNormError(const MatrixType& matrix) :
        UnaryMatrixError<MatrixType>(matrix) {}

    template VectorNormError<MatrixXd>::VectorNormError(const MatrixXd&);
    template VectorNormError<MatrixXI>::VectorNormError(const MatrixXI&);

    template <>
    const char* VectorNormError<MatrixXd>::what() const {
        return "VectorNormError<MatrixXd>";
    }

    template <>
    const char* VectorNormError<MatrixXI>::what() const {
        return "VectorNormError<MatrixXI>";
    }

    // VectorNormalizedError

    template <class MatrixType>
    VectorNormalizedError<MatrixType>::VectorNormalizedError(const MatrixType& matrix) :
        UnaryMatrixError<MatrixType>(matrix) {}

    template VectorNormalizedError<MatrixXd>::VectorNormalizedError(const MatrixXd&);
    template VectorNormalizedError<MatrixXI>::VectorNormalizedError(const MatrixXI&);

    template <>
    const char* VectorNormalizedError<MatrixXd>::what() const {
        return "VectorNormalizedError<MatrixXd>";
    }

    template <>
    const char* VectorNormalizedError<MatrixXI>::what() const {
        return "VectorNormalizedError<MatrixXI>";
    }

    // MatrixDeterminantError

    template <class MatrixType>
    MatrixDeterminantError<MatrixType>::MatrixDeterminantError(const MatrixType& matrix) :
        UnaryMatrixError<MatrixType>(matrix) {}

    template MatrixDeterminantError<MatrixXd>::MatrixDeterminantError(const MatrixXd&);
    template MatrixDeterminantError<MatrixXI>::MatrixDeterminantError(const MatrixXI&);

    template <>
    const char* MatrixDeterminantError<MatrixXd>::what() const {
        return "MatrixDeterminantError<MatrixXd>";
    }

    template <>
    const char* MatrixDeterminantError<MatrixXI>::what() const {
        return "MatrixDeterminantError<MatrixXI>";
    }

    // MatrixInverseError

    MatrixInverseError::MatrixInverseError(const MatrixXd& matrix) :
        UnaryMatrixError<MatrixXd>(matrix) {}

    const char* MatrixInverseError::what() const {
        return "MatrixInverseError";
    }

    // MatrixReplicateError

    template <class MatrixType>
    MatrixReplicateError<MatrixType>::MatrixReplicateError(
        const MatrixType& matrix,
        int row_factor,
        int col_factor
    ) : UnaryMatrixError<MatrixType>(matrix), _row_factor(row_factor), _col_factor(col_factor) {}

    template MatrixReplicateError<MatrixXd>::MatrixReplicateError(const MatrixXd&, int, int);
    template MatrixReplicateError<MatrixXI>::MatrixReplicateError(const MatrixXI&, int, int);

    template <>
    const char* MatrixReplicateError<MatrixXd>::what() const {
        return "MatrixReplicateError<MatrixXd>";
    }

    template <>
    const char* MatrixReplicateError<MatrixXI>::what() const {
        return "MatrixReplicateError<MatrixXI>";
    }

    template <class MatrixType>
    int MatrixReplicateError<MatrixType>::rowFactor() const {return _row_factor;}

    template int MatrixReplicateError<MatrixXd>::rowFactor() const;
    template int MatrixReplicateError<MatrixXI>::rowFactor() const;

    template <class MatrixType>
    int MatrixReplicateError<MatrixType>::colFactor() const {return _col_factor;}

    template int MatrixReplicateError<MatrixXd>::colFactor() const;
    template int MatrixReplicateError<MatrixXI>::colFactor() const;

    // MatrixDotProductError

    template <class FirstMatrixType, class SecondMatrixType>
    MatrixDotProductError<FirstMatrixType, SecondMatrixType>::MatrixDotProductError(
        const FirstMatrixType& first_matrix,
        const SecondMatrixType& second_matrix
    ) : BinaryMatrixError<FirstMatrixType, SecondMatrixType>(first_matrix, second_matrix) {}

    template MatrixDotProductError<MatrixXd, MatrixXd>::MatrixDotProductError(const MatrixXd&, const MatrixXd&);
    template MatrixDotProductError<MatrixXd, MatrixXI>::MatrixDotProductError(const MatrixXd&, const MatrixXI&);
    template MatrixDotProductError<MatrixXI, MatrixXd>::MatrixDotProductError(const MatrixXI&, const MatrixXd&);
    template MatrixDotProductError<MatrixXI, MatrixXI>::MatrixDotProductError(const MatrixXI&, const MatrixXI&);

    template <>
    const char* MatrixDotProductError<MatrixXd, MatrixXd>::what() const {
        return "MatrixDotProductError<MatrixXd, MatrixXd>";
    }

    template <>
    const char* MatrixDotProductError<MatrixXd, MatrixXI>::what() const {
        return "MatrixDotProductError<MatrixXd, MatrixXI>";
    }

    template <>
    const char* MatrixDotProductError<MatrixXI, MatrixXd>::what() const {
        return "MatrixDotProductError<MatrixXI, MatrixXd>";
    }

    template <>
    const char* MatrixDotProductError<MatrixXI, MatrixXI>::what() const {
        return "MatrixDotProductError<MatrixXI, MatrixXI>";
    }

    // MatrixCrossProductError

    template <class FirstMatrixType, class SecondMatrixType>
    MatrixCrossProductError<FirstMatrixType, SecondMatrixType>::MatrixCrossProductError(
        const FirstMatrixType& first_matrix,
        const SecondMatrixType& second_matrix
    ) : BinaryMatrixError<FirstMatrixType, SecondMatrixType>(first_matrix, second_matrix) {}

    template MatrixCrossProductError<MatrixXd, MatrixXd>::MatrixCrossProductError(const MatrixXd&, const MatrixXd&);
    template MatrixCrossProductError<MatrixXd, MatrixXI>::MatrixCrossProductError(const MatrixXd&, const MatrixXI&);
    template MatrixCrossProductError<MatrixXI, MatrixXd>::MatrixCrossProductError(const MatrixXI&, const MatrixXd&);
    template MatrixCrossProductError<MatrixXI, MatrixXI>::MatrixCrossProductError(const MatrixXI&, const MatrixXI&);

    template <>
    const char* MatrixCrossProductError<MatrixXd, MatrixXd>::what() const {
        return "MatrixCrossProductError<MatrixXd, MatrixXd>";
    }

    template <>
    const char* MatrixCrossProductError<MatrixXd, MatrixXI>::what() const {
        return "MatrixCrossProductError<MatrixXd, MatrixXI>";
    }

    template <>
    const char* MatrixCrossProductError<MatrixXI, MatrixXd>::what() const {
        return "MatrixCrossProductError<MatrixXI, MatrixXd>";
    }

    template <>
    const char* MatrixCrossProductError<MatrixXI, MatrixXI>::what() const {
        return "MatrixCrossProductError<MatrixXI, MatrixXI>";
    }

    // MatrixOverlapsError

    MatrixOverlapsError::MatrixOverlapsError(
        const MatrixXI& first_matrix,
        const MatrixXI& second_matrix
    ) : BinaryMatrixError<MatrixXI, MatrixXI>(first_matrix, second_matrix) {}

    const char* MatrixOverlapsError::what() const {
        return "MatrixOverlapsError";
    }

    // MatrixContainsError

    template <class SecondMatrixType>
    MatrixContainsError<SecondMatrixType>::MatrixContainsError(
        const MatrixXI& first_matrix,
        const SecondMatrixType& second_matrix
    ) : BinaryMatrixError<MatrixXI, SecondMatrixType>(first_matrix, second_matrix) {}

    template MatrixContainsError<MatrixXd>::MatrixContainsError(const MatrixXI&, const MatrixXd&);
    template MatrixContainsError<MatrixXI>::MatrixContainsError(const MatrixXI&, const MatrixXI&);

    template <>
    const char* MatrixContainsError<MatrixXd>::what() const {
        return "MatrixContainsError<MatrixXd>";
    }

    template <>
    const char* MatrixContainsError<MatrixXI>::what() const {
        return "MatrixContainsError<MatrixXI>";
    }

    // MatrixHullError

    template <class FirstMatrixType, class SecondMatrixType>
    MatrixHullError<FirstMatrixType, SecondMatrixType>::MatrixHullError(
        const FirstMatrixType& first_matrix,
        const SecondMatrixType& second_matrix
    ) : BinaryMatrixError<FirstMatrixType, SecondMatrixType>(first_matrix, second_matrix) {}

    template MatrixHullError<MatrixXd, MatrixXd>::MatrixHullError(const MatrixXd&, const MatrixXd&);
    template MatrixHullError<MatrixXd, MatrixXI>::MatrixHullError(const MatrixXd&, const MatrixXI&);
    template MatrixHullError<MatrixXI, MatrixXd>::MatrixHullError(const MatrixXI&, const MatrixXd&);
    template MatrixHullError<MatrixXI, MatrixXI>::MatrixHullError(const MatrixXI&, const MatrixXI&);

    template <>
    const char* MatrixHullError<MatrixXd, MatrixXd>::what() const {
        return "MatrixHullError<MatrixXd, MatrixXd>";
    }

    template <>
    const char* MatrixHullError<MatrixXd, MatrixXI>::what() const {
        return "MatrixHullError<MatrixXd, MatrixXI>";
    }

    template <>
    const char* MatrixHullError<MatrixXI, MatrixXd>::what() const {
        return "MatrixHullError<MatrixXI, MatrixXd>";
    }

    template <>
    const char* MatrixHullError<MatrixXI, MatrixXI>::what() const {
        return "MatrixHullError<MatrixXI, MatrixXI>";
    }

    // MatrixIntersectionError

    MatrixIntersectionError::MatrixIntersectionError(
        const MatrixXI& first_matrix,
        const MatrixXI& second_matrix
    ) : BinaryMatrixError<MatrixXI, MatrixXI>(first_matrix, second_matrix) {}

    const char* MatrixIntersectionError::what() const {
        return "MatrixIntersectionError";
    }

    // MatrixFactoryError

    MatrixFactoryError::MatrixFactoryError(int rows, int cols) : _rows(rows), _cols(cols) {}

    int MatrixFactoryError::rows() const {return _rows;}

    int MatrixFactoryError::cols() const {return _cols;}

    // ConstantMatrixConstructionError

    template <class MatrixType>
    ConstantMatrixConstructionError<MatrixType>::ConstantMatrixConstructionError(
        int rows,
        int cols,
        typename MatrixType::Scalar value
    ) : MatrixFactoryError(rows, cols), _value(value) {}

    template ConstantMatrixConstructionError<MatrixXd>::ConstantMatrixConstructionError(int, int, double);
    template ConstantMatrixConstructionError<MatrixXI>::ConstantMatrixConstructionError(int, int, Interval);

    template <>
    const char* ConstantMatrixConstructionError<MatrixXd>::what() const {
        return "ConstantMatrixConstructionError<MatrixXd>";
    }

    template <>
    const char* ConstantMatrixConstructionError<MatrixXI>::what() const {
        return "ConstantMatrixConstructionError<MatrixXI>";
    }

    template <class MatrixType>
    typename MatrixType::Scalar ConstantMatrixConstructionError<MatrixType>::value() const {
        return _value;
    }

    template double ConstantMatrixConstructionError<MatrixXd>::value() const;
    template Interval ConstantMatrixConstructionError<MatrixXI>::value() const;

    // ZeroMatrixConstructionError

    template <class MatrixType>
    ZeroMatrixConstructionError<MatrixType>::ZeroMatrixConstructionError(int rows, int cols) :
        MatrixFactoryError(rows, cols) {}

    template ZeroMatrixConstructionError<MatrixXd>::ZeroMatrixConstructionError(int, int);
    template ZeroMatrixConstructionError<MatrixXI>::ZeroMatrixConstructionError(int, int);

    template <>
    const char* ZeroMatrixConstructionError<MatrixXd>::what() const {
        return "ZeroMatrixConstructionError<MatrixXd>";
    }

    template <>
    const char* ZeroMatrixConstructionError<MatrixXI>::what() const {
        return "ZeroMatrixConstructionError<MatrixXI>";
    }

    // OnesMatrixConstructionError

    template <class MatrixType>
    OnesMatrixConstructionError<MatrixType>::OnesMatrixConstructionError(int rows, int cols) :
        MatrixFactoryError(rows, cols) {}

    template OnesMatrixConstructionError<MatrixXd>::OnesMatrixConstructionError(int, int);
    template OnesMatrixConstructionError<MatrixXI>::OnesMatrixConstructionError(int, int);

    template <>
    const char* OnesMatrixConstructionError<MatrixXd>::what() const {
        return "OnesMatrixConstructionError<MatrixXd>";
    }

    template <>
    const char* OnesMatrixConstructionError<MatrixXI>::what() const {
        return "OnesMatrixConstructionError<MatrixXI>";
    }

    // RandomMatrixConstructionError

    template <class MatrixType>
    RandomMatrixConstructionError<MatrixType>::RandomMatrixConstructionError(int rows, int cols) :
        MatrixFactoryError(rows, cols) {}

    template RandomMatrixConstructionError<MatrixXd>::RandomMatrixConstructionError(int, int);
    template RandomMatrixConstructionError<MatrixXI>::RandomMatrixConstructionError(int, int);

    template <>
    const char* RandomMatrixConstructionError<MatrixXd>::what() const {
        return "RandomMatrixConstructionError<MatrixXd>";
    }

    template <>
    const char* RandomMatrixConstructionError<MatrixXI>::what() const {
        return "RandomMatrixConstructionError<MatrixXI>";
    }

    // IdentityMatrixConstructionError

    template <class MatrixType>
    IdentityMatrixConstructionError<MatrixType>::IdentityMatrixConstructionError(int rows, int cols) :
        MatrixFactoryError(rows, cols) {}

    template IdentityMatrixConstructionError<MatrixXd>::IdentityMatrixConstructionError(int, int);
    template IdentityMatrixConstructionError<MatrixXI>::IdentityMatrixConstructionError(int, int);

    template <>
    const char* IdentityMatrixConstructionError<MatrixXd>::what() const {
        return "IdentityMatrixConstructionError<MatrixXd>";
    }

    template <>
    const char* IdentityMatrixConstructionError<MatrixXI>::what() const {
        return "IdentityMatrixConstructionError<MatrixXI>";
    }

    // MatrixSumError

    template <class FirstMatrixType, class SecondMatrixType>
    MatrixSumError<FirstMatrixType, SecondMatrixType>::MatrixSumError(
        const FirstMatrixType& first_matrix,
        const SecondMatrixType& second_matrix
    ) : BinaryMatrixError<FirstMatrixType, SecondMatrixType>(first_matrix, second_matrix) {}

    template MatrixSumError<MatrixXd, MatrixXd>::MatrixSumError(const MatrixXd&, const MatrixXd&);
    template MatrixSumError<MatrixXd, MatrixXI>::MatrixSumError(const MatrixXd&, const MatrixXI&);
    template MatrixSumError<MatrixXI, MatrixXd>::MatrixSumError(const MatrixXI&, const MatrixXd&);
    template MatrixSumError<MatrixXI, MatrixXI>::MatrixSumError(const MatrixXI&, const MatrixXI&);

    template <>
    const char* MatrixSumError<MatrixXd, MatrixXd>::what() const {
        return "MatrixSumError<MatrixXd, MatrixXd>";
    }

    template <>
    const char* MatrixSumError<MatrixXd, MatrixXI>::what() const {
        return "MatrixSumError<MatrixXd, MatrixXI>";
    }

    template <>
    const char* MatrixSumError<MatrixXI, MatrixXd>::what() const {
        return "MatrixSumError<MatrixXI, MatrixXd>";
    }

    template <>
    const char* MatrixSumError<MatrixXI, MatrixXI>::what() const {
        return "MatrixSumError<MatrixXI, MatrixXI>";
    }

    // MatrixDifferenceError

    template <class FirstMatrixType, class SecondMatrixType>
    MatrixDifferenceError<FirstMatrixType, SecondMatrixType>::MatrixDifferenceError(
        const FirstMatrixType& first_matrix,
        const SecondMatrixType& second_matrix
    ) : BinaryMatrixError<FirstMatrixType, SecondMatrixType>(first_matrix, second_matrix) {}

    template MatrixDifferenceError<MatrixXd, MatrixXd>::MatrixDifferenceError(const MatrixXd&, const MatrixXd&);
    template MatrixDifferenceError<MatrixXd, MatrixXI>::MatrixDifferenceError(const MatrixXd&, const MatrixXI&);
    template MatrixDifferenceError<MatrixXI, MatrixXd>::MatrixDifferenceError(const MatrixXI&, const MatrixXd&);
    template MatrixDifferenceError<MatrixXI, MatrixXI>::MatrixDifferenceError(const MatrixXI&, const MatrixXI&);

    template <>
    const char* MatrixDifferenceError<MatrixXd, MatrixXd>::what() const {
        return "MatrixDifferenceError<MatrixXd, MatrixXd>";
    }

    template <>
    const char* MatrixDifferenceError<MatrixXd, MatrixXI>::what() const {
        return "MatrixDifferenceError<MatrixXd, MatrixXI>";
    }

    template <>
    const char* MatrixDifferenceError<MatrixXI, MatrixXd>::what() const {
        return "MatrixDifferenceError<MatrixXI, MatrixXd>";
    }

    template <>
    const char* MatrixDifferenceError<MatrixXI, MatrixXI>::what() const {
        return "MatrixDifferenceError<MatrixXI, MatrixXI>";
    }

    // MatrixQuotientError

    template <class MatrixType, class ScalarType>
    MatrixQuotientError<MatrixType, ScalarType>::MatrixQuotientError(
        const MatrixType& matrix,
        ScalarType divisor
    ) : UnaryMatrixError<MatrixType>(matrix), _divisor(divisor) {}

    template MatrixQuotientError<MatrixXd, double>::MatrixQuotientError(const MatrixXd&, double);
    template MatrixQuotientError<MatrixXd, Interval>::MatrixQuotientError(const MatrixXd&, Interval);
    template MatrixQuotientError<MatrixXI, double>::MatrixQuotientError(const MatrixXI&, double);
    template MatrixQuotientError<MatrixXI, Interval>::MatrixQuotientError(const MatrixXI&, Interval);

    template <>
    const char* MatrixQuotientError<MatrixXd, double>::what() const {
        return "MatrixQuotientError<MatrixXd, double>";
    }

    template <>
    const char* MatrixQuotientError<MatrixXd, Interval>::what() const {
        return "MatrixQuotientError<MatrixXd, Interval>";
    }

    template <>
    const char* MatrixQuotientError<MatrixXI, double>::what() const {
        return "MatrixQuotientError<MatrixXI, double>";
    }

    template <>
    const char* MatrixQuotientError<MatrixXI, Interval>::what() const {
        return "MatrixQuotientError<MatrixXI, Interval>";
    }

    template <class MatrixType, class ScalarType>
    ScalarType MatrixQuotientError<MatrixType, ScalarType>::divisor() const {return _divisor;}

    template double MatrixQuotientError<MatrixXd, double>::divisor() const;
    template Interval MatrixQuotientError<MatrixXd, Interval>::divisor() const;
    template double MatrixQuotientError<MatrixXI, double>::divisor() const;
    template Interval MatrixQuotientError<MatrixXI, Interval>::divisor() const;

    // MatrixProductError

    template <class FirstMatrixType, class SecondMatrixType>
    MatrixProductError<FirstMatrixType, SecondMatrixType>::MatrixProductError(
        const FirstMatrixType& first_matrix,
        const SecondMatrixType& second_matrix
    ) : BinaryMatrixError<FirstMatrixType, SecondMatrixType>(first_matrix, second_matrix) {}

    template MatrixProductError<MatrixXd, MatrixXd>::MatrixProductError(const MatrixXd&, const MatrixXd&);
    template MatrixProductError<MatrixXd, MatrixXI>::MatrixProductError(const MatrixXd&, const MatrixXI&);
    template MatrixProductError<MatrixXI, MatrixXd>::MatrixProductError(const MatrixXI&, const MatrixXd&);
    template MatrixProductError<MatrixXI, MatrixXI>::MatrixProductError(const MatrixXI&, const MatrixXI&);

    template <>
    const char* MatrixProductError<MatrixXd, MatrixXd>::what() const {
        return "MatrixProductError<MatrixXd, MatrixXd>";
    }

    template <>
    const char* MatrixProductError<MatrixXd, MatrixXI>::what() const {
        return "MatrixProductError<MatrixXd, MatrixXI>";
    }

    template <>
    const char* MatrixProductError<MatrixXI, MatrixXd>::what() const {
        return "MatrixProductError<MatrixXI, MatrixXd>";
    }

    template <>
    const char* MatrixProductError<MatrixXI, MatrixXI>::what() const {
        return "MatrixProductError<MatrixXI, MatrixXI>";
    }

    // MatrixEqualityError

    template <class FirstMatrixType, class SecondMatrixType>
    MatrixEqualityError<FirstMatrixType, SecondMatrixType>::MatrixEqualityError(
        const FirstMatrixType& first_matrix,
        const SecondMatrixType& second_matrix
    ) : BinaryMatrixError<FirstMatrixType, SecondMatrixType>(first_matrix, second_matrix) {}

    template MatrixEqualityError<MatrixXd, MatrixXd>::MatrixEqualityError(const MatrixXd&, const MatrixXd&);
    template MatrixEqualityError<MatrixXd, MatrixXI>::MatrixEqualityError(const MatrixXd&, const MatrixXI&);
    template MatrixEqualityError<MatrixXI, MatrixXd>::MatrixEqualityError(const MatrixXI&, const MatrixXd&);
    template MatrixEqualityError<MatrixXI, MatrixXI>::MatrixEqualityError(const MatrixXI&, const MatrixXI&);

    template <>
    const char* MatrixEqualityError<MatrixXd, MatrixXd>::what() const {
        return "MatrixEqualityError<MatrixXd, MatrixXd>";
    }

    template <>
    const char* MatrixEqualityError<MatrixXd, MatrixXI>::what() const {
        return "MatrixEqualityError<MatrixXd, MatrixXI>";
    }

    template <>
    const char* MatrixEqualityError<MatrixXI, MatrixXd>::what() const {
        return "MatrixEqualityError<MatrixXI, MatrixXd>";
    }

    template <>
    const char* MatrixEqualityError<MatrixXI, MatrixXI>::what() const {
        return "MatrixEqualityError<MatrixXI, MatrixXI>";
    }

    // MatrixInequalityError

    template <class FirstMatrixType, class SecondMatrixType>
    MatrixInequalityError<FirstMatrixType, SecondMatrixType>::MatrixInequalityError(
        const FirstMatrixType& first_matrix,
        const SecondMatrixType& second_matrix
    ) : BinaryMatrixError<FirstMatrixType, SecondMatrixType>(first_matrix, second_matrix) {}

    template MatrixInequalityError<MatrixXd, MatrixXd>::MatrixInequalityError(const MatrixXd&, const MatrixXd&);
    template MatrixInequalityError<MatrixXd, MatrixXI>::MatrixInequalityError(const MatrixXd&, const MatrixXI&);
    template MatrixInequalityError<MatrixXI, MatrixXd>::MatrixInequalityError(const MatrixXI&, const MatrixXd&);
    template MatrixInequalityError<MatrixXI, MatrixXI>::MatrixInequalityError(const MatrixXI&, const MatrixXI&);

    template <>
    const char* MatrixInequalityError<MatrixXd, MatrixXd>::what() const {
        return "MatrixInequalityError<MatrixXd, MatrixXd>";
    }

    template <>
    const char* MatrixInequalityError<MatrixXd, MatrixXI>::what() const {
        return "MatrixInequalityError<MatrixXd, MatrixXI>";
    }

    template <>
    const char* MatrixInequalityError<MatrixXI, MatrixXd>::what() const {
        return "MatrixInequalityError<MatrixXI, MatrixXd>";
    }

    template <>
    const char* MatrixInequalityError<MatrixXI, MatrixXI>::what() const {
        return "MatrixInequalityError<MatrixXI, MatrixXI>";
    }
}
