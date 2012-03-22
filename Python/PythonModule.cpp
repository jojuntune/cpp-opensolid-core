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

#include <OpenSolid/Python/config.hpp>

#include <OpenSolid/Core/Common/Error.hpp>
#include <OpenSolid/Python/PythonModule.hpp>

using namespace boost::python;

namespace opensolid
{
    void bindFile();
    void bindObject();
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
        bindFile();
        bindObject();
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
    UnaryMatrixError<MatrixType>::~UnaryMatrixError() {}

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
    BinaryMatrixError<FirstMatrixType, SecondMatrixType>::~BinaryMatrixError() {}

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

    template <class MatrixType>
    VectorComponentError<MatrixType>::~VectorComponentError() {}

    template VectorComponentError<MatrixXd>::~VectorComponentError();
    template VectorComponentError<MatrixXI>::~VectorComponentError();

    template <>
    const char* VectorComponentError<MatrixXd>::what() const {
        return "MatrixXdVectorComponentError";
    }

    template <>
    const char* VectorComponentError<MatrixXI>::what() const {
        return "MatrixXIVectorComponentError";
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

    template <class MatrixType>
    VectorIndexError<MatrixType>::~VectorIndexError() {}

    template VectorIndexError<MatrixXd>::~VectorIndexError();
    template VectorIndexError<MatrixXI>::~VectorIndexError();

    template <>
    const char* VectorIndexError<MatrixXd>::what() const {
        return "MatrixXdVectorIndexError";
    }

    template <>
    const char* VectorIndexError<MatrixXI>::what() const {
        return "MatrixXIVectorIndexError";
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

    template <class MatrixType>
    MatrixIndexError<MatrixType>::~MatrixIndexError() {}

    template MatrixIndexError<MatrixXd>::~MatrixIndexError();
    template MatrixIndexError<MatrixXI>::~MatrixIndexError();

    template <>
    const char* MatrixIndexError<MatrixXd>::what() const {
        return "MatrixXdIndexError";
    }

    template <>
    const char* MatrixIndexError<MatrixXI>::what() const {
        return "MatrixXIIndexError";
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

    template <class MatrixType>
    VectorAssignmentError<MatrixType>::~VectorAssignmentError() {}

    template VectorAssignmentError<MatrixXd>::~VectorAssignmentError();
    template VectorAssignmentError<MatrixXI>::~VectorAssignmentError();

    template <>
    const char* VectorAssignmentError<MatrixXd>::what() const {
        return "MatrixXdVectorAssignmentError";
    }

    template <>
    const char* VectorAssignmentError<MatrixXI>::what() const {
        return "MatrixXIVectorAssignmentError";
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

    template <class MatrixType>
    MatrixAssignmentError<MatrixType>::~MatrixAssignmentError() {}

    template MatrixAssignmentError<MatrixXd>::~MatrixAssignmentError();
    template MatrixAssignmentError<MatrixXI>::~MatrixAssignmentError();

    template <>
    const char* MatrixAssignmentError<MatrixXd>::what() const {
        return "MatrixXdAssignmentError";
    }

    template <>
    const char* MatrixAssignmentError<MatrixXI>::what() const {
        return "MatrixXIAssignmentError";
    }

    template <class MatrixType>
    boost::python::object MatrixAssignmentError<MatrixType>::rowIndex() const {return _row_index;}

    template boost::python::object MatrixAssignmentError<MatrixXd>::rowIndex() const;
    template boost::python::object MatrixAssignmentError<MatrixXI>::rowIndex() const;

    template <class MatrixType>
    boost::python::object MatrixAssignmentError<MatrixType>::colIndex() const {return _col_index;}

    template boost::python::object MatrixAssignmentError<MatrixXd>::colIndex() const;
    template boost::python::object MatrixAssignmentError<MatrixXI>::colIndex() const;

    // MatrixSquaredNormError

    template <class MatrixType>
    MatrixSquaredNormError<MatrixType>::MatrixSquaredNormError(const MatrixType& matrix) :
        UnaryMatrixError<MatrixType>(matrix) {}

    template MatrixSquaredNormError<MatrixXd>::MatrixSquaredNormError(const MatrixXd&);
    template MatrixSquaredNormError<MatrixXI>::MatrixSquaredNormError(const MatrixXI&);

    template <class MatrixType>
    MatrixSquaredNormError<MatrixType>::~MatrixSquaredNormError() {}

    template MatrixSquaredNormError<MatrixXd>::~MatrixSquaredNormError();
    template MatrixSquaredNormError<MatrixXI>::~MatrixSquaredNormError();

    template <>
    const char* MatrixSquaredNormError<MatrixXd>::what() const {
        return "MatrixXdSquaredNormError";
    }

    template <>
    const char* MatrixSquaredNormError<MatrixXI>::what() const {
        return "MatrixXISquaredNormError";
    }

    // MatrixNormError

    template <class MatrixType>
    MatrixNormError<MatrixType>::MatrixNormError(const MatrixType& matrix) :
        UnaryMatrixError<MatrixType>(matrix) {}

    template MatrixNormError<MatrixXd>::MatrixNormError(const MatrixXd&);
    template MatrixNormError<MatrixXI>::MatrixNormError(const MatrixXI&);

    template <class MatrixType>
    MatrixNormError<MatrixType>::~MatrixNormError() {}

    template MatrixNormError<MatrixXd>::~MatrixNormError();
    template MatrixNormError<MatrixXI>::~MatrixNormError();

    template <>
    const char* MatrixNormError<MatrixXd>::what() const {
        return "MatrixXdNormError";
    }

    template <>
    const char* MatrixNormError<MatrixXI>::what() const {
        return "MatrixXINormError";
    }

    // MatrixNormalizedError

    template <class MatrixType>
    MatrixNormalizedError<MatrixType>::MatrixNormalizedError(const MatrixType& matrix) :
        UnaryMatrixError<MatrixType>(matrix) {}

    template MatrixNormalizedError<MatrixXd>::MatrixNormalizedError(const MatrixXd&);
    template MatrixNormalizedError<MatrixXI>::MatrixNormalizedError(const MatrixXI&);

    template <class MatrixType>
    MatrixNormalizedError<MatrixType>::~MatrixNormalizedError() {}

    template MatrixNormalizedError<MatrixXd>::~MatrixNormalizedError();
    template MatrixNormalizedError<MatrixXI>::~MatrixNormalizedError();

    template <>
    const char* MatrixNormalizedError<MatrixXd>::what() const {
        return "MatrixXdNormalizedError";
    }

    template <>
    const char* MatrixNormalizedError<MatrixXI>::what() const {
        return "MatrixXINormalizedError";
    }

    // MatrixDeterminantError

    template <class MatrixType>
    MatrixDeterminantError<MatrixType>::MatrixDeterminantError(const MatrixType& matrix) :
        UnaryMatrixError<MatrixType>(matrix) {}

    template MatrixDeterminantError<MatrixXd>::MatrixDeterminantError(const MatrixXd&);
    template MatrixDeterminantError<MatrixXI>::MatrixDeterminantError(const MatrixXI&);

    template <class MatrixType>
    MatrixDeterminantError<MatrixType>::~MatrixDeterminantError() {}

    template MatrixDeterminantError<MatrixXd>::~MatrixDeterminantError();
    template MatrixDeterminantError<MatrixXI>::~MatrixDeterminantError();

    template <>
    const char* MatrixDeterminantError<MatrixXd>::what() const {
        return "MatrixXdDeterminantError";
    }

    template <>
    const char* MatrixDeterminantError<MatrixXI>::what() const {
        return "MatrixXIDeterminantError";
    }

    // MatrixXdInverseError

    MatrixXdInverseError::MatrixXdInverseError(const MatrixXd& matrix) :
        UnaryMatrixError<MatrixXd>(matrix) {}

    MatrixXdInverseError::~MatrixXdInverseError() {}

    const char* MatrixXdInverseError::what() const {
        return "MatrixXdInverseError";
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

    template <class MatrixType>
    MatrixReplicateError<MatrixType>::~MatrixReplicateError() {}

    template MatrixReplicateError<MatrixXd>::~MatrixReplicateError();
    template MatrixReplicateError<MatrixXI>::~MatrixReplicateError();

    template <>
    const char* MatrixReplicateError<MatrixXd>::what() const {
        return "MatrixXdReplicateError";
    }

    template <>
    const char* MatrixReplicateError<MatrixXI>::what() const {
        return "MatrixXIReplicateError";
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

    template <class FirstMatrixType, class SecondMatrixType>
    MatrixDotProductError<FirstMatrixType, SecondMatrixType>::~MatrixDotProductError() {}

    template MatrixDotProductError<MatrixXd, MatrixXd>::~MatrixDotProductError();
    template MatrixDotProductError<MatrixXd, MatrixXI>::~MatrixDotProductError();
    template MatrixDotProductError<MatrixXI, MatrixXd>::~MatrixDotProductError();
    template MatrixDotProductError<MatrixXI, MatrixXI>::~MatrixDotProductError();

    template <>
    const char* MatrixDotProductError<MatrixXd, MatrixXd>::what() const {
        return "MatrixXdDotProductMatrixXdError";
    }

    template <>
    const char* MatrixDotProductError<MatrixXd, MatrixXI>::what() const {
        return "MatrixXdDotProductMatrixXIError";
    }

    template <>
    const char* MatrixDotProductError<MatrixXI, MatrixXd>::what() const {
        return "MatrixXIDotProductMatrixXdError";
    }

    template <>
    const char* MatrixDotProductError<MatrixXI, MatrixXI>::what() const {
        return "MatrixXIDotProductMatrixXIError";
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

    template <class FirstMatrixType, class SecondMatrixType>
    MatrixCrossProductError<FirstMatrixType, SecondMatrixType>::~MatrixCrossProductError() {}

    template MatrixCrossProductError<MatrixXd, MatrixXd>::~MatrixCrossProductError();
    template MatrixCrossProductError<MatrixXd, MatrixXI>::~MatrixCrossProductError();
    template MatrixCrossProductError<MatrixXI, MatrixXd>::~MatrixCrossProductError();
    template MatrixCrossProductError<MatrixXI, MatrixXI>::~MatrixCrossProductError();

    template <>
    const char* MatrixCrossProductError<MatrixXd, MatrixXd>::what() const {
        return "MatrixXdCrossProductMatrixXdError";
    }

    template <>
    const char* MatrixCrossProductError<MatrixXd, MatrixXI>::what() const {
        return "MatrixXdCrossProductMatrixXIError";
    }

    template <>
    const char* MatrixCrossProductError<MatrixXI, MatrixXd>::what() const {
        return "MatrixXICrossProductMatrixXdError";
    }

    template <>
    const char* MatrixCrossProductError<MatrixXI, MatrixXI>::what() const {
        return "MatrixXICrossProductMatrixXIError";
    }

    // MatrixXIOverlapsMatrixXIError

    MatrixXIOverlapsMatrixXIError::MatrixXIOverlapsMatrixXIError(
        const MatrixXI& first_matrix,
        const MatrixXI& second_matrix
    ) : BinaryMatrixError<MatrixXI, MatrixXI>(first_matrix, second_matrix) {}

    MatrixXIOverlapsMatrixXIError::~MatrixXIOverlapsMatrixXIError() {}

    const char* MatrixXIOverlapsMatrixXIError::what() const {
        return "MatrixXIOverlapsMatrixXIError";
    }

    // MatrixXIContainsError

    template <class SecondMatrixType>
    MatrixXIContainsError<SecondMatrixType>::MatrixXIContainsError(
        const MatrixXI& first_matrix,
        const SecondMatrixType& second_matrix
    ) : BinaryMatrixError<MatrixXI, SecondMatrixType>(first_matrix, second_matrix) {}

    template MatrixXIContainsError<MatrixXd>::MatrixXIContainsError(const MatrixXI&, const MatrixXd&);
    template MatrixXIContainsError<MatrixXI>::MatrixXIContainsError(const MatrixXI&, const MatrixXI&);

    template <class SecondMatrixType>
    MatrixXIContainsError<SecondMatrixType>::~MatrixXIContainsError() {}

    template MatrixXIContainsError<MatrixXd>::~MatrixXIContainsError();
    template MatrixXIContainsError<MatrixXI>::~MatrixXIContainsError();

    template <>
    const char* MatrixXIContainsError<MatrixXd>::what() const {
        return "MatrixXIContainsMatrixXdError";
    }

    template <>
    const char* MatrixXIContainsError<MatrixXI>::what() const {
        return "MatrixXIContainsMatrixXIError";
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

    template <class FirstMatrixType, class SecondMatrixType>
    MatrixHullError<FirstMatrixType, SecondMatrixType>::~MatrixHullError() {}

    template MatrixHullError<MatrixXd, MatrixXd>::~MatrixHullError();
    template MatrixHullError<MatrixXd, MatrixXI>::~MatrixHullError();
    template MatrixHullError<MatrixXI, MatrixXd>::~MatrixHullError();
    template MatrixHullError<MatrixXI, MatrixXI>::~MatrixHullError();

    template <>
    const char* MatrixHullError<MatrixXd, MatrixXd>::what() const {
        return "MatrixXdHullMatrixXdError";
    }

    template <>
    const char* MatrixHullError<MatrixXd, MatrixXI>::what() const {
        return "MatrixXdHullMatrixXIError";
    }

    template <>
    const char* MatrixHullError<MatrixXI, MatrixXd>::what() const {
        return "MatrixXIHullMatrixXdError";
    }

    template <>
    const char* MatrixHullError<MatrixXI, MatrixXI>::what() const {
        return "MatrixXIHullMatrixXIError";
    }

    // MatrixIntersectionError

    MatrixXIIntersectionMatrixXIError::MatrixXIIntersectionMatrixXIError(
        const MatrixXI& first_matrix,
        const MatrixXI& second_matrix
    ) : BinaryMatrixError<MatrixXI, MatrixXI>(first_matrix, second_matrix) {}

    MatrixXIIntersectionMatrixXIError::~MatrixXIIntersectionMatrixXIError() {}

    const char* MatrixXIIntersectionMatrixXIError::what() const {
        return "MatrixXIIntersectionMatrixXIError";
    }

    // MatrixFactoryError

    MatrixFactoryError::MatrixFactoryError(int rows, int cols) : _rows(rows), _cols(cols) {}

    MatrixFactoryError::~MatrixFactoryError() {}

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

    template <class MatrixType>
    ConstantMatrixConstructionError<MatrixType>::~ConstantMatrixConstructionError() {}

    template ConstantMatrixConstructionError<MatrixXd>::~ConstantMatrixConstructionError();
    template ConstantMatrixConstructionError<MatrixXI>::~ConstantMatrixConstructionError();

    template <>
    const char* ConstantMatrixConstructionError<MatrixXd>::what() const {
        return "ConstantMatrixXdConstructionError";
    }

    template <>
    const char* ConstantMatrixConstructionError<MatrixXI>::what() const {
        return "ConstantMatrixXIConstructionError";
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

    template <class MatrixType>
    ZeroMatrixConstructionError<MatrixType>::~ZeroMatrixConstructionError() {}

    template ZeroMatrixConstructionError<MatrixXd>::~ZeroMatrixConstructionError();
    template ZeroMatrixConstructionError<MatrixXI>::~ZeroMatrixConstructionError();

    template <>
    const char* ZeroMatrixConstructionError<MatrixXd>::what() const {
        return "ZeroMatrixXdConstructionError";
    }

    template <>
    const char* ZeroMatrixConstructionError<MatrixXI>::what() const {
        return "ZeroMatrixXIConstructionError";
    }

    // OnesMatrixConstructionError

    template <class MatrixType>
    OnesMatrixConstructionError<MatrixType>::OnesMatrixConstructionError(int rows, int cols) :
        MatrixFactoryError(rows, cols) {}

    template OnesMatrixConstructionError<MatrixXd>::OnesMatrixConstructionError(int, int);
    template OnesMatrixConstructionError<MatrixXI>::OnesMatrixConstructionError(int, int);

    template <class MatrixType>
    OnesMatrixConstructionError<MatrixType>::~OnesMatrixConstructionError() {}

    template OnesMatrixConstructionError<MatrixXd>::~OnesMatrixConstructionError();
    template OnesMatrixConstructionError<MatrixXI>::~OnesMatrixConstructionError();

    template <>
    const char* OnesMatrixConstructionError<MatrixXd>::what() const {
        return "OnesMatrixXdConstructionError";
    }

    template <>
    const char* OnesMatrixConstructionError<MatrixXI>::what() const {
        return "OnesMatrixXIConstructionError";
    }

    // RandomMatrixConstructionError

    template <class MatrixType>
    RandomMatrixConstructionError<MatrixType>::RandomMatrixConstructionError(int rows, int cols) :
        MatrixFactoryError(rows, cols) {}

    template RandomMatrixConstructionError<MatrixXd>::RandomMatrixConstructionError(int, int);
    template RandomMatrixConstructionError<MatrixXI>::RandomMatrixConstructionError(int, int);

    template <class MatrixType>
    RandomMatrixConstructionError<MatrixType>::~RandomMatrixConstructionError() {}

    template RandomMatrixConstructionError<MatrixXd>::~RandomMatrixConstructionError();
    template RandomMatrixConstructionError<MatrixXI>::~RandomMatrixConstructionError();

    template <>
    const char* RandomMatrixConstructionError<MatrixXd>::what() const {
        return "RandomMatrixXdConstructionError";
    }

    template <>
    const char* RandomMatrixConstructionError<MatrixXI>::what() const {
        return "RandomMatrixXIConstructionError";
    }

    // IdentityMatrixConstructionError

    template <class MatrixType>
    IdentityMatrixConstructionError<MatrixType>::IdentityMatrixConstructionError(int rows, int cols) :
        MatrixFactoryError(rows, cols) {}

    template IdentityMatrixConstructionError<MatrixXd>::IdentityMatrixConstructionError(int, int);
    template IdentityMatrixConstructionError<MatrixXI>::IdentityMatrixConstructionError(int, int);

    template <class MatrixType>
    IdentityMatrixConstructionError<MatrixType>::~IdentityMatrixConstructionError() {}

    template IdentityMatrixConstructionError<MatrixXd>::~IdentityMatrixConstructionError();
    template IdentityMatrixConstructionError<MatrixXI>::~IdentityMatrixConstructionError();

    template <>
    const char* IdentityMatrixConstructionError<MatrixXd>::what() const {
        return "IdentityMatrixXdConstructionError";
    }

    template <>
    const char* IdentityMatrixConstructionError<MatrixXI>::what() const {
        return "IdentityMatrixXIConstructionError";
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

    template <class FirstMatrixType, class SecondMatrixType>
    MatrixSumError<FirstMatrixType, SecondMatrixType>::~MatrixSumError() {}

    template MatrixSumError<MatrixXd, MatrixXd>::~MatrixSumError();
    template MatrixSumError<MatrixXd, MatrixXI>::~MatrixSumError();
    template MatrixSumError<MatrixXI, MatrixXd>::~MatrixSumError();
    template MatrixSumError<MatrixXI, MatrixXI>::~MatrixSumError();

    template <>
    const char* MatrixSumError<MatrixXd, MatrixXd>::what() const {
        return "MatrixXdSumMatrixXdError";
    }

    template <>
    const char* MatrixSumError<MatrixXd, MatrixXI>::what() const {
        return "MatrixXdSumMatrixXIError";
    }

    template <>
    const char* MatrixSumError<MatrixXI, MatrixXd>::what() const {
        return "MatrixXISumMatrixXdError";
    }

    template <>
    const char* MatrixSumError<MatrixXI, MatrixXI>::what() const {
        return "MatrixXISumMatrixXIError";
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

    template <class FirstMatrixType, class SecondMatrixType>
    MatrixDifferenceError<FirstMatrixType, SecondMatrixType>::~MatrixDifferenceError() {}

    template MatrixDifferenceError<MatrixXd, MatrixXd>::~MatrixDifferenceError();
    template MatrixDifferenceError<MatrixXd, MatrixXI>::~MatrixDifferenceError();
    template MatrixDifferenceError<MatrixXI, MatrixXd>::~MatrixDifferenceError();
    template MatrixDifferenceError<MatrixXI, MatrixXI>::~MatrixDifferenceError();

    template <>
    const char* MatrixDifferenceError<MatrixXd, MatrixXd>::what() const {
        return "MatrixXdDifferenceMatrixXdError";
    }

    template <>
    const char* MatrixDifferenceError<MatrixXd, MatrixXI>::what() const {
        return "MatrixXdDifferenceMatrixXIError";
    }

    template <>
    const char* MatrixDifferenceError<MatrixXI, MatrixXd>::what() const {
        return "MatrixXIDifferenceMatrixXdError";
    }

    template <>
    const char* MatrixDifferenceError<MatrixXI, MatrixXI>::what() const {
        return "MatrixXIDifferenceMatrixXIError";
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

    template <class FirstMatrixType, class ScalarType>
    MatrixQuotientError<FirstMatrixType, ScalarType>::~MatrixQuotientError() {}

    template MatrixQuotientError<MatrixXd, double>::~MatrixQuotientError();
    template MatrixQuotientError<MatrixXd, Interval>::~MatrixQuotientError();
    template MatrixQuotientError<MatrixXI, double>::~MatrixQuotientError();
    template MatrixQuotientError<MatrixXI, Interval>::~MatrixQuotientError();

    template <>
    const char* MatrixQuotientError<MatrixXd, double>::what() const {
        return "MatrixXdQuotientDoubleError";
    }

    template <>
    const char* MatrixQuotientError<MatrixXd, Interval>::what() const {
        return "MatrixXdQuotientIntervalError";
    }

    template <>
    const char* MatrixQuotientError<MatrixXI, double>::what() const {
        return "MatrixXIQuotientDoubleError";
    }

    template <>
    const char* MatrixQuotientError<MatrixXI, Interval>::what() const {
        return "MatrixXIQuotientIntervalError";
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

    template <class FirstMatrixType, class SecondMatrixType>
    MatrixProductError<FirstMatrixType, SecondMatrixType>::~MatrixProductError() {}

    template MatrixProductError<MatrixXd, MatrixXd>::~MatrixProductError();
    template MatrixProductError<MatrixXd, MatrixXI>::~MatrixProductError();
    template MatrixProductError<MatrixXI, MatrixXd>::~MatrixProductError();
    template MatrixProductError<MatrixXI, MatrixXI>::~MatrixProductError();

    template <>
    const char* MatrixProductError<MatrixXd, MatrixXd>::what() const {
        return "MatrixXdProductMatrixXdError";
    }

    template <>
    const char* MatrixProductError<MatrixXd, MatrixXI>::what() const {
        return "MatrixXdProductMatrixXIError";
    }

    template <>
    const char* MatrixProductError<MatrixXI, MatrixXd>::what() const {
        return "MatrixXIProductMatrixXdError";
    }

    template <>
    const char* MatrixProductError<MatrixXI, MatrixXI>::what() const {
        return "MatrixXIProductMatrixXIError";
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

    template <class FirstMatrixType, class SecondMatrixType>
    MatrixEqualityError<FirstMatrixType, SecondMatrixType>::~MatrixEqualityError() {}

    template MatrixEqualityError<MatrixXd, MatrixXd>::~MatrixEqualityError();
    template MatrixEqualityError<MatrixXd, MatrixXI>::~MatrixEqualityError();
    template MatrixEqualityError<MatrixXI, MatrixXd>::~MatrixEqualityError();
    template MatrixEqualityError<MatrixXI, MatrixXI>::~MatrixEqualityError();

    template <>
    const char* MatrixEqualityError<MatrixXd, MatrixXd>::what() const {
        return "MatrixXdEqualityMatrixXdError";
    }

    template <>
    const char* MatrixEqualityError<MatrixXd, MatrixXI>::what() const {
        return "MatrixXdEqualityMatrixXIError";
    }

    template <>
    const char* MatrixEqualityError<MatrixXI, MatrixXd>::what() const {
        return "MatrixXIEqualityMatrixXdError";
    }

    template <>
    const char* MatrixEqualityError<MatrixXI, MatrixXI>::what() const {
        return "MatrixXIEqualityMatrixXIError";
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

    template <class FirstMatrixType, class SecondMatrixType>
    MatrixInequalityError<FirstMatrixType, SecondMatrixType>::~MatrixInequalityError() {}

    template MatrixInequalityError<MatrixXd, MatrixXd>::~MatrixInequalityError();
    template MatrixInequalityError<MatrixXd, MatrixXI>::~MatrixInequalityError();
    template MatrixInequalityError<MatrixXI, MatrixXd>::~MatrixInequalityError();
    template MatrixInequalityError<MatrixXI, MatrixXI>::~MatrixInequalityError();

    template <>
    const char* MatrixInequalityError<MatrixXd, MatrixXd>::what() const {
        return "MatrixXdInequalityMatrixXdError";
    }

    template <>
    const char* MatrixInequalityError<MatrixXd, MatrixXI>::what() const {
        return "MatrixXdInequalityMatrixXIError";
    }

    template <>
    const char* MatrixInequalityError<MatrixXI, MatrixXd>::what() const {
        return "MatrixXIInequalityMatrixXdError";
    }

    template <>
    const char* MatrixInequalityError<MatrixXI, MatrixXI>::what() const {
        return "MatrixXIInequalityMatrixXIError";
    }

    template <class MatrixType>
    MatrixCopyConstructionError<MatrixType>::MatrixCopyConstructionError(
        const MatrixType& argument
    ) : _argument(argument) {}
    
    template <class MatrixType>
    MatrixCopyConstructionError<MatrixType>::~MatrixCopyConstructionError() {}

    template <class MatrixType>
    MatrixType MatrixCopyConstructionError<MatrixType>::argument() const {return _argument;}

    template class MatrixCopyConstructionError<MatrixXd>;
    template class MatrixCopyConstructionError<MatrixXI>;

    Vector2dCopyConstructionError::Vector2dCopyConstructionError(const MatrixXd& argument) :
        MatrixCopyConstructionError<MatrixXd>(argument) {}
    
    Vector2dCopyConstructionError::~Vector2dCopyConstructionError() {}

    const char* Vector2dCopyConstructionError::what() const {
        return "Vector2dCopyConstructionError";
    }

    Vector3dCopyConstructionError::Vector3dCopyConstructionError(const MatrixXd& argument) :
        MatrixCopyConstructionError<MatrixXd>(argument) {}
    
    Vector3dCopyConstructionError::~Vector3dCopyConstructionError() {}

    const char* Vector3dCopyConstructionError::what() const {
        return "Vector3dCopyConstructionError";
    }

    VectorXdCopyConstructionError::VectorXdCopyConstructionError(const MatrixXd& argument) :
        MatrixCopyConstructionError<MatrixXd>(argument) {}
    
    VectorXdCopyConstructionError::~VectorXdCopyConstructionError() {}

    const char* VectorXdCopyConstructionError::what() const {
        return "VectorXdCopyConstructionError";
    }

    RowVector2dCopyConstructionError::RowVector2dCopyConstructionError(const MatrixXd& argument) :
        MatrixCopyConstructionError<MatrixXd>(argument) {}
    
    RowVector2dCopyConstructionError::~RowVector2dCopyConstructionError() {}

    const char* RowVector2dCopyConstructionError::what() const {
        return "RowVector2dCopyConstructionError";
    }

    RowVector3dCopyConstructionError::RowVector3dCopyConstructionError(const MatrixXd& argument) :
        MatrixCopyConstructionError<MatrixXd>(argument) {}
    
    RowVector3dCopyConstructionError::~RowVector3dCopyConstructionError() {}

    const char* RowVector3dCopyConstructionError::what() const {
        return "RowVector3dCopyConstructionError";
    }

    RowVectorXdCopyConstructionError::RowVectorXdCopyConstructionError(const MatrixXd& argument) :
        MatrixCopyConstructionError<MatrixXd>(argument) {}
    
    RowVectorXdCopyConstructionError::~RowVectorXdCopyConstructionError() {}

    const char* RowVectorXdCopyConstructionError::what() const {
        return "RowVectorXdCopyConstructionError";
    }

    Matrix2dCopyConstructionError::Matrix2dCopyConstructionError(const MatrixXd& argument) :
        MatrixCopyConstructionError<MatrixXd>(argument) {}
    
    Matrix2dCopyConstructionError::~Matrix2dCopyConstructionError() {}

    const char* Matrix2dCopyConstructionError::what() const {
        return "Matrix2dCopyConstructionError";
    }

    Matrix3dCopyConstructionError::Matrix3dCopyConstructionError(const MatrixXd& argument) :
        MatrixCopyConstructionError<MatrixXd>(argument) {}
    
    Matrix3dCopyConstructionError::~Matrix3dCopyConstructionError() {}

    const char* Matrix3dCopyConstructionError::what() const {
        return "Matrix3dCopyConstructionError";
    }

    Vector2ICopyConstructionError::Vector2ICopyConstructionError(const MatrixXI& argument) :
        MatrixCopyConstructionError<MatrixXI>(argument) {}
    
    Vector2ICopyConstructionError::~Vector2ICopyConstructionError() {}

    const char* Vector2ICopyConstructionError::what() const {
        return "Vector2ICopyConstructionError";
    }

    Vector3ICopyConstructionError::Vector3ICopyConstructionError(const MatrixXI& argument) :
        MatrixCopyConstructionError<MatrixXI>(argument) {}
    
    Vector3ICopyConstructionError::~Vector3ICopyConstructionError() {}

    const char* Vector3ICopyConstructionError::what() const {
        return "Vector3ICopyConstructionError";
    }

    VectorXICopyConstructionError::VectorXICopyConstructionError(const MatrixXI& argument) :
        MatrixCopyConstructionError<MatrixXI>(argument) {}
    
    VectorXICopyConstructionError::~VectorXICopyConstructionError() {}

    const char* VectorXICopyConstructionError::what() const {
        return "VectorXICopyConstructionError";
    }

    RowVector2ICopyConstructionError::RowVector2ICopyConstructionError(const MatrixXI& argument) :
        MatrixCopyConstructionError<MatrixXI>(argument) {}
    
    RowVector2ICopyConstructionError::~RowVector2ICopyConstructionError() {}

    const char* RowVector2ICopyConstructionError::what() const {
        return "RowVector2ICopyConstructionError";
    }

    RowVector3ICopyConstructionError::RowVector3ICopyConstructionError(const MatrixXI& argument) :
        MatrixCopyConstructionError<MatrixXI>(argument) {}
    
    RowVector3ICopyConstructionError::~RowVector3ICopyConstructionError() {}

    const char* RowVector3ICopyConstructionError::what() const {
        return "RowVector3ICopyConstructionError";
    }

    RowVectorXICopyConstructionError::RowVectorXICopyConstructionError(const MatrixXI& argument) :
        MatrixCopyConstructionError<MatrixXI>(argument) {}
    
    RowVectorXICopyConstructionError::~RowVectorXICopyConstructionError() {}

    const char* RowVectorXICopyConstructionError::what() const {
        return "RowVectorXICopyConstructionError";
    }

    Matrix2ICopyConstructionError::Matrix2ICopyConstructionError(const MatrixXI& argument) :
        MatrixCopyConstructionError<MatrixXI>(argument) {}
    
    Matrix2ICopyConstructionError::~Matrix2ICopyConstructionError() {}

    const char* Matrix2ICopyConstructionError::what() const {
        return "Matrix2ICopyConstructionError";
    }

    Matrix3ICopyConstructionError::Matrix3ICopyConstructionError(const MatrixXI& argument) :
        MatrixCopyConstructionError<MatrixXI>(argument) {}
    
    Matrix3ICopyConstructionError::~Matrix3ICopyConstructionError() {}

    const char* Matrix3ICopyConstructionError::what() const {
        return "Matrix3ICopyConstructionError";
    }

    UnitVectorConstructionError::UnitVectorConstructionError(int index) : _index(index) {}
    
    UnitVectorConstructionError::~UnitVectorConstructionError() {}

    int UnitVectorConstructionError::index() const {return _index;}

    DynamicUnitVectorConstructionError::DynamicUnitVectorConstructionError(int size, int index) :
        UnitVectorConstructionError(index), _size(size) {}
    
    DynamicUnitVectorConstructionError::~DynamicUnitVectorConstructionError() {}

    int DynamicUnitVectorConstructionError::size() const {return _size;}

    UnitVector2dConstructionError::UnitVector2dConstructionError(int index) :
        UnitVectorConstructionError(index) {}
    
    UnitVector2dConstructionError::~UnitVector2dConstructionError() {}

    const char* UnitVector2dConstructionError::what() const {
        return "UnitVector2dConstructionError";
    }

    UnitVector3dConstructionError::UnitVector3dConstructionError(int index) :
        UnitVectorConstructionError(index) {}
    
    UnitVector3dConstructionError::~UnitVector3dConstructionError() {}

    const char* UnitVector3dConstructionError::what() const {
        return "UnitVector3dConstructionError";
    }

    UnitVectorXdConstructionError::UnitVectorXdConstructionError(int size, int index) :
        DynamicUnitVectorConstructionError(size, index) {}
    
    UnitVectorXdConstructionError::~UnitVectorXdConstructionError() {}

    const char* UnitVectorXdConstructionError::what() const {
        return "UnitVectorXdConstructionError";
    }

    UnitRowVector2dConstructionError::UnitRowVector2dConstructionError(int index) :
        UnitVectorConstructionError(index) {}
    
    UnitRowVector2dConstructionError::~UnitRowVector2dConstructionError() {}

    const char* UnitRowVector2dConstructionError::what() const {
        return "UnitRowVector2dConstructionError";
    }

    UnitRowVector3dConstructionError::UnitRowVector3dConstructionError(int index) :
        UnitVectorConstructionError(index) {}
    
    UnitRowVector3dConstructionError::~UnitRowVector3dConstructionError() {}

    const char* UnitRowVector3dConstructionError::what() const {
        return "UnitRowVector3dConstructionError";
    }

    UnitRowVectorXdConstructionError::UnitRowVectorXdConstructionError(int size, int index) :
        DynamicUnitVectorConstructionError(size, index) {}
    
    UnitRowVectorXdConstructionError::~UnitRowVectorXdConstructionError() {}

    const char* UnitRowVectorXdConstructionError::what() const {
        return "UnitRowVectorXdConstructionError";
    }

    UnitVector2IConstructionError::UnitVector2IConstructionError(int index) :
        UnitVectorConstructionError(index) {}
    
    UnitVector2IConstructionError::~UnitVector2IConstructionError() {}

    const char* UnitVector2IConstructionError::what() const {
        return "UnitVector2IConstructionError";
    }

    UnitVector3IConstructionError::UnitVector3IConstructionError(int index) :
        UnitVectorConstructionError(index) {}
    
    UnitVector3IConstructionError::~UnitVector3IConstructionError() {}

    const char* UnitVector3IConstructionError::what() const {
        return "UnitVector3IConstructionError";
    }

    UnitVectorXIConstructionError::UnitVectorXIConstructionError(int size, int index) :
        DynamicUnitVectorConstructionError(size, index) {}
    
    UnitVectorXIConstructionError::~UnitVectorXIConstructionError() {}

    const char* UnitVectorXIConstructionError::what() const {
        return "UnitVectorXIConstructionError";
    }

    UnitRowVector2IConstructionError::UnitRowVector2IConstructionError(int index) :
        UnitVectorConstructionError(index) {}
    
    UnitRowVector2IConstructionError::~UnitRowVector2IConstructionError() {}

    const char* UnitRowVector2IConstructionError::what() const {
        return "UnitRowVector2IConstructionError";
    }

    UnitRowVector3IConstructionError::UnitRowVector3IConstructionError(int index) :
        UnitVectorConstructionError(index) {}
    
    UnitRowVector3IConstructionError::~UnitRowVector3IConstructionError() {}

    const char* UnitRowVector3IConstructionError::what() const {
        return "UnitRowVector3IConstructionError";
    }

    UnitRowVectorXIConstructionError::UnitRowVectorXIConstructionError(int size, int index) :
        DynamicUnitVectorConstructionError(size, index) {}
    
    UnitRowVectorXIConstructionError::~UnitRowVectorXIConstructionError() {}

    const char* UnitRowVectorXIConstructionError::what() const {
        return "UnitRowVectorXIConstructionError";
    }
}
