/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef OPENSOLID__MATRIXBASE_HPP
#define OPENSOLID__MATRIXBASE_HPP

#include <cstdlib>

#include <OpenSolid/Value/Eigen.hpp>
#include <OpenSolid/Value/Double.hpp>
#include <OpenSolid/Value/Interval.hpp>
#include <OpenSolid/Value/declarations.hpp>
#include <OpenSolid/Value/Range.hpp>

namespace Eigen
{
    namespace internal
    {
        template <class ScalarType>
        struct traits<OpenSolid::MatrixBase<ScalarType>>
        {
            typedef ScalarType Scalar;
            typedef int Index;
            typedef Dense StorageKind;
            static const int RowsAtCompileTime = Dynamic;
            static const int ColsAtCompileTime = Dynamic;
            static const int MaxRowsAtCompileTime = Dynamic;
            static const int MaxColsAtCompileTime = Dynamic;
            static const int Flags = LvalueBit | DirectAccessBit;
            static const int CoeffReadCost = 2;
        };
    }
}

namespace OpenSolid
{
    template <class ScalarType>
    class MatrixBase : protected Eigen::MatrixBase<MatrixBase<ScalarType>>
    {
    private:
        int _rows;
        int _cols;
        int _stride;
        ScalarType* _data;
        ScalarType* _owned;
        
        typedef Eigen::MatrixBase<MatrixBase<ScalarType>> Base;
        friend class Base;
        ScalarType& coeffRef(int index);
        const ScalarType& coeff(int index) const;
        ScalarType& coeffRef(int row, int col);
        const ScalarType& coeff(int row, int col) const;
        
        friend class VectorBase<ScalarType>;
    protected:
        Base& base();
        const Base& base() const;
        
        Matrix<ScalarType>& derived();
        const Matrix<ScalarType>& derived() const;
        
        void init();
        void init(int rows, int cols);
        void init(Matrix<ScalarType>&& argument);
        
        void assign(const ScalarType& argument);
        void assign(const Vector<ScalarType>& argument);
        void assign(const Matrix<ScalarType>& argument);
    public:
        typedef ScalarType Scalar;
        typedef Matrix<Interval> Bounds;
        
        ~MatrixBase();
        
        void operator=(const ScalarType& argument);
        void operator=(const Vector<ScalarType>& argument);
        
        int rows() const;
        int cols() const;
        int size() const;
        
        ScalarType& operator()(int index);
        const ScalarType& operator()(int index) const;
        ScalarType& operator()(int row, int col);
        const ScalarType& operator()(int row, int col) const;
        
        Matrix<ScalarType> row(int index);
        const Matrix<ScalarType> row(int index) const;
        Matrix<ScalarType> col(int index);
        const Matrix<ScalarType> col(int index) const;
        
        Matrix<ScalarType> operator()(Range index_range);
        const Matrix<ScalarType> operator()(Range index_range) const;
        Matrix<ScalarType> operator()(Range row_range, Range col_range);
        const Matrix<ScalarType> operator()(Range row_range, Range col_range) const;
        
        template <class PredicateType>
        bool all(PredicateType predicate = PredicateType()) const;
        
        template <class PredicateType>
        bool any(PredicateType predicate = PredicateType()) const;
        
        template <class FunctionType>
        auto unaryExpr(FunctionType function = FunctionType()) const ->
            Matrix<decltype(function(ScalarType()))>;
        
        template <class FunctionType>
        auto binaryExpr(
            const Matrix<ScalarType>& argument,
            FunctionType function = FunctionType()
        ) const -> Matrix<decltype(function(ScalarType(), ScalarType()))>;
        
        template <class FunctionType>
        auto binaryExpr(
            const Matrix<typename ScalarType::OtherScalar>& argument,
            FunctionType function = FunctionType()
        ) const -> Matrix<decltype(function(ScalarType(), typename ScalarType::OtherScalar()))>;
        
        ScalarType sum() const;
        
        Matrix<ScalarType> cwiseProduct(const Matrix<ScalarType>& argument) const;
        
        Matrix<Interval> cwiseProduct(
            const Matrix<typename ScalarType::OtherScalar>& argument
        ) const;
        
        Matrix<ScalarType> cwiseQuotient(const Matrix<ScalarType>& argument) const;
        
        Matrix<Interval> cwiseQuotient(
            const Matrix<typename ScalarType::OtherScalar>& argument
        ) const;
        
        ScalarType dot(const Vector<ScalarType>& argument) const;
        Interval dot(const Vector<typename ScalarType::OtherScalar>& argument) const;
        
        Vector<ScalarType> cross(const Vector<ScalarType>& argument) const;
        Vector<Interval> cross(const Vector<typename ScalarType::OtherScalar>& argument) const;
        
        ScalarType norm() const;
        ScalarType squaredNorm() const;
        Vector<ScalarType> normalized() const;
        
        Matrix<ScalarType> transpose() const;
        ScalarType determinant() const;
        
        bool isZero(double precision = OPENSOLID_PRECISION) const;
        
        bool isEqualTo(
            const Matrix<ScalarType>& argument,
            double precision = OPENSOLID_PRECISION
        ) const;
        
        static Matrix<ScalarType> Zero(int size);
        static Matrix<ScalarType> Zero(int rows, int cols);
        static Matrix<ScalarType> Ones(int size);
        static Matrix<ScalarType> Ones(int rows, int cols);
        static Matrix<ScalarType> Identity(int size);
        static Matrix<ScalarType> Identity(int rows, int cols);
        static Matrix<ScalarType> Random(int size);
        static Matrix<ScalarType> Random(int rows, int cols);
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    template <class ScalarType>
    inline ScalarType& MatrixBase<ScalarType>::coeffRef(int index) {
        assert(cols() == 1 || rows() == 1);
        assert(index >= 0 && index < size());
        return *(_data + index * (cols() == 1 ? 1 : _stride));
    }
    
    template <class ScalarType>
    inline const ScalarType& MatrixBase<ScalarType>::coeff(int index) const {
        assert(cols() == 1 || rows() == 1);
        assert(index >= 0 && index < size());
        return *(_data + index * (cols() == 1 ? 1 : _stride));
    }
    
    template <class ScalarType>
    inline ScalarType& MatrixBase<ScalarType>::coeffRef(int row, int col) {
        assert(row >= 0 && row < rows());
        assert(col >= 0 && col < cols());
        return *(_data + col * _stride + row);
    }
    
    template <class ScalarType>
    inline const ScalarType& MatrixBase<ScalarType>::coeff(int row, int col) const {
        assert(row >= 0 && row < rows());
        assert(col >= 0 && col < cols());
        return *(_data + col * _stride + row);
    }
    
    template <class ScalarType>
    inline Eigen::MatrixBase<MatrixBase<ScalarType>>& MatrixBase<ScalarType>::base() {
        return *this;
    }
    
    template <class ScalarType>
    inline const Eigen::MatrixBase<MatrixBase<ScalarType>>& MatrixBase<ScalarType>::base() const {
        return *this;
    }
    
    template <class ScalarType>
    inline Matrix<ScalarType>& MatrixBase<ScalarType>::derived() {
        return static_cast<Matrix<ScalarType>&>(*this);
    }
    
    template <class ScalarType>
    inline const Matrix<ScalarType>& MatrixBase<ScalarType>::derived() const {
        return static_cast<const Matrix<ScalarType>&>(*this);
    }
    
    template <class ScalarType>
    inline void MatrixBase<ScalarType>::init() {
        _rows = 0;
        _cols = 0;
        _stride = 0;
        _data = nullptr;
        _owned = nullptr;
    }
    
    template <class ScalarType>
    inline void MatrixBase<ScalarType>::init(int rows, int cols) {
        _rows = rows;
        _cols = cols;
        _stride = rows;
        _data = std::malloc(rows * cols * sizeof(ScalarType));
        _owned = data;
    }
    
    template <class ScalarType>
    inline void MatrixBase<ScalarType>::init(Matrix<ScalarType>&& argument) {
        _rows = argument._rows;
        _cols = argument._cols;
        _stride = argument._stride;
        _data = argument._data;
        _owned = _data;
        argument._owned = nullptr;
    }
        
    template <class ScalarType>
    inline void MatrixBase<ScalarType>::assign(const ScalarType& argument) {
        assert(rows() == 1);
        assert(cols() == 1);
        *_data = argument;
    }
    
    template <class ScalarType>
    inline void MatrixBase<ScalarType>::assign(const Vector<ScalarType>& argument) {
        assert(rows() == argument.size());
        assert(cols() == 1);
        base() = argument.base();
    }
    
    template <class ScalarType>
    inline void MatrixBase<ScalarType>::assign(const Matrix<ScalarType>& argument) {
        assert(rows() == argument.rows());
        assert(cols() == argument.cols());
        base() = argument.base();
    }
    
    template <class ScalarType>
    inline MatrixBase<ScalarType>::~MatrixBase() {if (_owned) {std::free(_owned);}}
    
    template <class ScalarType>
    inline void MatrixBase<ScalarType>::operator=(const ScalarType& argument) {
        assign(argument);
    }
    
    template <class ScalarType>
    inline void MatrixBase<ScalarType>::operator=(const Vector<ScalarType>& argument) {
        assign(argument);
    }
    
    template <class ScalarType>
    inline int MatrixBase<ScalarType>::rows() const {return _rows;}
    
    template <class ScalarType>
    inline int MatrixBase<ScalarType>::cols() const {return _cols;}
    
    template <class ScalarType>
    inline int MatrixBase<ScalarType>::size() const {return _rows * _cols;}
    
    template <class ScalarType>
    inline ScalarType& MatrixBase<ScalarType>::operator()(int index) {
        return coeffRef(index);
    }
    
    template <class ScalarType>
    inline const ScalarType& MatrixBase<ScalarType>::operator()(int index) const {
        return coeff(index);
    }
    
    template <class ScalarType>
    inline ScalarType& MatrixBase<ScalarType>::operator()(int row, int col) {
        return coeffRef(row, col);
    }
    
    template <class ScalarType>
    inline const ScalarType& MatrixBase<ScalarType>::operator()(int row, int col) const {
        return coeff(row, col);
    }
    
    template <class ScalarType>
    inline Matrix<ScalarType> MatrixBase<ScalarType>::row(int index) {
        return operator()(index, All());
    }
    
    template <class ScalarType>
    inline const Matrix<ScalarType> MatrixBase<ScalarType>::row(int index) const {
        return operator()(index, All())
    }
    
    template <class ScalarType>
    inline Matrix<ScalarType> MatrixBase<ScalarType>::col(int index) {
        return operator()(All(), index);
    }
    
    template <class ScalarType>
    inline const Matrix<ScalarType> MatrixBase<ScalarType>::col(int index) const {
        return operator()(All(), index);
    }
    
    template <class ScalarType>
    inline Matrix<ScalarType> MatrixBase<ScalarType>::operator()(Range index_range) {
        assert(rows() == 1 || cols() == 1);
        return rows() == 1 ? operator()(0, index_range) : operator()(index_range, 0);
    }
    
    template <class ScalarType>
    inline const Matrix<ScalarType> MatrixBase<ScalarType>::operator()(Range index_range) const {
        assert(rows() == 1 || cols() == 1);
        return rows() == 1 ? operator()(0, index_range) : operator()(index_range, 0);
    }
    
    template <class ScalarType>
    inline Matrix<ScalarType> MatrixBase<ScalarType>::operator()(
        Range row_range,
        Range col_range
    ) {
        Matrix<ScalarType> result;
        result._rows = row_range.size(rows());
        result._cols = col_range.size(cols());
        result._stride = _stride;
        result._data = _data + row_range.start(rows()) + col_range.start(cols()) * _stride;
        result._owned = nullptr;
        return std::move(result);
    }
    
    template <class ScalarType>
    inline const Matrix<ScalarType> MatrixBase<ScalarType>::operator()(
        Range row_range,
        Range col_range
    ) const {
        Matrix<ScalarType> result;
        result._rows = row_range.size(rows());
        result._cols = col_range.size(cols());
        result._stride = _stride;
        result._data = _data + row_range.start(rows()) + col_range.start(cols()) * _stride;
        result._owned = nullptr;
        return std::move(result);
    }
    
    template <class ScalarType>
    inline template <class FunctionType>
    auto MatrixBase<ScalarType>::unaryExpr(FunctionType function = FunctionType()) const ->
        Matrix<decltype(function(ScalarType()))> {
        Matrix<decltype(function(ScalarType()))> result;
        result.init(rows(), cols());
        for (int j = 0; j < cols(); ++j) {
            for (int i = 0; i < rows(); ++i) {
                result(i, j) = function(operator()(i, j));
            }
        }
        return std::move(result);
    }
    
    template <class ScalarType> template <class FunctionType>
    inline auto MatrixBase<ScalarType>::binaryExpr(
        const Matrix<ScalarType>& argument,
        FunctionType function = FunctionType()
    ) const -> Matrix<decltype(function(ScalarType(), ScalarType()))> {
        assert(argument.rows() == rows());
        assert(argument.cols() == cols());
        Matrix<decltype(function(ScalarType(), ScalarType()))> result;
        result.init(rows(), cols());
        for (int j = 0; j < cols(); ++j) {
            for (int i = 0; i < rows(); ++i) {
                result(i, j) = function(operator()(i, j), argument(i, j));
            }
        }
        return std::move(result);
    }
        
    template <class ScalarType> template <class PredicateType>
    bool MatrixBase<ScalarType>::all(PredicateType predicate = PredicateType()) const {
        for (int j = 0; j < cols(); ++j) {
            for (int i = 0; i < rows(); ++i) {
                if (!predicate(operator()(i, j))) {return false;}
            }
        }
        return true;
    }
    
    template <class ScalarType> template <class PredicateType>
    bool MatrixBase<ScalarType>::any(PredicateType predicate = PredicateType()) const {
        for (int j = 0; j < cols(); ++j) {
            for (int i = 0; i < rows(); ++i) {
                if (predicate(operator()(i, j))) {return true;}
            }
        }
        return false;
    }
    
    template <class ScalarType> template <class FunctionType>
    inline auto MatrixBase<ScalarType>::binaryExpr(
        const Matrix<typename ScalarType::OtherScalar>& argument,
        FunctionType function = FunctionType()
    ) const -> Matrix<decltype(function(ScalarType(), typename ScalarType::OtherScalar()))> {
        assert(argument.rows() == rows());
        assert(argument.cols() == cols());
        Matrix<decltype(function(ScalarType(), typename ScalarType::OtherScalar()))> result;
        result.init(rows(), cols());
        for (int j = 0; j < cols(); ++j) {
            for (int i = 0; i < rows(); ++i) {
                result(i, j) = function(operator()(i, j), argument(i, j));
            }
        }
        return std::move(result);
    }
    
    template <class ScalarType>
    ScalarType MatrixBase<ScalarType>::sum() const {return base().sum();}
    
    template <class ScalarType>
    inline Matrix<ScalarType> MatrixBase<ScalarType>::cwiseProduct(
        const Matrix<ScalarType>& argument
    ) const {
        return binaryExpr(
            argument,
            [] (const ScalarType& first_argument, const ScalarType& second_argument) {
                return first_argument * second_argument;
            }
        )
    }
    
    template <class ScalarType>
    inline Matrix<Interval> MatrixBase<ScalarType>::cwiseProduct(
        const Matrix<typename ScalarType::OtherScalar>& argument
    ) const {
        return binaryExpr(
            argument,
            [] (
                const ScalarType& first_argument,
                const typename ScalarType::OtherScalar& second_argument
            ) {return first_argument * second_argument;}
        )
    }
    
    template <class ScalarType>
    inline Matrix<ScalarType> MatrixBase<ScalarType>::cwiseQuotient(
        const Matrix<ScalarType>& argument
    ) const {
        return binaryExpr(
            argument,
            [] (const ScalarType& first_argument, const ScalarType& second_argument) {
                return first_argument / second_argument;
            }
        )
    }
    
    template <class ScalarType>
    inline Matrix<Interval> MatrixBase<ScalarType>::cwiseQuotient(
        const Matrix<typename ScalarType::OtherScalar>& argument
    ) const {
        return binaryExpr(
            argument,
            [] (
                const ScalarType& first_argument,
                const typename ScalarType::OtherScalar& second_argument
            ) {return first_argument / second_argument;}
        )
    }
    
    template <class ScalarType>
    inline ScalarType MatrixBase<ScalarType>::dot(
        const Vector<ScalarType>& argument
    ) const {return Vector<ScalarType>(*this).dot(argument);}
    
    template <class ScalarType>
    inline Interval MatrixBase<ScalarType>::dot(
        const Vector<typename ScalarType::OtherScalar>& argument
    ) const {return Vector<ScalarType>(*this).dot(argument);}
    
    template <class ScalarType>
    inline Vector<ScalarType> MatrixBase<ScalarType>::cross(
        const Vector<ScalarType>& argument
    ) const {return Vector<ScalarType>(*this).cross(argument);}
    
    template <class ScalarType>
    inline Vector<Interval> MatrixBase<ScalarType>::cross(
        const Vector<typename ScalarType::OtherScalar>& argument
    ) const {return Vector<ScalarType>(*this).cross(argument);}
    
    template <class ScalarType>
    inline ScalarType MatrixBase<ScalarType>::norm() const {
        return Vector<ScalarType>(*this).norm();
    }
    
    template <class ScalarType>
    inline ScalarType MatrixBase<ScalarType>::squaredNorm() const {
        return Vector<ScalarType>(*this).squaredNorm();
    }
    
    template <class ScalarType>
    inline Vector<ScalarType> MatrixBase<ScalarType>::normalized() const {
        return Vector<ScalarType>(*this).normalized();
    }
    
    template <class ScalarType>
    inline Matrix<ScalarType> MatrixBase<ScalarType>::transpose() const {
        Matrix<ScalarType> result;
        result.init(cols(), rows());
        result.base() = base().transpose();
        return std::move(result);
    }
    
    template <class ScalarType>
    inline ScalarType MatrixBase<ScalarType>::determinant() const {return base().determinant();}
    
    template <class ScalarType>
    inline bool MatrixBase<ScalarType>::isZero(double precision = OPENSOLID_PRECISION) const {
        for (int j = 0; j < cols(); ++j) {
            for (int i = 0; i < rows(); ++i) {
                if (!operator()(i, j).isZero(precision)) {return false;}
            }
        }
        return true;
    }
    
    template <class ScalarType>
    inline bool MatrixBase<ScalarType>::isEqualTo(
        const Matrix<ScalarType>& argument,
        double precision = OPENSOLID_PRECISION
    ) const {
        assert(rows() == argument.rows());
        assert(cols() == argument.cols());
        for (int j = 0; j < cols(); ++j) {
            for (int i = 0; i < rows(); ++i) {
                if (!operator()(i, j).isZero(precision)) {return false;}
            }
        }
        return true;
    }
    
    template <class ScalarType>
    inline Matrix<ScalarType> MatrixBase<ScalarType>::Zero(int size) {return Zero(size, size);}
    
    template <class ScalarType>
    inline Matrix<ScalarType> MatrixBase<ScalarType>::Zero(int rows, int cols) {
        Matrix<ScalarType> result;
        result.init(rows, cols);
        result.base().setZero();
        return std::move(result);
    }
    
    template <class ScalarType>
    inline Matrix<ScalarType> MatrixBase<ScalarType>::Ones(int size) {return Ones(size, size);}
    
    template <class ScalarType>
    inline Matrix<ScalarType> MatrixBase<ScalarType>::Ones(int rows, int cols) {
        Matrix<ScalarType> result;
        result.init(rows, cols);
        result.base().setOnes();
        return std::move(result);
    }
    
    template <class ScalarType>
    inline Matrix<ScalarType> MatrixBase<ScalarType>::Identity(int size) {
        return Identity(size, size);
    }
    
    template <class ScalarType>
    inline Matrix<ScalarType> MatrixBase<ScalarType>::Identity(int rows, int cols) {
        Matrix<ScalarType> result;
        result.init(rows, cols);
        result.base().setIdentity();
        return std::move(result);
    }
    
    template <class ScalarType>
    inline Matrix<ScalarType> MatrixBase<ScalarType>::Random(int size) {return Random(size, size);}
    
    template <class ScalarType>
    inline Matrix<ScalarType> MatrixBase<ScalarType>::Random(int rows, int cols) {
        Matrix<ScalarType> result;
        result.init(rows, cols);
        result.base().setRandom();
        return std::move(result);
    }
}

#endif
